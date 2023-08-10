/**
 * @file component_manager.cc
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */
#include <vector>

#include "../entry/params_define.h"
#include "common/file_utils.h"
#include "component_config.h"
#include "component_manager.h"
#include "componet_impl.h"
#include "log/log.h"
#include "search_file.h"

namespace gomros {
namespace entry {

ComponentManager *ComponentManager::instance = nullptr;

ComponentManager &ComponentManager::Instance() {
  if (!instance) {
    instance = new ComponentManager();
    LOG_INFO("new instance . \n");
  }

  return *instance;
}

void ComponentManager::ProductCfgInit() {

  std::vector<std::string> target_paths = {GOMROS_INSTALL_PATH};
  std::vector<std::string> file_paths;

  SearchFile::GetFilePaths(target_paths, PRODUCT_CONFIG_FILENAME, file_paths);

  if (file_paths.size() == 0) {
    LOG_ERROR("cant find product cfg .");
    exit(0);
  }

  // todo: fork 多个产品
  auto &cur = file_paths.front();

  {
    {
      std::string fullname = cur + "/" + PRODUCT_CONFIG_FILENAME;
      ComponetConfigImpl::ReadConfigFile(fullname, this->product_cfg);
    }
    // 合并 fix config;

    {
      std::string fullname = std::string(GOMROS_DATA_PATH) + "/" +
                             product_cfg.name + "/" +
                             PRODUCT_CONFIG_FIX_FILENAME;
      ComponetConfigImpl::ReadConfigFile(fullname, this->fix_product);
    }

    for (auto &i : fix_product.processes) {
      for (auto &j : product_cfg.processes) { // 遍历process
        if (i.name == j.name) {
          for (auto &k : i.component) {
            for (auto &l : j.component) { // 遍历 component
              if (k.running_name == l.running_name) {
                map_utils::InsertAndMerge(l.fixed_keyval_map,k.fixed_keyval_map);
                
              }
            }
          }
        }
      }
    }
  }
}

void ComponentManager::Init(
    std::map<std::string, std::vector<std::string>> &cmd_map) {

  ProductCfgInit();

  for (auto &i : this->product_cfg.processes) {
    subprocess_name.push_back(i.name);
    LOG_DEBUG("subprocess  %s", i.name.c_str());
  }

  end_sem = std::make_shared<gomros::async::Semaphore>(0);
}

void ComponentManager::Init(
    const std::string &process_name,
    std::map<std::string, std::vector<std::string>> &cmd_map) {
  Init(cmd_map);
  this->process_name = process_name;

  //
  std::vector<std::string> target_paths = {GOMROS_INSTALL_PATH};
  // add search path
  if (cmd_map.find(CMD_ADD_COMPONENT_PATH) != cmd_map.end()) {
    for (auto &i : cmd_map[CMD_ADD_COMPONENT_PATH])
      target_paths.push_back(i);
  }

  std::vector<std::string> file_paths;
  SearchFile::GetFilePaths(target_paths, COMPONENT_CONFIG_FILENAME, file_paths);

  for (auto &f : file_paths) {
    std::string str_buf;
    gomros::entry::ComponentCfgTypedef temp;
    std::string fullname = f + "/" + COMPONENT_CONFIG_FILENAME;

    ComponetConfigImpl::ReadConfigFile(fullname, temp);

    this->comp_name_path_map.insert({temp.name, f});
  }
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
  for (auto &process : product_cfg.processes) {
    if (process.name == process_name) {
      for (auto &comp : process.component) {
        this->component_list.push_back(new ComponetImpl(comp));
      }

      break;
    }
  }
}

void ComponentManager::InitAllComponent() {
  for (auto &i : this->component_list) {
    i->Init();
  }
}
void ComponentManager::UnInitAllComponent() {
  for (auto &i : this->component_list) {
    i->Uninit();
  }
}

void ComponentManager::GetProcessNameList(
    std::vector<std::string> &process_name_list) {
  process_name_list.clear();
  process_name_list = subprocess_name;
}

bool ComponentManager::GetComponentPath(const std::string &name,
                                        std::string &path) {
  if (comp_name_path_map.find(name) != comp_name_path_map.end()) {
    path = comp_name_path_map[name];
    return true;
  }

  return false;
}

void ComponentManager::ChangeProductCfg(ComponentFixCfgTypedef &fix_cfg) {

  // todo: read and write

  // read

  std::string fullname = std::string(GOMROS_DATA_PATH) + "/" +
                         product_cfg.name + "/" + PRODUCT_CONFIG_FIX_FILENAME;
  ComponetConfigImpl::ReadConfigFile(fullname, this->fix_product);

  // change
  for (auto &i : this->fix_product.processes) {
    for (auto &j : i.component) {
      if (j.running_name == fix_cfg.running_name) {
        j = fix_cfg;

        // write
        ComponetConfigImpl::WriteConfigFile(fullname, this->fix_product);
        return;
      }
    }
  }
}

} // namespace entry
} // namespace gomros
