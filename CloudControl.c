#include <CloudControl.h>

#include "DataStorage.h"
#include "usart1.h"

/**
 * @brief  CloudControl structure definition
 */

#define QUEUEMAXNUM 20
#define QUEUELEN 20

u8 Dir_flag = 0;
u8 addtask_flag = 0;
u8 cleartask_flag = 0;

typedef struct {
  u16 task;          /*!< 任务种类 */
  u8 data[QUEUELEN]; /* 数据 */
  u8 len;            /* 长度 */

} CommandTypedef;

CommandTypedef command[QUEUEMAXNUM];

CommandTypedef new_command;

typedef struct {
  u16 task; /* 任务 */

  u32 rfid;    /* 点值 */
  u8 dir;      /* 方向 */
  u8 next_dir; /* 下个方向 */
  u8 pre_dir;
  float last_v; /*取上一次速度的正负（读地标用）*/
  float v;      /* m/s */
  u8 park_rank; /* 停车等级  */
  int timeout_cnt;

} CloudControlType;

struct {
  u8 head;
  u8 rear;
  u8 num;
} queue = {0, 0, 0};

enum { START, RUNNING, END } TaskState = START; /* enum {START, RUNNING, END} */

CloudControlType CloudControl;

/** @defgroup commandTask_define_Constants
 * @{
 */
#define TASK_NULL 0
#define TASK_MOVE 0xC100           // 行走任务
#define TASK_CANCEL 0xC102         // 任务取消
#define TASK_LOADUP 0xC105         // 顶升上升
#define TASK_LOADDOWN 0xC106       // 顶升下降
#define TASK_ROURELOCK 0xC201      // 路线锁定
#define TASK_TURN 0xC10A           // 旋转
#define TASK_ROOFTURN 0xC10B       // 顶升旋转
#define TASK_TURN_ROOFSTOP 0xC10C  // 顶升旋转停止
#define TASK_WRITE_PARA 0xC10D     // 写入参数
#define TASK_READ_PARA 0xC10F      // 读取参数
#define TASK_Debug 0xD100          // 调试

/**
 * @brief 清除任务队列
 *
 * @return
 * @note
 */
static void ClearTask(void) {
  queue.num = 0;   // 队列号码
  queue.head = 0;  // 队列头
  queue.rear = 0;  // 队列尾

  for (int i = 0; i < QUEUEMAXNUM; i++) {
    command[i].task = 0;
  }

  TaskState = END;
}

/**
 * @brief 增加一个任务（只在usart1.c中调用）
 *
 * @return 0:false 1:true
 * @note
 */
u8 CloudControlAddTask(u8 *arr, u8 len) {
  /* 清任务指令 */
  u16 task = (arr[0] << 8 | arr[1]);  // CXXX
  if (task == TASK_CANCEL) {
    cleartask_flag = 1;
    return 1;
  }

  addtask_flag = 1;
  new_command.task = task;
  new_command.len = len;
  for (u8 i = 0; i < len; i++) new_command.data[i] = arr[i + 2];
  return 1;
}

/**
 * @brief 任务向下个任务推进
 *
 * @return
 * @note	当完成一个任务时，任务向下个任务推进
 */
static void TaskMovetoNext(void) {
  if (queue.num > 0) {
    queue.num--;
    command[queue.head].task = 0;
    queue.head = (queue.head+1) % QUEUEMAXNUM;
  }
}

static void TaskNull(void) {
  if (queue.num > 0) TaskMovetoNext();

  /******************LogicOutput************************/
  /* move */
  CarDrive_Clear();
  CarNavi.warning_obav_in_flag = 0;
  CarNavi.warning_obav_out_flag = 0;

  LogicOutput.move.state = MOVE_STOP;
  LogicOutput.move.v = 0;
  LogicOutput.move.angle = 0;
  LogicOutput.move.omega = 0;
  LogicOutput.liftState = LIFT_STOP;

  /* led */
  LogicOutput.led = LED_BLUE;

  /* voice */
  LogicOutput.voice = VOICE_NONE;

  /* command feedback */
  LogicOutput.hostComputerCommand = COMMAND_NONE;

  TaskState = START;
}

/**
 * @brief TaskSteerTurn
 *
 * @return
 */
static void TaskSteerTurn(void) {  // 只在TaskMove中调用

  CarDrive.steer_turn_state = steer_turn;

  /***************** LogicOutput *******************/
  /* move */
  LogicOutput.move.state = MOVE_STEERTURN;
  // CarDrive.v = 0;
  LogicOutput.move.v = 0;
  LogicOutput.move.angle = CarDrive.tar_angle;
  LogicOutput.move.omega = 0;

  /* led */
  LogicOutput.led = LED_BLUE;

  /* voice */
  LogicOutput.voice = VOICE_MUSIC;

  /* command feedback */
  LogicOutput.hostComputerCommand = COMMAND_NONE;
}

