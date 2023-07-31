
#include <vector>

#include "../params_define.h"
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
void ComponentManager::Init(
    std::map<std::string, std::vector<std::string>>& cmd_map) {
  SearchFile::Instance().AddFolder(GOMROS_INSTALL_PATH);

  if (cmd_map.find(CMD_ADD_COMPONENT_PATH) != cmd_map.end()) {
    for (auto i : cmd_map[CMD_ADD_COMPONENT_PATH]) {
      SearchFile::Instance().AddFolder(i);
    }
  }

  std::vector<std::string> file_paths;

  SearchFile::Instance().GetFilePaths(PRODUCT_CONFIG_FILENAME, file_paths);

  // 逐个读取合并 product.xml
  // serialize::decoder();
  // gomros::entry::ProductCfgTypedef  temp;
  //     gomros::serialize::utils::decode(GOMROS_SERIAL_XML,temp);

  product_cfg;

  end_sem = std::make_shared<gomros::threadpool::Semaphore>(0);
}

void ComponentManager::Init(
    const std::string& process_name,
    std::map<std::string, std::vector<std::string>>& cmd_map) {
  Init(cmd_map);
  this->process_name = process_name;
}

void ComponentManager::Uninit() {
  delete instance;
  instance = nullptr;

  LOG_INFO("delete instance . \n");
}

void ComponentManager::WaitEnd() {
  LOG_INFO("wait end . \n");

  this->end_sem->Wait();
}

void ComponentManager::LoadAllComponent() {
  // component.xml
  std::vector<std::string> file_paths;

  // SearchFile::GetFilePaths(COMPONENT_CONFIG_FILENAME, file_paths);
  // read all comp cfg

  // SearchFile::GetFilePaths(COMPONENT_CONFIG_FILENAME, file_paths);
  // decode
  this->component_cfg_map;

  for (auto& process : product_cfg.processes) {
    if (process.name == process_name) {
      this->process_name = process_name;

      for (auto& comp : process.component) {
        this->component_list.push_back(new ComponetImpl(comp));
      }

      break;
    }
  }

  // serialize::decoder();

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
