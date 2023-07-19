
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

  if (!handle) {
    LOG_ERROR("%s\n", dlerror());
    return false;
  }

  {
    *(void **)(&(func_list->init)) = dlsym(handle, "ComponentInit");
    char *error = dlerror();

    if (error != NULL) {
      LOG_ERROR(" init load error %s\n", dlerror());
      return false;
    }
  }

  {
    *(void **)(&(func_list->uninit)) = dlsym(handle, "ComponentUninit");
    char *error = dlerror();

    if (error != NULL) {
      LOG_ERROR(" uninit load error %s\n", dlerror());
      return false;
    }
  }

  return true;
}

bool DynamicLoad::AddEnv(const std::string &name, const std::string &value) {
  if (setenv(name.c_str(), value.c_str(), 1) != 0) {
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

}  // namespace entry
}  // namespace gomros
