

#include "entry/componet.h"
#include "log/log.h"

extern "C" void ComponentInit(Componet* comp) { LOG_INFO("ComponentInit \n"); }

extern "C" void ComponentUninit(Componet* comp) {
  LOG_INFO("ComponentUnInit \n");
}