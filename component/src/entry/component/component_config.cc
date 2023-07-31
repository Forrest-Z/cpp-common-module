
#include "entry/componet.h"
#include "../config_struct.h"

namespace gomros {
namespace entry {

class ComponetConfigImpl : public ComponetConfig {
 public:
  virtual bool GetConfig(const std::string& key, std::string& val) {}

  virtual bool GetConfig(gomros::common::StringUtils::ParamsType& params) {}

  virtual bool SetConfig(gomros::common::StringUtils::ParamsType& params) {}

  // 找其他 配置文件
  virtual bool ReadAndMergeConfigFile(
      const std::string& filename,
      gomros::common::StringUtils::ParamsType& params) {

        
      }

  // template <typename A>
  // bool ReadConfigFile(std::string filename, A& out); // 按优先级找到一个文件
  // 序列化

 private:
  gomros::entry::ComponentCfgTypedef cfg;
};

}  // namespace entry
}  // namespace gomros
