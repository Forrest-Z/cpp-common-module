/**
 * @file dynamic_load.cc
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */
#include "dynamic_load.h"
#include "entry/componet.h"
#include "log/log.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

namespace gomros {
namespace entry {

static void ComponentVoid(Componet *) { LOG_WARN("component void . \n"); }

bool DynamicLoad::LoadEntryFunc(std::string ld_path, ComponentFunc *func_list) {
  void *handle = dlopen(ld_path.c_str(), RTLD_LAZY);
  func_list->init = ComponentVoid;
  func_list->uninit = ComponentVoid;

  LOG_DEBUG("ldpath : %s", ld_path.c_str());

  if (!handle) {
    LOG_ERROR("%s\n", dlerror());
    return false;
  }

  {
    *(void **)(&(func_list->init)) = dlsym(handle, "ComponentInit");
    char *error = dlerror();

    if (error != NULL) {
      LOG_ERROR(" init load error %s\n", dlerror());
      func_list->init = ComponentVoid;
      return false;
    }
  }

  {
    *(void **)(&(func_list->uninit)) = dlsym(handle, "ComponentUninit");
    char *error = dlerror();

    if (error != NULL) {
      LOG_ERROR(" uninit load error %s\n", dlerror());
      func_list->uninit = ComponentVoid;
      return false;
    }
  }

  return true;
}

bool DynamicLoad::AddEnv(const std::string &name, const std::string &value) {

  std::string pre_evn;

  {
    char *var_value = std::getenv(name.c_str());
    if (var_value != nullptr) {
      LOG_INFO("pre Environment variable %s is : %s  .\n", name.c_str(),
               var_value);
      pre_evn = var_value;
    } else {
      LOG_ERROR("Environment variable %s is not set.\n", name.c_str());
    }
  }

  // set env
  std::string set_evn;
  if (pre_evn == "") {
    set_evn = value;
  } else {
    set_evn = pre_evn;
    set_evn += ":";
    set_evn += value;
  }

  if (setenv(name.c_str(), set_evn.c_str(), 1) != 0) {
    LOG_ERROR("Failed to set environment variable.\n");
    return false;
  }

  // 获取并打印设置的环境变量
  char *var_value = std::getenv(name.c_str());
  if (var_value != nullptr) {
    LOG_INFO("Environment variable %s  is set to: %s .\n", name.c_str(),
             var_value);
  } else {
    LOG_ERROR("Environment variable %s is not set.\n", name.c_str());
  }

  return true;
}

} // namespace entry
} // namespace gomros
