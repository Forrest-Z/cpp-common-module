
#include "entry/entry.h"
#include "component_interface.h"
#include "gomros_interface.h"

typedef struct ComponentFunc {
  void (*init)(char*, int);
  void (*destroy)();
} ComponentFunc;

int StartProcess() {
  // 初始化线程等基础组件
  InitGomros();

  // 加载组件so  component.xml
  // 可以检查组件间版本依赖关系是否正确
  // 加载动态库 dlopen dlsym
  ComponentFunc componet = {ComponentInit, ComponentUninit};

  // 根据配置加载动态库，调用启动接口
  componet.init(nullptr, 0);

  // start 基础组件
  StartGomros();

  // 等待结束信号

  // 完成一些必要动作,结束组件
  componet.destroy();

  // 关闭线程等基础组件
  DestroyGomros();
}

// 主入口
int Entry(int argc, char** argv) {
  // 解析参数

  // 读配置文件 product.xml

  // 启动进程 , 根据配置文件可启动多个 , fork 子进程
  StartProcess();

  // 等待所有进程结束
  // 在等待过程中可监控进程状态
}