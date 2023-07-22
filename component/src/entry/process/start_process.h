#pragma once

#include <string>

namespace gomros {
namespace entry {

class StartProcess {
 public:
  static void StartProduct();

  static void StartSingleProcess(const std::string& name);

 private:
  static bool GetProgramRunningPath(std::string& program_running_path);
};

}  // namespace entry
}  // namespace gomros