static void TaskMove(void) {
  /* led */
  LogicOutput.led = LED_BLUE;
  /* voice */
  LogicOutput.voice = VOICE_MUSIC;

  /* 当行走子任务开始执行时，发送一次当前RFID信息,与调度系统交互 */
  if (TaskState == START) {
    TaskState = RUNNING;
    CloudControl.timeout_cnt = 0;

    // pre
    CloudControl.pre_dir = CloudControl.dir;

    u8 *p;

    CloudControl.task = command[queue.head].task;

    p = command[queue.head].data;
    CloudControl.rfid = p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
    CloudControl.dir = p[4];
    CloudControl.v = (p[5] << 8 | p[6]) / 1000.0;
    if (CloudControl.dir == TRAVERSE_R || CloudControl.dir == TRAVERSE_L)
      Dir_flag = 1;

    // if (CloudControl.v == 0) CloudControl.dir = CARSTOP;
    // 速度为0（停车），使用上一指令的方向
    if (CloudControl.v == 0) {
      CloudControl.dir = CloudControl.pre_dir;
    }

    CloudControl.park_rank = (p[7] >> 4) & 0x1;
    if (CloudControl.v != 0)  // 速度不为0时不接收读地标指令
    {
      CloudControl.park_rank = 0;
    }
    /* 直接设置避障区域，只在此地方设置改参数 */
    LogicOutput.move.OBAV_area = (p[7] >> 0) & 0x7;  // p[7]后三位用于设置避障

    if (CloudControl.dir == BACKWARD || CloudControl.dir == BACKWARD_L ||
        CloudControl.dir == BACKWARD_R || CloudControl.dir == TRAVERSE_R)
      CloudControl.v = -CloudControl.v;

    LogicOutput.hostComputerCommand = COMMAND_ARRIVERFID;

    return;
  }

  /* 获取下一个点运行方向 */
  CommandTypedef next_cmd = command[(queue.head + 1) % QUEUEMAXNUM];
  if ((queue.num > 1) && (next_cmd.task != 0)) {
    CloudControl.next_dir = next_cmd.data[4];
  } else
    CloudControl.next_dir = CARSTOP;

  /* END */
  if (TaskState == END) {
    TaskMovetoNext();
    TaskState = START;
    //==============================================================================================
    LogicOutput.hostComputerCommand =
        COMMAND_NONE;  // 消除停车之后行走指令的返回信号不一致
    //==============================================================================================
    return;
  }

  // running
  CloudControl.timeout_cnt++;

  /* 调轮子角度 */
  {
    float tar_angle;

    u8 dir = CloudControl.dir;
    if ((dir == TRAVERSE_R) || (dir == TRAVERSE_L))
      tar_angle = 90;
    else if ((dir == FORWARD) || (dir == FORWARD_L) || (dir == FORWARD_R) /* */
             || (dir == BACKWARD) || (dir == BACKWARD_L) || (dir == BACKWARD_R))
      tar_angle = 0;
    else {
      tar_angle = CarDrive.tar_angle;
      CarDrive.steer_turn_state = steer_end;  // 引导转轮子到目标角度的状态
    }
    if (CarDrive.tar_angle != tar_angle) {
      CarDrive.steer_turn_state = steer_start;
      CarDrive.tar_angle = tar_angle;
    }

    if (CarDrive.steer_turn_state != steer_end) {
      TaskSteerTurn();
      return;
    }
  }

  LogicOutput.hostComputerCommand = COMMAND_NONE;

  CarDrive.get_v = CloudControl.v;

  if (CloudControl.v != 0)  // 获取速度不为零时的正负号
    CloudControl.last_v = CloudControl.v;
  else
    CloudControl.last_v = CloudControl.last_v;

  /* 获取避障减速 */
  {
    float r;
    u8 dir = CloudControl.dir;

    if (dir == FORWARD || dir == FORWARD_L || dir == FORWARD_R)
      r = CarNavi.front_dec_r;
    else if (dir == BACKWARD || dir == BACKWARD_L || dir == BACKWARD_R)
      r = CarNavi.rear_dec_r;
    else if (dir == TRAVERSE_L || dir == TRAVERSE_R)
      r = (CarNavi.rear_dec_r && CarNavi.front_dec_r);  // CarNavi.side_dec_r
    else if (dir == CARSTOP)
      r = 1;
    else
      r = 0;

    if (r == 0) {
      CarNavi.warning_obav_in_flag = 1;
      CarNavi.warning_obav_out_flag = 0;
    } else if ((r == CarParameter.OBAV_LimitLevel1) ||
               (r == CarParameter.OBAV_LimitLevel2)) {
      CarNavi.warning_obav_out_flag = 1;
      CarNavi.warning_obav_in_flag = 0;
    } else {
      CarNavi.warning_obav_in_flag = 0;
      CarNavi.warning_obav_out_flag = 0;
    }

    CarDrive.exp_v = CarDrive.get_v * r;
  }

  /* 根据方向行走 */
  u8 dir = CloudControl.dir;

  if (CloudControl.v == 0) {         // stop
    if (CloudControl.park_rank == 1) /* 读地标停 */
    {
      if (CloudControl.last_v > 0)
        CarDrive.exp_v = 0.05;
      else if (CloudControl.last_v < 0)
        CarDrive.exp_v = -0.05;
      else
        CarDrive.exp_v = 0;
			
			// 避障清除计数
			if(CarInfo.warningCode  == WARNING_OBAVINSIDE) {
				CloudControl.timeout_cnt = 0;
			}

      // timeout stop
      if (CloudControl.timeout_cnt++ >= 1000) {
        CloudControl.timeout_cnt = 1000;
        CarDrive.exp_v = 0;
        LogicOutput.led = LED_YELLOW;
      }

      //			if(Dir_flag == 1)
      //			{
      if (CarNavi.landmark2_flag || CarNavi.landmark1_flag) /* 读到地标 */
        CloudControl.park_rank = 0;
      //			}
      //			else
      //			{
      //				if (CarNavi.landmark1_flag) /* 读到地标
      //*/ 					CloudControl.park_rank = 0;
      //			}

    } else {
      if (fabs(CarDrive.v) < 2 * CarParameter.vThreshold) {
        TaskState = END;
        LogicOutput.hostComputerCommand = COMMAND_STOPCOMPLETE;
      }
    }

    LogicOutput.move.state = MOVE_ObliqueRUN;
    LogicOutput.move.angle = CarDrive.tar_angle;

    LogicOutput.move.E_F = 0;
    LogicOutput.move.E_B = 0;
  } else if (dir == FORWARD || dir == FORWARD_R || dir == FORWARD_L /* */
             || dir == BACKWARD || dir == BACKWARD_L || dir == BACKWARD_R) {
    /* 到达目标点，任务完成 */
    if (CarInfo.rfid != CloudControl.rfid)
      if (CarInfo.rfid != 0) TaskState = END;

    /* move */
    LogicOutput.move.state = MOVE_RUN;
    LogicOutput.move.angle = 0;
    LogicOutput.move.omega = 0;

    LogicOutput.move.E_F = CarNavi.delta_F;
    LogicOutput.move.E_B = CarNavi.delta_B;

  } else if (dir == TRAVERSE_L || dir == TRAVERSE_R) {
    /* 到达目标点，任务完成 */
    if (CarInfo.rfid != CloudControl.rfid) TaskState = END;

    /* move */
    LogicOutput.move.state = MOVE_ObliqueRUN;
    LogicOutput.move.angle = CarDrive.tar_angle;
    LogicOutput.move.omega = 0;
    /*横移用一条磁条*/
    LogicOutput.move.E_F =
        (CarNavi.delta_F) / 2;  // 能加后舵轮偏差吗？+ CarNavi.delta_B
    LogicOutput.move.E_B = LogicOutput.move.E_F;
    /*横移用两条磁条-2023.11.15*/
    //		LogicOutput.move.E_F = (CarNavi.delta_F) / 2;
    //		LogicOutput.move.E_B = (CarNavi.delta_B) / 2;
  }
  /* 配置加减速控制实际下发速度 */
  {
    if (fabs(CarDrive.v - CarDrive.exp_v) < CarParameter.vThreshold)
      CarDrive.v = CarDrive.exp_v;
    else if (CarDrive.v < CarDrive.exp_v)
      CarDrive.v += CarInfo.circleTime * CarParameter.v_a;
    else if (CarDrive.v > CarDrive.exp_v)
      CarDrive.v -= CarInfo.circleTime * CarParameter.v_a;

    LogicOutput.move.v = CarDrive.v;
  }

  /*漏点（由上位机判断）*/
}
/**
 * @brief 云控制小车顶板顶升
 *
 * @return

 */
