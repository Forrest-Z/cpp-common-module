

#pragma once 

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "co_driver.h"
#include "co_slave.h"

namespace canopen {

class CoMaster {
  friend CoSlave;

 public:
  CoMaster(std::shared_ptr<CoDriver> driver) : driver(driver) {}

  bool AddSlave(std::shared_ptr<CoSlave> slave);

  void Run();

 private:
  std::mutex mtx;
  bool is_alive = true;

  std::shared_ptr<CoDriver> driver;

  std::map<uint32_t, std::shared_ptr<CoSlave>> slaves;
};

}  // namespace canopen
