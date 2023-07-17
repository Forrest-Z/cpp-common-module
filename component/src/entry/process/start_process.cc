
#include <string>

#include "../dynamicload/dynamic_load.h"
#include "../framework/gomros_interface.h"
#include "log/log.h"
#include "start_process.h"

namespace gomros {
namespace entry {

void StartProcess::StartProduct() { LOG_INFO("start product . \n"); };

void StartProcess::StartSingleProcess(const std::string& name) {
  // 初始化线程等基础组件
  InitGomros();

  // 加载组件so  component.xml
  // 可以检查组件间版本依赖关系是否正确
  // 加载动态库 dlopen dlsym
  gomros::entry::ComponentFunc componet;

  // 根据配置加载动态库，调用启动接口
  componet.init(nullptr);

  // start 基础组件
  StartGomros();

  // 等待结束信号

  // 完成一些必要动作,结束组件
  componet.uninit(nullptr);

  // 关闭线程等基础组件
  UninitGomros();
};

}  // namespace entry
}  // namespace gomros
