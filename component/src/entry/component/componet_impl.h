
#pragma once

#include "../dynamicload/dynamic_load.h"
#include "entry/componet.h"
#include "../config_struct.h"

namespace gomros {
namespace entry {

class ComponetImpl : public Componet {
 public:
  ComponetImpl(gomros::entry::ComponentFixCfgTypedef& comp_fix_cfg) {
    // cfg = new
    // threadpool = new

    // dynamic load
    // func list
  }

   ~ComponetImpl() {}

  virtual std::string GetName() { return ""; }
  virtual std::string GetPath() { return ""; }

  void Init() { func_list.init(this); }

  void Uninit() { func_list.uninit(this); }

 private:
  std::string name;
  std::string running_name;

  gomros::entry::ComponentCfgTypedef cfg;

  ComponentFunc func_list;
};

}  // namespace entry
}  // namespace gomros