

#include "../src/component/utils/map_utils.h"
#include "common/time_utils.h"
#include "entry/componet.h"
#include "log/log.h"

extern "C" void ComponentInit(Componet* comp) {
  LOG_INFO("ComponentInit \n");
  gomros::common::StringUtils::ParamsType params;
  comp->cfg->GetConfig(params);

  std::string str;
  gomros::entry::map_utils::ToString(params, str);

  LOG_WARN("%s ", str.c_str());

  std::string key = "write_time";
  auto time = gomros::common::TimeUtils::GetFormatDateTime();
  LOG_WARN("time : %s ", time.c_str());

  gomros::entry::map_utils::InsertAndMerge(params, key, time);
  comp->cfg->SetConfig(params);
}

extern "C" void ComponentUninit(Componet* comp) {
  LOG_INFO("ComponentUnInit \n");
}

// objdump -T component/test_data/libdynamic_load_test.so
