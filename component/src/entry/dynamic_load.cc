
#include "dynamic_load.h"
#include "entry/componet.h"
#include "log/log.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

namespace gomros {
namespace entry {

bool DynamicLoad::LoadEntryFunc(std::string ld_path, ComponentFunc *func_list) {
  void *handle = dlopen(ld_path.c_str(), RTLD_LAZY);

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

}  // namespace entry
}  // namespace gomros
