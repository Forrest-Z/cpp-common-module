/**
 * @file componet_impl.cc
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */
#include "componet_impl.h"
#include "../entry/config_struct.h"
#include "../entry/params_define.h"
#include "common/file_utils.h"
#include "component_config.h"
#include "component_manager.h"
#include "entry/componet.h"
#include "log/log.h"
#include "threadpool.h"

namespace gomros {
namespace entry {

ComponetImpl::ComponetImpl(const ComponentFixCfgTypedef &comp_fix_cfg) {
  name = comp_fix_cfg.name;
  running_name = comp_fix_cfg.running_name;

  ComponentManager::Instance().GetComponentPath(comp_fix_cfg.name,
                                                component_path);
  ComponentManager::Instance().GetDataPath(this->data_path);

  if (component_path == "") {
    LOG_ERROR("cant find comp %s ", comp_fix_cfg.name.c_str());
    exit(0);
  }

  LOG_DEBUG("component_path %s ", component_path.c_str());

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

  ((ComponetConfigImpl *)cfg)->Init(temp, comp_fix_cfg);

  threadpool = new ThreadPoolImpl();

  // 加载入口函数，如果没有则为默认函数
  DynamicLoad::LoadEntryFunc(component_path + "/lib/lib" + name + ".so",
                             &func_list);

  // 将当前组件路径添加到环境变量
  DynamicLoad::AddEnv("LD_LIBRARY_PATH", component_path + "/lib");
}

} // namespace entry
} // namespace gomros