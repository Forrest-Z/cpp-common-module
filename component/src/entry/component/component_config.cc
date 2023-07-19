
#include "entry/componet.h"

namespace gomros {
namespace entry {

class ComponetConfigImpl : public ComponetConfig {
 public:
  virtual bool GetConfig(const std::string& key, std::string& val) {}

  virtual bool GetConfig(gomros::common::StringUtils::ParamsType& params) {}

  virtual bool SetConfig(gomros::common::StringUtils::ParamsType& params) {}

  virtual bool ReadAndMergeConfigFile(
      const std::string& filename,
      gomros::common::StringUtils::ParamsType& params) {}


  // template <typename A>
  // bool ReadConfigFile(std::string filename, A& out);
};

}  // namespace entry
}  // namespace gomros
