
#include <gtest/gtest.h>
#include "common/data_buf.h"
#include "serialize/streambase.hpp"
typedef struct PosType {
  int x;
  int y;
  std::string name;
} PosType;

GPACK(PosType, false, x, y, name);

TEST(serialize, xml) {
  PosType pos = {1, 5, "pos"};
  gomros::common::DataBuf buf;

  std::cout << "---------------start-------------------" << std::endl;

  try {
    gomros::serialize::utils::encode(pos, GOMROS_SERIAL_XML, buf);
    std::string xml_str(buf.buf, buf.datalen);
    std::cout << "----------------------------------" << std::endl;
    std::cout << xml_str << std::endl;
    buf.Free();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // std::string xml_str(buf.buf, buf.datalen);
  // std::cout << xml_str << std::endl;
}