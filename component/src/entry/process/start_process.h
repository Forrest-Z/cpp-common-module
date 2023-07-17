#pragma once

#include <string>

namespace gomros {
namespace entry {

class StartProcess {
 public:
  static void StartProduct();

  static void StartSingleProcess(const std::string& name);
};

}  // namespace entry
}  // namespace gomros
