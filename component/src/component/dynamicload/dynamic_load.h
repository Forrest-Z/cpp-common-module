/**
 * @file dynamic_load.h
 * @author 童汉森 (ths)
 * @brief 
 * @version 1.0
 * @date 2023-07-15
 * 
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 * 
 */
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

  // 添加环境变量 只对当前进程生效
  static bool AddEnv(const std::string &name, const std::string &value);
};

}  // namespace entry
}  // namespace gomros
