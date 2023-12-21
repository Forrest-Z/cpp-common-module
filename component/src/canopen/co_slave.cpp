#include "co_slave.h"

namespace canopen {

void CoSlave::HandleFrame(uint32_t& id, uint8_t& len, uint8_t* data) {
  if (id - 0x180 == this->node_id) {
    RecvTpdo1(len, data);
  } else if (id - 0x280 == this->node_id) {
    RecvTpdo2(len, data);
  } else if (id - 0x380 == this->node_id) {
    RecvTpdo3(len, data);
  } else if (id - 0x480 == this->node_id) {
    RecvTpdo4(len, data);
  } else if (id - 0x580 == this->node_id) {
    RecvTsdo(len, data);
  }
}

void CoSlave::RecvTsdo(const uint8_t len, uint8_t* data) {
  std::lock_guard<std::mutex> lck(this->mtx);

  this->tsdo.clear();
  for (size_t i = 0; i < len; i++) {
    this->tsdo.push_back(data[i]);
  }
  this->tsdo_cv.notify_one();
}

}  // namespace canopen
