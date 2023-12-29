#include "co_master.h"

namespace canopen {

bool CoMaster::AddSlave(std::shared_ptr<CoSlave> slave, bool enable_node_guard,
                        int32_t interval_ms) {
  std::lock_guard<std::mutex> lck(this->mtx);
  if (this->slaves.count(slave->GetNodeId())) {
    return false;
  } else {
    this->slaves.insert({slave->GetNodeId(), slave});

    if (enable_node_guard) {
      this->timer.AddTask(
          std::string("NodeGuard-") + std::to_string(slave->node_id),
          std::bind(&CoMaster::NodeGuard, this, slave->node_id), interval_ms);
    }
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

void CoMaster::NodeGuard(uint32_t node_id) {
  this->driver->Send(driver->AddFlag((0x700 + node_id), true), 0, nullptr);
}

}  // namespace canopen