#pragma once

#include <string>
#include <vector>

namespace gomros {
namespace common {
template <class T>
static void BigEndianWrite(uint8_t *pos, const T &data) {
  size_t size = sizeof(data);
  for (size_t i = 0; i < size; i++) {
    pos[size - i - 1] = (uint8_t)(data >> 8 * i);
  }
}

template <class T>
static T BigEndianRead(const uint8_t *pos) {
  size_t size = sizeof(T);
  uint32_t temp = 0x0;
  for (size_t i = 0; i < size; i++) {
    temp |= (pos[size - i - 1] << i * 8);
  }
  return *((T *)&temp);
}
}  // namespace common
}  // namespace gomros