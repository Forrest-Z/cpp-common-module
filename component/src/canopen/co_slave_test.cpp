#include "co_slave.h"

#include <gtest/gtest.h>

class Motor : public canopen::CoSlave {
  Motor(std::shared_ptr<canopen::CoDriver> driver, uint32_t node_id)
      : CoSlave(driver, node_id) {}
};

TEST(canopen, coslave) { printf("-----------test start------------\n"); }