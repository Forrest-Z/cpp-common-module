
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
   * @param type {MAC,HardDriveSerial}
   * @param device_id
   * @return true
   * @return false
   */
  bool Get(std::string& device_id, const std::string& type = "MAC");

 private:
  bool GetMac(std::string& mac);
  bool GetALLMac(std::vector<std::string>& mmacAddressesacs);
  std::string GetMACAddress(int sock, const std::string& interfaceName);

 private:
  std::string GetHardDriveName();
  std::string GetHardDriveSerialNumber();
};

}  // namespace common
}  // namespace gomros
