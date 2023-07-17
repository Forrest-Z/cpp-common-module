#pragma once

#include <string>
#include <vector>

namespace gomros {
namespace entry {

typedef struct ComponentFixCfgTypedef {
  std::string running_name;
  std::string fixed_keyval_map;  // key1:val1;key2;val2;
} ComponentFixCfgTypedef;

typedef struct ProcessCfgTypedef {
  std::string name;
  std::vector<std::string> component;
} ProcessCfgTypedef;

/**
 * @brief product.xml
 * 
 */
typedef struct ProductCfgTypedef {
  std::string name;
  std::string version;
  std::vector<ProcessCfgTypedef> processes;
} ProductCfgTypedef;

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

}  // namespace entry
}  // namespace gomros
