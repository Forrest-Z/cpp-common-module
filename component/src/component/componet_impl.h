/**
 * @file componet_impl.h
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
#include "./dynamicload/dynamic_load.h"
#include "entry/componet.h"

namespace gomros {
namespace entry {

class ComponetImpl : public Componet {
public:
  ComponetImpl(const ComponentFixCfgTypedef &comp_fix_cfg);

  virtual ~ComponetImpl() {}

  virtual std::string GetRunningName() { return running_name; }
  virtual std::string GetPath() { return data_path; }

  void Init() { func_list.init(this); }

  void Uninit() { func_list.uninit(this); }

private:
  std::string name;
  std::string running_name;
  std::string data_path; // 数据目录

  std::string component_path;

  ComponentFunc func_list;
};

} // namespace entry
} // namespace gomros