#include "co_master.h"

namespace canopen {

bool CoMaster::AddSlave(std::shared_ptr<CoSlave> slave) {
  std::lock_guard<std::mutex> lck(this->mtx);
  if (this->slaves.count(slave->GetNodeId())) {
    return false;
  } else {
    this->slaves.insert({slave->GetNodeId(), slave});
  }
}

void CoMaster::Run() {
  uint32_t frame_id;
  uint8_t data[8];
  uint8_t len;

  while (is_alive) {
    len = 8;
    if (this->driver->Recv(frame_id, len, data) != 0) {
      continue;
    }

    uint32_t node_id_temp = frame_id & 0x7f;
    std::shared_ptr<CoSlave> slave;

    {
      std::lock_guard<std::mutex> lck(this->mtx);
      if (this->slaves.count(node_id_temp)) {
        slave = this->slaves[node_id_temp];
      } else {
        continue;
      }
    }
    slave->HandleFrame(frame_id, len, data);
  }
}

}  // namespace canopen