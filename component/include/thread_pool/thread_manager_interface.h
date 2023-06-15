
#pragma once

#include <functional>
#include <string>

namespace gomros {
namespace common {

/**
 * @brief 无参函数，如需要传参用std::bind 绑定成无参函数
 *
 */
typedef std::function<void()> VoidFunc;

/**
 * @brief 线程管理单例类
 *
 */
class ThreadManager;

/**
 * @brief 线程管理单例类接口
 *
 */
class ThreadManagerInterface {
 public:
  /**
   * @brief 添加定时任务，第一次执行时间为 interval_ms 间隔后
   *
   * @param name 任务名称
   * @param loop_flag 是否为循环任务，true:循环 ，false:一次
   * @param interval_ms 间隔时间，单位ms
   * @param func 任务函数
   */
  static void AddTask(const std::string& name, bool loop_flag, int interval_ms,
                      VoidFunc func);

/**
 * @brief 添加队列任务，返回唤醒函数，通过唤醒函数控制队列任务执行
 * 
 * @param name 任务名称
 * @param func 执行函数
 * @param priority 线程优先级 (-20~0,-20为最高优先级)
 * @return VoidFunc 唤醒函数
 */
  static VoidFunc AddTask(const std::string& name, VoidFunc func,
                          int priority = 0);

/**
 * @brief 无特定目的的普通线程，线程循环(loop_func)和退出逻辑(break_func)均由相关模块提供
 * 
 * @param name 任务名称
 * @param loop_func 循环函数
 * @param break_func 退出函数
 * @param priority 线程优先级 (-20~0,-20为最高优先级)
 */
  static void AddTask(const std::string& name, VoidFunc loop_func,
                      VoidFunc break_func, int priority = 0);
};

}  // namespace common
}  // namespace gomros
