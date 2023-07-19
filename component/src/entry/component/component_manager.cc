
#include <vector>

#include "../params_define.h"
#include "component_manager.h"
#include "componet_impl.h"
#include "log/log.h"
#include "search_file.h"

namespace gomros {
namespace entry {

ComponentManager* ComponentManager::instance = nullptr;

ComponentManager& ComponentManager::Instance() {
  if (!instance) {
    instance = new ComponentManager();
    LOG_INFO("new instance . \n");
  }

  return *instance;
}
void ComponentManager::Init() {
  std::vector<std::string> file_paths;

  SearchFile::GetFilePaths(PRODUCT_CONFIG_FILENAME, file_paths);

  // 读取合并后的 product.xml
  // serialize::decoder();
  product_cfg;
}

void ComponentManager::Init(std::string process_name) {
  Init();
  // auto * comp_list
  for (auto& process : product_cfg.processes) {
    if (process.name == process_name) {
      this->process_name = process_name;

      for (auto& comp : process.component) {
        this->component_list.push_back(new ComponetImpl(comp));
      }

      break;
    }
  }
}

void ComponentManager::Uninit() {
  delete instance;
  instance = nullptr;

  LOG_INFO("delete instance . \n");
}

void ComponentManager::LoadAllComponent() {
  // component.xml

  // setenv

  // dynamic load
}

void ComponentManager::InitAllComponent() {
  for (auto& i : this->component_list) {
    i->Init();
  }
}
void ComponentManager::UnInitAllComponent() {
  for (auto& i : this->component_list) {
    i->Uninit();
  }
}

}  // namespace entry
}  // namespace gomros
