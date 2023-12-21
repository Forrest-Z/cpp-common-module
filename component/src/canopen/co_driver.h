

#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace canopen {

template <class T>
static void LittleEndianWrite(uint8_t* pos, const T& data) {
  size_t size = sizeof(data);
  for (size_t i = 0; i < size; i++) {
    pos[i] = (uint8_t)(data >> 8 * i);
  }
}

template <class T>
static T LittleEndianRead(const uint8_t* pos) {
  size_t size = sizeof(T);
  uint32_t temp = 0x0;
  for (size_t i = 0; i < size; i++) {
    temp |= (pos[i] << i * 8);
  }
  return *((T*)&temp);
}

class CoDriver {
 public:
  int Recv(uint32_t& id, uint8_t& len, uint8_t* data);

  int Send(const uint32_t& id, const uint8_t& len, const uint8_t* data);
};

class CoDriverDemo : public CoDriver {
 public:
  void Init(std::vector<std::tuple<uint32_t, std::vector<uint8_t>>>& buff) {
    this->buff = buff;
  }

  int Recv(uint32_t& id, uint8_t& len, uint8_t* data) {
    if (index < buff.size()) {
      auto& [d1, d2] = buff[++index];

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

}  // namespace canopen
