
#include <gtest/gtest.h>
#include "serialize/streambase.hpp"

typedef struct PosType {
  int x;
  int y;
  std::string name;
} PosType;

GPACK(PosType, true, x, y, name);

TEST(serialize, xml) {
  PosType pos = {1, 5, "pos"};
  gomros::serialize::databuf buf;

  try {
    gomros::serialize::utils::decode(GOMROS_SERIAL_XML, buf, pos);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // std::string xml_str(buf.buf, buf.datalen);
  // std::cout << xml_str << std::endl;
}