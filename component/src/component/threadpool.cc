/**
 * @file threadpool.cc
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-08-08
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */

#include "threadpool.h"
#include "../threadpool/thread_manager.h"

namespace gomros {
namespace entry {

bool ThreadPoolImpl::AddTimerMsg(const std::string &name, bool loop_flag,
                                 bool execute_immediately, int interval_ms,
                                 const std::string &topic,
                                 const std::string &msg) {
  // todo: 根据消息组件来写
}

bool ThreadPoolImpl::AddNormalTask(const std::string &name,
                                   std::function<void()> loop_func,
                                   std::function<void()> break_func) {


  threadpool::ThreadManager::Instance().AddTask(name, loop_func, break_func);
}

} // namespace entry
} // namespace gomros