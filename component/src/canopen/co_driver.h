
#pragma once

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
  virtual int Recv(uint32_t& id, uint8_t& len, uint8_t* data) {}

  virtual int Send(const uint32_t& id, const uint8_t& len,
                   const uint8_t* data) {}

  virtual uint32_t AddFlag(uint32_t id, bool RTR = false, bool EFF = false,
                           bool ERR = false) {}

  virtual uint32_t Mask(uint32_t id, bool SFF = true, bool EFF = true) {}
};

}  // namespace canopen
