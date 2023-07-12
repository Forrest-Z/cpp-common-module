
#include <gtest/gtest.h>

#include <boost/serialization/serialization.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <fstream>
#include <sstream>

#define NAME(a) #a

// 模板递归
template <typename F>
void DTEST(F f) {
  std::cout << f << std::endl;
};

template <typename F, typename... FF>
void DTEST(F f, FF... ff) {
  std::cout << f;
  DTEST(ff...);
};

class gps_position {
 private:
  friend class boost::serialization::access;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& degrees;
    ar& minutes;
    ar& seconds;
  }
  int degrees;
  int minutes;
  float seconds;

 public:
  gps_position(){};
  gps_position(int d, int m, float s) : degrees(d), minutes(m), seconds(s) {}
};

class bus_stop {
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    ar& latitude;
    ar& longitude;
  }
  gps_position latitude;
  gps_position longitude;

 protected:
  bus_stop(const gps_position& lat_, const gps_position& long_)
      : latitude(lat_), longitude(long_) {}

 public:
  bus_stop() {}
  // See item # 14 in Effective C++ by Scott Meyers.
  // re non-virtual destructors in base classes.
  virtual ~bus_stop() {}
};

TEST(temp, serialize) {
  DTEST(5, 6, "abcdef");
  std::string s_test;
  std::cout << "string max : " << s_test.max_size() / 1024 / 1024 / 1024
            << " GB" << std::endl;
  // create and open a character archive for output
  std::stringstream ofs;

  std::cout << NAME(ofc) << std::endl;

  // create class instance
  const gps_position g(35, 59, 24.567f);
  bus_stop b;

  // save data to archive
  {
    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << g;
    // std::cout << ofs.str().size() << std::endl;
    std::cout << ofs.str() << std::endl;

    // archive and stream closed when destructors are called
  }

  // ... some time later restore the class instance to its orginal state
  gps_position newg;
  {
    // create and open an archive for input
    std::stringstream ifs(ofs.str());
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> newg;
    // archive and stream closed when destructors are called
  }
}

TEST(temp, str) {
  std::string s =
      "B@\x90\x03\x08 "
      "\x1c\x83@&\x02q\x00\x00\x00\x00@\x00\x01\x00@"
      "\x08D\x14\x820\x100\x04b\x10`!\x13d\x00C\x00@A\x05H\x14\x06\x1a$"
      "\x05\x18\x14d\x81\xa0\x0e\x10\x01IH\x00\x80\x04\x00\x10\x02\x00\xb0!"
      "HPP\x01*a\x80\x90!\x11sB\x060\x00\x00\x06\x14\x01\x00("
      "\xc1\x06\x02\x00\xcc\x81CA\x00\x19P\x10\x14\x10S\x01\x04("
      "\x04D\xc1B\x12\x11\x10\xb8`\x05\x05\x00)\xc4\x12 \n";

      for (auto&c:s)
      {
        std::cout << std::hex << (uint8_t)c;
      }
      

  
}
