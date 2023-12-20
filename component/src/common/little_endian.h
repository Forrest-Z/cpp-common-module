#pragma once

#include <string>
#include <vector>

namespace gomros {
namespace common {
template <class T>
static void LittleEndianWrite(uint8_t *pos, const T &data) {
  size_t size = sizeof(data);
  for (size_t i = 0; i < size; i++) {
    pos[i] = (uint8_t)(data >> 8 * i);
  }
}

template <class T>
static T LittleEndianRead(const uint8_t *pos) {
  size_t size = sizeof(T);
  uint32_t temp = 0x0;
  for (size_t i = 0; i < size; i++) {
    temp |= (pos[i] << i * 8);
  }
  return *((T *)&temp);
}
}  // namespace common
}  // namespace gomros