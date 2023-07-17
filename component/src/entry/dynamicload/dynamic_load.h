#pragma once
#include "entry/componet.h"

namespace gomros {
namespace entry {

typedef struct ComponentFunc {
  void (*init)(Componet *);
  void (*uninit)(Componet *);
} ComponentFunc;

/**
 * @brief 加载入口函数动态库 ComponentInit  ComponentUninit
 *
 */
class DynamicLoad {
 public:
  static bool LoadEntryFunc(std::string ld_path, ComponentFunc *func_list);

  // 添加环境
  static bool AddEnv(const std::string &name, std::string &value);
};

}  // namespace entry
}  // namespace gomros
