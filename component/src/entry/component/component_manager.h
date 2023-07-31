
#pragma once

#include <vector>

#include "../config_struct.h"
#include "componet_impl.h"
#include "entry/componet.h"
#include "threadpool/semaphore.h"

namespace gomros {
namespace entry {

class ComponentManager {
 public:
  static ComponentManager& Instance();

  // 主进程 中 初始化
  void Init(std::map<std::string, std::vector<std::string>>& cmd_map);
  // 子进程 中 初始化
  void Init(const std::string& process_name,
            std::map<std::string, std::vector<std::string>>& cmd_map);
  void Uninit();

  void LoadAllComponent();

  void WaitEnd();

  void InitAllComponent();
  void UnInitAllComponent();

  void GetProcessNameList(std::vector<std::string>& process_name_list) {
    process_name_list.clear();
    process_name_list = subprocess_name;
  }

  bool GetComponentPath(const std::string& name, std::string& path) {
    if (comp_name_path_map.find(name) != comp_name_path_map.end()) {
      path = comp_name_path_map[name];
      return true;
    }

    return false;
  }

 private:
  ComponentManager() {}
  ~ComponentManager() {}

  static ComponentManager* instance;

  // name , component_path
  std::map<std::string, std::string> comp_name_path_map;

  std::vector<ComponetImpl*> component_list;
  ProductCfgTypedef* product_cfg = nullptr;

  std::string process_name;
  std::vector<std::string> subprocess_name;

  std::shared_ptr<gomros::threadpool::Semaphore> end_sem;
};

}  // namespace entry
}  // namespace gomros
