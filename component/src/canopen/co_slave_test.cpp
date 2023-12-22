#include "co_slave.h"

#include <gtest/gtest.h>

using namespace canopen;

class CoDriverDemo : public CoDriver {
 public:
  void Init(std::vector<std::tuple<uint32_t, std::vector<uint8_t>>>& buff) {
    this->buff = buff;
  }

  int Recv(uint32_t& id, uint8_t& len, uint8_t* data) {
    if (index < buff.size()) {
      auto d1 = std::get<0>(buff[index]);
      auto d2 = std::get<1>(buff[index]);

      id = d1;
      len = std::min((std::size_t)len, d2.size());
      memcpy(data, d2.data(), len);

      {
        std::stringstream ss;
        ss << " recv " << std::hex << id << " : ";

        for (size_t i = 0; i < len; i++) {
          ss << data[i] << "  ";
        }

        std::cout << ss.str() << std::endl;
      }

    } else {
      index = 0;
    }
  }

  int Send(const uint32_t& id, const uint8_t& len, const uint8_t* data) {
    std::stringstream ss;

    ss << " send " << std::hex << id << " : ";

    for (size_t i = 0; i < len; i++) {
      ss << data[i] << "  ";
    }

    std::cout << ss.str() << std::endl;
  }

 private:
  int index = 0;
  std::vector<std::tuple<uint32_t, std::vector<uint8_t>>> buff;
};

class Motor : public canopen::CoSlave {
  Motor(std::shared_ptr<canopen::CoDriver> driver, uint32_t node_id)
      : CoSlave(driver, node_id) {}
};

TEST(canopen, coslave_recv) { printf("-----------test start------------\n"); }

TEST(canopen, coslave_send) { printf("-----------test start------------\n"); }