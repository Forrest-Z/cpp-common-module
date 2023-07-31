
#pragma once

#include "../config_struct.h"
#include "../dynamicload/dynamic_load.h"
#include "component_config.h"
#include "component_manager.h"
#include "entry/componet.h"
#include "log/log.h"
#include "threadpool.h"

namespace gomros {
namespace entry {

class ComponetImpl : public Componet {
 public:
  ComponetImpl(gomros::entry::ComponentFixCfgTypedef& comp_fix_cfg) {
    name = comp_fix_cfg.name;
    running_name = comp_fix_cfg.running_name;

    ComponentManager::Instance().GetComponentPath(comp_fix_cfg.name,
                                                  component_path);

    std::string str_buf;
    gomros::entry::ComponentCfgTypedef temp;
    std::string file_name = component_path + "/" + COMPONENT_CONFIG_FILENAME;
    if (!gomros::common::FileUtils::ReadSmallFile(file_name, str_buf)) {
      LOG_ERROR("read failed !!! file = %s ", file_name.c_str());
    }
    gomros::common::DataBuf buf;
    buf.From(str_buf.data(), str_buf.size(), 1);

    if (!gomros::serialize::utils::decode(GOMROS_SERIAL_XML, buf, temp)) {
      LOG_ERROR("decode failed !!! file = %s ", file_name.c_str());
    }

    buf.Free();

    cfg = new ComponetConfigImpl();

    ((ComponetConfigImpl*)cfg)->Init(temp, comp_fix_cfg);

    threadpool = new ThreadPoolImpl();

    // 加载入口函数，如果没有则为默认函数
    DynamicLoad::LoadEntryFunc(component_path + "/lib/lib" + name + ".so",
                               &func_list);

    // 将当前组件路径添加到环境变量
    DynamicLoad::AddEnv("LD_LIBRARY_PATH", component_path + "/lib");
  }

  ~ComponetImpl() {}

  virtual std::string GetName() { return name; }
  virtual std::string GetPath() { return data_path; }

  void Init() { func_list.init(this); }

  void Uninit() { func_list.uninit(this); }

 private:
  std::string name;
  std::string running_name;
  std::string data_path;  // 数据目录

  std::string component_path;

  ComponentFunc func_list;
};

}  // namespace entry
}  // namespace gomros