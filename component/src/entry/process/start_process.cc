
#include <string>

#include "../component/component_manager.h"
#include "../component/search_file.h"
#include "../dynamicload/dynamic_load.h"
#include "../framework/gomros_interface.h"
#include "../params_define.h"
#include "log/log.h"
#include "start_process.h"

namespace gomros {
namespace entry {

void StartProcess::StartProduct() {
  LOG_INFO("start product . \n");

  ComponentManager::Instance().Init();

  std::vector<std::string> file_paths;
  SearchFile::GetFilePaths(GOMROS_APPLICATION, file_paths);

  if (file_paths.size() == 0) {
    return;
  }

  //
  std::vector<std::string> process_name_list;
  ComponentManager::Instance().GetProcessNameList(process_name_list);
  for (auto& sub_process_name : process_name_list) {
    std::string cmd;
    cmd += file_paths[0];
    cmd += " -process ";
    cmd += sub_process_name;

    // 开启 子线程
    LOG_INFO("cmd : %s \n", cmd.c_str());
    system(cmd.c_str());
  }

  // 主线程 监控 子线程或其他任务

  // 等待结束信号
  //
}

void StartProcess::StartSingleProcess(const std::string& name) {
  // init comp manager
  LOG_INFO("start process . \n");
  ComponentManager::Instance().Init(name);

  //
  ComponentManager::Instance().LoadAllComponent();

  // 初始化线程等基础组件
  InitGomros();

  ComponentManager::Instance().InitAllComponent();

  // start 基础组件
  StartGomros();

  // 等待结束信号
  //

  // uninit all component
  ComponentManager::Instance().UnInitAllComponent();

  // 关闭线程等基础组件
  UninitGomros();

  ComponentManager::Instance().Uninit();
};

}  // namespace entry
}  // namespace gomros
