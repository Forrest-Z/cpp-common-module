
#pragma once

#include "../dynamicload/dynamic_load.h"
#include "entry/componet.h"

namespace gomros {
namespace entry {

class ComponetImpl : public Componet {
 public:
  ComponetImpl(gomros::entry::ComponentFixCfgTypedef& comp_fix_cfg);

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