static void TaskLiftUp(void) {
  LogicOutput.liftState = LIFT_UP;
  LogicOutput.move.state = MOVE_STOP;
  LogicOutput.move.v = 0;
  LogicOutput.led = LED_BLUE;
  LogicOutput.voice = VOICE_MUSIC;
  LogicOutput.hostComputerCommand = COMMAND_NONE;

  if (SignalIn.LiftUpLimit == 1) {
    TaskNull();
    LogicOutput.hostComputerCommand = COMMAND_UPLOADCOMPLETE;
  }
}
/**
 * @brief 云控制小车顶板下降
 *
 * @return

 */
static void TaskLiftDown(void) {
  LogicOutput.liftState = LIFT_DOWN;
  LogicOutput.move.state = MOVE_STOP;
  LogicOutput.move.v = 0;
  LogicOutput.led = LED_BLUE;
  LogicOutput.voice = VOICE_MUSIC;
  LogicOutput.hostComputerCommand = COMMAND_NONE;

  if (SignalIn.LiftDownLimit == 1) {
    TaskNull();
    LogicOutput.hostComputerCommand = COMMAND_DOWNLOADCOMPLETE;
  }
}

/**
 * @brief 云控制小车路径锁定
 *
 * @return

 */
static void TaskRouteLock(void) {
  LogicOutput.voice = VOICE_NONE;
  LogicOutput.hostComputerCommand = COMMAND_NONE;

  /* 如果接收到新的任务,当前路径锁定任务完成 */
  //	if (CloudControlNext.task != TASK_NULL)
  //		command.TaskCompleteFlag = 1;
}

