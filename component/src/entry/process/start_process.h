#pragma once

#include <string>

namespace gomros {
namespace entry {

/**
 * @brief 启动进程类
 * 
 */
class StartProcess {
 public:
 /**
  * @brief 启动产品，主线程
  * 
  */
  static void StartProduct();

/**
 * @brief 启动子线程
 * 
 * @param name 子线程名称,与配置文件对应
 */
  static void StartSingleProcess(const std::string& name);

 private:
 /**
  * @brief 获取程序当前运行路径，如： /opt/gomros/run/gomros-1.0/bin/gomros
  * 
  * @param program_running_path 当前程序运行路径
  * @return true 成功
  * @return false 失败
  */
  static bool GetProgramRunningPath(std::string& program_running_path);
};

}  // namespace entry
}  // namespace gomros
