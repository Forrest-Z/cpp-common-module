
#include "linux_can.h"

#include <gtest/gtest.h>

TEST(linuxcan, can) {
  LinuxCan can("can0");
  LinuxCan can1("can0");

  uint8_t data[8];
  can.Send(0x111, 6, data);
  can1.Send(0x111, 6, data);
  {
    uint32_t id;
    uint8_t len;
    can.Recv(id, len, data);

    printf("recv : id = %u , len = %u \n", id, len);
    EXPECT_EQ(id, 0x111);
    EXPECT_EQ(len, 6);
  }
}