/**
 * @brief 云控制小车参数写入
 *
 * @return

 */
static void TaskWritePara(void) {
  /* 参数配置 */
  float index, value;
  u8 *p = command[queue.head].data;

  value = (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]) / 10000.0;
  index = p[4];

  CarParameter_singleParaWrite(index, value);
  /* 数据存储 */
  ParameterData_Write();

  LogicOutput.move.state = MOVE_STOP;
  LogicOutput.move.v = 0;
  LogicOutput.led = LED_BLUE;
  LogicOutput.voice = VOICE_NONE;
  LogicOutput.hostComputerCommand = COMMAND_NONE;

  para_Write_Feedback(value, index);

  /* 任务完成 */
  TaskMovetoNext();
}
/**
 * @brief 云控制小车参数读取
 *
 * @return

 */
static void TaskReadPara(void) {
  /* 参数配置 */
  float index, value;
  u8 *p = command[queue.head].data;

  index = p[0];

  value = CarParameter_singleParaRead(index);

  LogicOutput.move.state = MOVE_STOP;
  LogicOutput.move.v = 0;
  LogicOutput.led = LED_BLUE;
  LogicOutput.voice = VOICE_NONE;
  LogicOutput.hostComputerCommand = COMMAND_NONE;

  para_Read_Feedback(value, index);

  /* 任务完成 */
  TaskMovetoNext();
}

/**
 * @brief 云控制
 *
 * @return

 */
void CloudControlProcess(void) {
  if (addtask_flag) {
    addtask_flag = 0;
    command[queue.rear] = new_command;
    queue.rear = (queue.rear+1) % QUEUEMAXNUM;
    queue.num++;
  }

  if (cleartask_flag) {
    cleartask_flag = 0;
    ClearTask();
  }

  LogicOutput.led = LED_BLUE;
  switch (command[queue.head].task) {
    case TASK_NULL:  // 空任务
      TaskNull();
      break;
    case TASK_MOVE:  // 行走任务
      TaskMove();
      break;
    case TASK_LOADUP:  // 顶升上升
      TaskLiftUp();
      break;
    case TASK_LOADDOWN:  // 顶升下降
      TaskLiftDown();
      break;
    case TASK_ROURELOCK:  // 路线锁定
      TaskRouteLock();
      break;
    case TASK_WRITE_PARA:  // 写参数
      TaskWritePara();
      break;
    case TASK_READ_PARA:  // 读参数
      TaskReadPara();
      break;
    case TASK_CANCEL:
      ClearTask();  // 清空任务
      break;
    default:
      TaskNull();
      break;
  }

  if (CarInfo.green_button == 1) LogicOutput.move.OBAV_area = 0x07;

  /* 小车方向 */
  CarInfo.dir = CloudControl.dir;

  /* 后台控制有任务时小车亮绿灯 */
  //	if(command[queue.head].task == TASK_NULL)
  //		LogicOutput.led = LED_YELLOW;
  //	else
  //		LogicOutput.led = LED_BLUE;
}
