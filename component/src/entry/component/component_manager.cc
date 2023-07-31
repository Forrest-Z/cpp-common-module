
#include <vector>

#include "../params_define.h"
#include "../params_define.h"
#include "common/file_utils.h"
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

  for (auto& f : file_paths) {
    std::string str_buf;
    gomros::entry::ProductCfgTypedef temp;
    std::string file_name = f + "/" + PRODUCT_CONFIG_FILENAME;
    if (!gomros::common::FileUtils::ReadSmallFile(file_name, str_buf)) {
      LOG_ERROR("read failed !!! file = %s ", file_name.c_str());
    }
    gomros::common::DataBuf buf;
    buf.From(str_buf.data(), str_buf.size(), 1);

    if (!gomros::serialize::utils::decode(GOMROS_SERIAL_XML, buf, temp)) {
      LOG_ERROR("decode failed !!! file = %s ", file_name.c_str());
    }

    buf.Free();

    // 合并写入   product_cfg;
    if (product_cfg == nullptr) {  // 第一个直接写入，后面的替换key val
      product_cfg = new ProductCfgTypedef(temp);
    } else {
      for (auto& i : temp.processes) {
        for (auto& j : product_cfg->processes) {  // 遍历process
          if (i.name == j.name) {
            for (auto& k : i.component) {
              for (auto& l : j.component) {  // 遍历 component
                if (k.running_name == l.running_name) {
                  for (auto& fix : k.fixed_keyval_map) {
                    l.fixed_keyval_map.insert({fix.first, fix.second});
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  end_sem = std::make_shared<gomros::threadpool::Semaphore>(0);
}

void ComponentManager::Init(
    const std::string& process_name,
    std::map<std::string, std::vector<std::string>>& cmd_map) {
  Init(cmd_map);
  this->process_name = process_name;

  //
  std::vector<std::string> file_paths;
  SearchFile::Instance().GetFilePaths(COMPONENT_CONFIG_FILENAME, file_paths);

  for (auto& f : file_paths) {
    std::string str_buf;
    gomros::entry::ComponentCfgTypedef temp;
    std::string file_name = f + "/" + COMPONENT_CONFIG_FILENAME;
    if (!gomros::common::FileUtils::ReadSmallFile(file_name, str_buf)) {
      LOG_ERROR("read failed !!! file = %s ", file_name.c_str());
      break;
    }
    gomros::common::DataBuf buf;
    buf.From(str_buf.data(), str_buf.size(), 1);

    if (!gomros::serialize::utils::decode(GOMROS_SERIAL_XML, buf, temp)) {
      LOG_ERROR("decode failed !!! file = %s ", file_name.c_str());
      break;
    }

    buf.Free();

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
  for (auto& process : product_cfg->processes) {
    if (process.name == process_name) {
      for (auto& comp : process.component) {
        this->component_list.push_back(new ComponetImpl(comp));
      }

      break;
    }
  }

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
