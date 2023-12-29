#include "co_slave.h"

#include <gtest/gtest.h>

#include "co_master.h"
#include "linux_can.h"

using namespace canopen;

class CoDriverDemo : public CoDriver {
 public:
  CoDriverDemo() { this->can = std::make_shared<LinuxCan>("can0"); }

  void Init(std::vector<std::tuple<uint32_t, std::vector<uint8_t>>>& buff) {
    this->buff = buff;
  }

  virtual uint32_t AddFlag(uint32_t id, bool RTR = false, bool EFF = false,
                           bool ERR = false) {
    return can->AddFlag(id, RTR, EFF, ERR);
  }

  virtual uint32_t Mask(uint32_t id, bool SFF = true, bool EFF = true) {
    return can->Mask(id, SFF, EFF);
  }

  int Recv(uint32_t& id, uint8_t& len, uint8_t* data) {
    sleep(1);
    if (index < buff.size()) {
      auto d1 = std::get<0>(buff[index]);
      auto d2 = std::get<1>(buff[index]);
      index++;

      id = d1;
      len = std::min((std::size_t)len, d2.size());
      memcpy(data, d2.data(), len);

      {
        std::stringstream ss;
        ss << " recv " << std::hex << id << " : ";

        for (size_t i = 0; i < len; i++) {
          ss << std::hex << (int)data[i] << "  ";
        }

        std::cout << ss.str() << std::endl;
        return 0;
      }

    } else {
      index = 0;
      return -1;
    }
  }

  int Send(const uint32_t& id, const uint8_t& len, const uint8_t* data) {
    std::stringstream ss;

    ss << " send " << std::hex << id << " : ";

    for (size_t i = 0; i < len; i++) {
      ss << std::hex << (int)data[i] << "  ";
    }

    std::cout << std::hex << ss.str() << std::endl;
    can->Send(id, len, data);
  }

 private:
  int index = 0;
  std::vector<std::tuple<uint32_t, std::vector<uint8_t>>> buff;
  std::shared_ptr<LinuxCan> can;
};

class Motor : public canopen::CoSlave {
 public:
  Motor(std::shared_ptr<canopen::CoDriver> driver, uint32_t node_id)
      : CoSlave(driver, node_id) {}

 protected:
  virtual void RecvTpdo1(const uint8_t len, uint8_t* data) {
    int32_t speed = 0;
    speed = LittleEndianRead<int32_t>(data);

    printf("RecvTpdo1 : speed = %d \n\n", speed);
  }
};

TEST(canopen, coslave_recv) {
  printf("-----------test start------------\n");
  auto driver = std::make_shared<CoDriverDemo>();
  std::vector<std::tuple<uint32_t, std::vector<uint8_t>>> buff;
  buff.push_back({0x185, {0xe8, 0x03, 0x00, 0x00}});
  buff.push_back({0x185, {0x8e, 0x03, 0xFF, 0xFF}});
  driver->Init(buff);

  auto slave = std::make_shared<Motor>(driver, 5);
  auto slave2 = std::make_shared<Motor>(driver, 6);

  CoMaster master(driver);
  master.AddSlave(slave);
  master.AddSlave(slave2);

  master.Run();
}

TEST(canopen, coslave_guard) {
  printf("-----------test start------------\n");
  auto driver = std::make_shared<CoDriverDemo>();
  std::vector<std::tuple<uint32_t, std::vector<uint8_t>>> buff;
  buff.push_back({0x185, {0xe8, 0x03, 0x00, 0x00}});
  buff.push_back({0x185, {0x8e, 0x03, 0xFF, 0xFF}});
  driver->Init(buff);

  auto slave = std::make_shared<Motor>(driver, 5);
  auto slave2 = std::make_shared<Motor>(driver, 6);

  CoMaster master(driver);
  master.AddSlave(slave, true);
  master.AddSlave(slave2, true, 1000);

  master.Run();
}

TEST(canopen, coslave_send) { printf("-----------test start------------\n"); }