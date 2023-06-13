
#include "thread_pool/queue_thread.h"
#include "log_define.h"

namespace gomros {
namespace common {

// QueueThread::QueueThread(const std::string& name,
//                            const ThreadPriority& priority,
//                            std::shared_ptr<Semaphore> exit_sema,
//                            VoidFunc loop_func, VoidFunc break_func)
//     : BaseThread(name, priority, exit_sema),
//       loop_func(loop_func),
//       break_func(break_func) {}

// QueueThread::~QueueThread() {}

// void QueueThread::NotifyStop() {
//   info_log("%s exect break_func . \n", this->GetName().c_str());
//   break_func();
// }
// void QueueThread::Exec() {
 
// }
}  // namespace common
}  // namespace gomros
