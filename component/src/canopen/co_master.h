

#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "co_driver.h"
#include "co_slave.h"
#include "co_timer.h"

namespace canopen {

class CoMaster {
  friend CoSlave;

 public:
  CoMaster(std::shared_ptr<CoDriver> driver) : driver(driver) {}

  bool AddSlave(std::shared_ptr<CoSlave> slave, bool enable_node_guard = false,
                int32_t interval_ms = 500);

  void Run();

 private:
  void NodeGuard(uint32_t node_id);

 private:
  std::mutex mtx;
  bool is_alive = true;

  CoTimer timer;

  std::shared_ptr<CoDriver> driver;

  std::map<uint32_t, std::shared_ptr<CoSlave>> slaves;
};

}  // namespace canopen
