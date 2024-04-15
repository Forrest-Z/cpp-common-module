#include "clv602_protocol.h"

namespace gomros {
namespace device {
Clv602Protocol::Clv602Protocol(const std::string head, const std::string rear,
                               const std::string noread)
    : head(head), rear(rear), noread(noread) {}

Clv602Protocol::RetType Clv602Protocol::Process(const char* data, int size,
                                                std::string& result) {
  buff += std::string(data, size);

  int indexh = buff.find(head);
  if (indexh != std::string::npos) {
    readhead = true;
  }

  int indexr = buff.find(rear);
  if (readhead && (indexr != std::string::npos)) {
    readrear = true;
  }
  if (readhead && readrear) {
    result = buff.substr(indexh + 1, (indexr - indexh - 1));
    buff = buff.substr(indexr + 1);
    readhead = false;
    readrear = false;

    if (result == noread) {
      return RetType::NoRead;
    } else {
      return RetType::ReadSuccess;
    }
  } else if (readhead) {
    buff = buff.substr(indexh);
    return RetType::ProcessFail;
  } else {
    readhead = false;
    readrear = false;

    buff = "";
    return RetType::ProcessFail;
  }
}

}  // namespace device
}  // namespace gomros
