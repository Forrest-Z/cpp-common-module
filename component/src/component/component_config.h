/**
 * @file component_config.h
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */
#pragma once

#include "../entry/config_struct.h"
#include "./utils/map_utils.h"
#include "component_manager.h"
#include "entry/componet.h"
#include "log/log.h"

namespace gomros {
namespace entry {

class ComponetConfigImpl : public ComponetConfig {
public:
  virtual bool GetConfig(const std::string &key, std::string &val) {
    if (cfg.keyval_map.find(key) != cfg.keyval_map.end()) {
      /* code */
      val = cfg.keyval_map[key];
      return true;
    } else {
      val.clear();
      return false;
    }
  }

  virtual bool GetConfig(gomros::common::StringUtils::ParamsType &params) {
    params = cfg.keyval_map;
    return true;
  }

  virtual bool SetConfig(gomros::common::StringUtils::ParamsType &params) {

    entry::map_utils::InsertAndMerge(fix_cfg.fixed_keyval_map, params);

    // 写入 product.xml fix_cfg ,并更新配置文件
    ComponentManager::Instance().ChangeProductCfg(fix_cfg);
  }

  // 找其他 配置文件
  virtual bool
  ReadAndMergeConfigFile(const std::string &filename,
                         gomros::common::StringUtils::ParamsType &params) {}

  template <typename A>
  static bool ReadConfigFile(std::string filefullname, A &out) {
    std::string str_buf;

    if (!gomros::common::FileUtils::ReadSmallFile(filefullname, str_buf)) {
      LOG_ERROR("read failed !!! file = %s ", filefullname.c_str());
      return false;
    }
    LOG_DEBUG("str_buf_ %s ", str_buf.c_str());
    gomros::common::DataBuf buf;
    buf.From(str_buf.data(), str_buf.size(), 1);

    if (!gomros::serialize::utils::decode(GOMROS_SERIAL_XML, buf, out)) {
      LOG_ERROR("decode failed !!! file = %s ", filefullname.c_str());

      buf.Free();
      return false;
    }

    buf.Free();
    return true;
  }

  template <typename A>
  static bool WriteConfigFile(const std::string &filefullname, const A &in) {
    gomros::common::DataBuf buf;

    gomros::serialize::utils::encode(in, GOMROS_SERIAL_XML, buf);
    std::string xml_str(buf.buf, buf.datalen);
    LOG_DEBUG("xml_str : %s ", xml_str.c_str());

    gomros::common::FileUtils::WriteSmallFile(filefullname, xml_str);

    buf.Free();
  }

  void Init(ComponentCfgTypedef cfg, ComponentFixCfgTypedef fix_cfg) {
    this->cfg = cfg;
    this->fix_cfg = fix_cfg;
    ComponentManager::Instance().GetDataPath(this->data_path);

    // 合并 fix_cfg 中的 key_val_map 到 this->cfg
    map_utils::InsertAndMerge(this->cfg.keyval_map, fix_cfg.fixed_keyval_map);

    std::string str;
    map_utils::ToString(fix_cfg.fixed_keyval_map, str);
    LOG_DEBUG(" %s ", str.c_str());
  }

private:
  gomros::entry::ComponentCfgTypedef cfg;
  ComponentFixCfgTypedef fix_cfg;
  std::string data_path; // 数据目录
};

} // namespace entry
} // namespace gomros
