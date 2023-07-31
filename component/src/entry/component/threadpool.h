#pragma once

#include "entry/componet.h"

namespace gomros {
namespace entry {

class ThreadPoolImpl : public ThreadPool {
 private:
  /* data */
 public:
  ThreadPoolImpl(/* args */) {}
  ~ThreadPoolImpl() {}

  /**
*@brief 添加定时消息，根据配置定时发布消息
*
*@param name 任务名称
*@param loop_flag 是否是循环任务 ， true:是
*@param execute_immediately 是否立即执行 ，  true:是
*@param interval_ms 时间间隔，等过interval_ms才开始执行
*@param topic 消息话题
*@param msg 消息内容
*@return true 添加成功
*@return false 添加失败
*/
  virtual bool AddTimerMsg(const std::string& name, bool loop_flag,
                           bool execute_immediately, int interval_ms,
                           const std::string& topic, const std::string& msg) {}

  /**
 * @brief
 * 无特定目的的普通线程，线程循环(loop_func)和退出逻辑(break_func)均由相关模块提供
 *
 * @param name 任务名称，若重名会添加失败
 * @param loop_func 循环函数
 * @param break_func 退出函数
   * @return true 成功
 * @return false 失败
 */
  virtual bool AddNormalTask(const std::string& name,
                             std::function<void()> loop_func,
                             std::function<void()> break_func) {}
};

}  // namespace entry
}  // namespace gomros