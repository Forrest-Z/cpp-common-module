
#include <string>

#include "../../component/component_manager.h"
#include "../../component/dynamicload/dynamic_load.h"
#include "../../component/search_file.h"
#include "../framework/gomros_interface.h"
#include "../params_define.h"
#include "log/log.h"
#include "start_process.h"

namespace gomros {
namespace entry {

void StartProcess::StartProduct(
    std::map<std::string, std::vector<std::string>> &cmd_map) {
  LOG_INFO("start product . \n");

  std::string running_path;
  GetProgramRunningPath(running_path);

  ComponentManager::Instance().Init(cmd_map);

  std::string add_path_cmd;
  if (cmd_map.find(CMD_ADD_COMPONENT_PATH) != cmd_map.end()) {
    add_path_cmd += " ";
    add_path_cmd += CMD_ADD_COMPONENT_PATH;
    for (auto i : cmd_map[CMD_ADD_COMPONENT_PATH]) {
      add_path_cmd += " ";
      add_path_cmd += i;
    }
    add_path_cmd += " ";
  }

  //
  std::vector<std::string> process_name_list;
  ComponentManager::Instance().GetProcessNameList(process_name_list);
  for (auto &sub_process_name : process_name_list) {
    std::string cmd;
    cmd += running_path;
    cmd += " ";
    cmd += CMD_PROCESS;
    cmd += " ";
    cmd += sub_process_name;
    cmd += add_path_cmd;

    // 开启 子线程
    LOG_INFO("cmd : %s \n", cmd.c_str());
    { auto ret = system(cmd.c_str()); }
  }

  // 主线程 监控 子线程或其他任务

  // todo: 等待结束信号 退出消息 (收到退出消息时产生结束信号)
  // ComponentManager::Instance().WaitEnd();
  //
}

void StartProcess::StartSingleProcess(
    const std::string &name,
    std::map<std::string, std::vector<std::string>> &cmd_map) {
  // init comp manager
  LOG_INFO("start subprocess . \n");
  ComponentManager::Instance().Init(name, cmd_map);

  //
  ComponentManager::Instance().LoadAllComponent();

  // 初始化线程等基础组件
  InitGomros();

  ComponentManager::Instance().InitAllComponent();

  // start 基础组件
  StartGomros();

  // 等待结束信号 退出消息
  // ComponentManager::Instance().WaitEnd();

  // uninit all component
  ComponentManager::Instance().UnInitAllComponent();

  // 关闭线程等基础组件
  UninitGomros();

  ComponentManager::Instance().Uninit();
};

#include <stdio.h>
#include <unistd.h>

bool StartProcess::GetProgramRunningPath(std::string &program_running_path) {
  program_running_path.clear();

  char szBuf[UINT16_MAX];
  char szPath[UINT16_MAX];

  memset(szBuf, 0x00, sizeof(szBuf));
  memset(szPath, 0x00, sizeof(szPath));

  { auto i = getcwd(szBuf, sizeof(szBuf) - 1); }
  LOG_INFO("buf:%s\n", szBuf);

  int ret = readlink("/proc/self/exe", szPath, sizeof(szPath) - 1);
  LOG_INFO("ret:%d", ret);
  LOG_INFO("path:%s", szPath);

  if (ret == -1) {
    return false;
  }

  program_running_path = std::string(szPath, ret);
  return true;
}

} // namespace entry
} // namespace gomros
