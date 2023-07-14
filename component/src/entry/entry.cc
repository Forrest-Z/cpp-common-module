
#include "component_interface.h"
#include "dynamic_load.h"
#include "gomros_interface.h"

int StartProcess() {
  // 初始化线程等基础组件
  InitGomros();

  // 加载组件so  component.xml
  // 可以检查组件间版本依赖关系是否正确
  // 加载动态库 dlopen dlsym
  gomros::entry::ComponentFunc componet = {ComponentInit, ComponentUninit};

  // 根据配置加载动态库，调用启动接口
  componet.init(nullptr);

  // start 基础组件
  StartGomros();

  // 等待结束信号

  // 完成一些必要动作,结束组件
  componet.uninit(nullptr);

  // 关闭线程等基础组件
  UninitGomros();
}

// 主入口
int Entry(int argc, char** argv) {
  // 解析参数

  // 一堆  if else 分支判断

  // // 读配置文件 product.xml 一个
  // //
  // //

  // // 启动单个进程
  // StartProcess();

  // // 等待所有进程结束
  // // 在等待过程中可监控进程状态
}