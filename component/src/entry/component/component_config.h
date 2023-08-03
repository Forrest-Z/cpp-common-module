
#pragma once

#include "../config_struct.h"
#include "entry/componet.h"

namespace gomros {
namespace entry {

class ComponetConfigImpl : public ComponetConfig {
 public:
  virtual bool GetConfig(const std::string& key, std::string& val) {
    if (cfg.keyval_map.find(key) != cfg.keyval_map.end()) {
      /* code */
      val = cfg.keyval_map[key];
      return true;
    } else {
      val.clear();
      return false;
    }

  }

  virtual bool GetConfig(gomros::common::StringUtils::ParamsType& params) {
    params = cfg.keyval_map;
    return true;
  }

  virtual bool SetConfig(gomros::common::StringUtils::ParamsType& params) {

    // 写入 product.xml fix_cfg ,并更新配置文件
  }

  // 找其他 配置文件
  virtual bool ReadAndMergeConfigFile(
      const std::string& filename,
      gomros::common::StringUtils::ParamsType& params) {}

  // template <typename A>
  // bool ReadConfigFile(std::string filename, A& out); // 按优先级找到一个文件
  // 序列化

  void Init(ComponentCfgTypedef cfg, ComponentFixCfgTypedef fix_cfg) {
    this->cfg = cfg;

    // 合并 fix_cfg
  }

 private:
  gomros::entry::ComponentCfgTypedef cfg;
};

}  // namespace entry
}  // namespace gomros
