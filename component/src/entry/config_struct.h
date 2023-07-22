#pragma once

#include <string>
#include <vector>

#include "serialize/streambase.hpp"

namespace gomros {
namespace entry {

typedef struct ComponentFixCfgTypedef {
  std::string name;
  std::string running_name;
  std::string fixed_keyval_map;  // key1:val1;key2;val2;
} ComponentFixCfgTypedef;

GPACK(ComponentFixCfgTypedef, false, running_name, fixed_keyval_map);

typedef struct ProcessCfgTypedef {
  std::string name;
  std::vector<ComponentFixCfgTypedef> component;
} ProcessCfgTypedef;

GPACK(ProcessCfgTypedef, false, name, component);

/**
 * @brief product.xml
 *
 */
typedef struct ProductCfgTypedef {
  std::string name;
  std::string version;
  std::vector<ProcessCfgTypedef> processes;
} ProductCfgTypedef;

GPACK(ProductCfgTypedef, false, name, version, processes);

/**
 * @brief component.xml
 *
 */
typedef struct ComponentCfgTypedef {
  std::string name;
  std::string system_arch;
  std::string brief_info;
  std::string version;

  bool has_entry;  // 是否包含初始化入口

  std::string dependence_component;  // compA;compB;

  std::string keyval_map;  // key1:val1;key2;val2;

} ComponentCfgTypedef;

GPACK(ComponentCfgTypedef, false, name, system_arch, brief_info, version,
      has_entry, dependence_component, keyval_map);

}  // namespace entry
}  // namespace gomros
