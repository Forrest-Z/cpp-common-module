
#pragma once

#include <string>
#include <vector>

namespace gomros {
namespace common {

class DeviceID {
 public:
  /**
   * @brief
   *
   * @param type {mac,storage_serial}
   * @param device_id
   * @return true
   * @return false
   */
  bool Get(std::string& device_id, const std::string& type = "mac");

 private:
  bool GetMac(std::string& mac);
  bool GetALLMac(std::vector<std::string>& mmacAddressesacs);
  std::string GetMACAddress(int sock, const std::string& interfaceName);
};

}  // namespace common
}  // namespace gomros
