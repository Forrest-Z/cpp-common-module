#pragma once
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include "common/data_buf.h"
#include "macrohelpers.h"

#define GOMROS_SERIAL_DEFAULT 0
#define GOMROS_SERIAL_JSON 1
#define GOMROS_SERIAL_XML 2
#define GOMROS_SERIAL_ROS 3
using namespace std;
namespace gomros {
namespace serialize {
class encoder;
class decoder;
}
}
template <typename T>
extern bool s_simple(const T &obj);
template <typename T>
extern void s_encode(const T &obj, const char *key,
                     gomros::serialize::encoder *coder);
template <typename T>
extern bool s_decode(T &obj, const char *key,
                     gomros::serialize::decoder *decoder);

namespace gomros {
namespace serialize {

/**
 * @brief 序列化操作类
 * 将不同类型的数据进行序列化，支持XML,JSON,二进制格式
*/
class encoder {
 public:
  encoder() {}
  virtual ~encoder() {}

  /**
   * @brief 获取序列化对象格式 xml json格式 二进制格式
   * @return 对应类型的标示
  */
  virtual int format() { return 0; }

  /**
   * @brief 将序列化的数据输出
   * @param buf 结果存储变量
  */
  virtual void result(gomros::common::DataBuf &buf) {}

  /**
   * @brief 获取序列化格式 xml json格式 二进制格式
   * @return 对应类型的标示
  */
  int GetType();

  /**
   * @brief 判断数据类型是否是简单定长类型
   * @return true 定长数据
   * @return false 不定长数据
  */
  template <typename T>
  bool simple(T &obj) {
    return s_simple(obj);
  }

 public:
  /**
   * @brief 开始object数据 序列化
   * @param key 对应键值
  */
  virtual void beginobject(const char *key) {}

  /**
   * @brief 结束object 序列化
  */
  virtual void endobject() {}

  /**
   * @brief 开始数组数据 序列化
   * @param key 对应键值
  */
  virtual void beginarray(const char *key) {}

  /**
   * @brief 结束数组数据 序列化
  */
  virtual void endarray() {}

  /**
   * @brief 开始list数据 序列化
   * @param key 对应键值
   * @param count list数据数量
  */
  virtual void beginlist(const char *key, int count) {}

  /**
   * @brief 结束list数据 序列化
  */
  virtual void endlist() {}

  /**
   * @brief 开始map数据 序列化
   * @param key 对应键值
   * @param count map数据数量
  */
  virtual void beginmap(const char *key, int count) {}

  /**
   * @brief 结束map数据 序列化
  */
  virtual void endmap() {}

  /**
   * @brief 向缓冲区中写入数据
   * @param buf 准备写入的数据
   * @param len 写入的长度
  */
  virtual void addbuf(const char *buf, int len) {}

 public:
  char error_code = 0;

 public:
  /**
   * @brief const bool 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const bool &o) {}

  /**
   * @brief const char 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const char &o) {}

  /**
   * @brief const int 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const int &o) {}

  /**
   * @brief const float 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const float &o) {}

  /**
   * @brief const double 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const double &o) {}

  /**
   * @brief const string 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const std::string &o) {}

  /**
   * @brief const int8_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const int8_t &o) {}
  /**
   * @brief const int16_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const int16_t &o) {}

  /**
   * @brief const int64_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const int64_t &o) {}

  /**
   * @brief const uint8_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const uint8_t &o) {}
  /**
   * @brief const uint16_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const uint16_t &o) {}

  /**
   * @brief const uint32_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const uint32_t &o) {}

  /**
   * @brief const uint64_t 类型数据的序列化
   * @param key 对应的键值
   * @param o 写入的数据
  */
  virtual void encode(const char *key, const uint64_t &o) {}

  // /**
  //  * @brief string 类型数据的序列化
  //  * @param key 对应的键值
  //  * @param o 写入的数据
  // */
  // void encode(const char *key, std::string & o);

  /**
   * @brief char 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const char (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len);
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief int 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const int (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(int));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief int16_t 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const int16_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(int16_t));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief int64_t 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const int64_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(int64_t));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief uint8_t 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const uint8_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(uint8_t));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief uint16_t 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const uint16_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(uint16_t));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief uint32_t 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const uint32_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(uint32_t));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief uint64_t 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const uint64_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(uint64_t));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief float 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const float (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(float));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief double 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const double (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      addbuf((char *)arr, len * sizeof(double));
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief string 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <size_t N>
  void encode(const char *key, const std::string (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      for (int i = 0; i < len; i++) encode("", arr[i]);
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) {
      encode("item", arr[i]);
    }
    endarray();
  }

  /**
   * @brief 自定义结构 数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <typename T>
  void encode(const char *key, const T &o) {
    if (format() == 0) {
      int len = sizeof(T);
      if (s_simple(o) == true) {
        addbuf((char *)&o, len);
      } else {
        s_encode(o, key, this);
      }
      return;
    }
    const char *tKey = "item";
    if (strcmp(key, "") == 0) {
      s_encode(o, tKey, this);
    } else
      s_encode(o, key, this);
  }

  /**
   * @brief 自定义结构 数组数据的序列化
   * @param key 对应的键值
   * @param arr 写入的数组数据
  */
  template <typename T, size_t N>
  void encode(const char *key, const T (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) return;
      if (s_simple(arr[0]) == true) {
        addbuf((char *)arr, sizeof(arr));
      } else {
        for (int i = 0; i < len; i++) {
          s_encode(arr[i], "", this);
          // encode("",arr[i]);
        }
      }
      return;
    }

    beginarray(key);
    for (size_t i = 0; i < N; i++) encode("item", arr[i]);
    endarray();
  }

  /**
  * \brief vector<char> 类型数据序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<char> &val);

  /**
  * \brief vector<int> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<int> &val);

  /**
  * \brief vector<int8_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<int8_t> &val);

  /**
  * \brief vector<int16_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<int16_t> &val);

  /**
  * \brief vector<int64_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<int64_t> &val);

  /**
  * \brief vector<uint8_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<uint8_t> &val);

  /**
  * \brief vector<uint16_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<uint16_t> &val);

  /**
  * \brief vector<uint32_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<uint32_t> &val);

  /**
  * \brief vector<uint64_t> 类型数据的序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<uint64_t> &val);

  /**
  * \brief vector<float> 类型数据序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<float> &val);

  /**
  * \brief vector<double> 类型数据序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<double> &val);

  /**
  * \brief vector<string> 类型数据序列化
  * \param val 待序列化数据
  */
  void encode(const char *key, const std::vector<std::string> &val);

  /**
  * \brief vector<T> 自定义类型数据序列化
  * \param val 待序列化数据
  */
  template <typename T>
  void encode(const char *key, const std::vector<T> &val) {
    int count = val.size();
    beginlist(key, count);
    if (count > 0) {
      if (format() == 0) {
        int len = count;
        const T &first = val[0];
        if (s_simple(first) == true) {
          addbuf((char *)&first, sizeof(T) * len);
        } else {
          for (size_t i = 0; i < count; i++) s_encode(val[i], key, this);
        }
      } else {
        for (size_t i = 0; i < count; i++) encode("item", val[i]);
      }
    }
    endlist();
  }

  /**
   * @brief 自定义类型 list数据 序列化
   * @param key 对应键值
   * @param val list数据
  */
  template <typename T>
  void encode(const char *key, const std::list<T> &val) {
    beginlist(key, val.size());
    for (auto it = val.begin(); it != val.end(); it++) {
      encode("item", *it);
    }
    endlist();
  }

  /**
   * @brief 自定义类型 map数据 序列化
   * @param key 对应键值
   * @param val map数据
  */
  template <typename K, typename T>
  void encode(const char *key, const std::map<K, T> &val) {
    beginlist(key, val.size());
    for (auto it = val.begin(); it != val.end(); it++) {
      beginobject("");
      encode("key", it.key);
      encode("value", it.value);
      endobject();
    }
    endlist();
  }
};

/**
 * @brief 反序列化操作类
 * 将不同类型的数据进行反序列化，支持XML,JSON,二进制格式
*/
class decoder {
 public:
  decoder() {}
  virtual ~decoder() {}

  /**
   * @brief 获取反序列化对象格式 xml json格式 二进制格式
   * @return 对应类型的标识
  */
  virtual int format() { return 0; }

  /**
   * @brief 从buf中加载要反序列化的数据
   * @return 对应类型的标识
  */
  virtual void from(gomros::common::DataBuf &buf) {}
  int GetType();

  /**
   * @brief 判断数据类型是否是简单定长类型
   * @return true 定长数据
   * @return false 不定长数据
  */
  template <typename T>
  bool simple(T &obj) {
    return s_simple(obj);
  }

 public:
  /**
   * @brief 开始object数据 反序列化
   * @param key 对应键值
  */
  virtual void de_beginobject(const char *key) {}

  /**
   * @brief 结束object数据 反序列化
  */
  virtual void de_endobject() {}

  /**
   * @brief 开始array数据 反序列化
   * @param key 对应键值
  */
  virtual void de_beginarray(const char *key) {}

  /**
   * @brief 结束array数据 反序列化
  */
  virtual void de_endarray() {}

  /**
   * @brief 开始list数据 反序列化
   * @param key 对应键值
   * @param count list包含的数据个数
  */
  virtual void de_beginlist(const char *key, int &count) {}

  /**
   * @brief 结束list数据 反序列化
  */
  virtual void de_endlist() {}

  /**
   * @brief 开始 map 数据 反序列化
   * @param key 对应键值
  */
  virtual void de_beginmap(const char *key, int &count) {}

  /**
   * @brief 结束 map数据 反序列化
  */
  virtual void de_endmap() {}

  /**
   * @brief 读取指定长度的数据
  */
  virtual void readbuf(char *buf, int len) {}

 public:
  char error_code = 0;

 public:
  /**
   * @brief bool 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, bool &o) {}

  /**
   * @brief char 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, char &o) {}

  /**
   * @brief int 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, int &o) {}

  /**
   * @brief int8_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, int8_t &o) {}

  /**
   * @brief int16_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, int16_t &o) {}

  /**
   * @brief int64_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, int64_t &o) {}

  /**
   * @brief uint8_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, uint8_t &o) {}

  /**
   * @brief uint16_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, uint16_t &o) {}

  /**
   * @brief uint32_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, uint32_t &o) {}

  /**
   * @brief uint64_t 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, uint64_t &o) {}

  /**
   * @brief float 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, float &o) {}

  /**
   * @brief double 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, double &o) {}

  /**
   * @brief string 类型数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  virtual bool decode(const char *key, std::string &o) {}
  bool decode(const char *key, const std::string &o) {}

  /**
   * @brief 自定义 类型 数据的反序列化
   * @param key 对应的键值
   * @param o 输出的数据
  */
  template <typename T>
  bool decode(const char *key, T &o) {
    if (format() == 0) {
      int len = sizeof(T);
      if (len < 0) {
        return false;
      }
      if (s_simple(o) == true) {
        readbuf((char *)&o, len);
      } else {
        s_decode(o, key, this);
      }
      return true;
    }
    const char *tKey = "item";
    if (strcmp(key, "") == 0) {
      s_decode(o, tKey, this);
    } else
      s_decode(o, key, this);
  }

  /**
   * @brief 固定长度char 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, char (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf(&arr[0], len);
      return true;
    }
    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 int 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, int (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(int));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 int8_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, int8_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(int8_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 int16_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, int16_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(int16_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 int64_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, int64_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(int64_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 uint8_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, uint8_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(uint8_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 uint16_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, uint16_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(uint16_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 uint32_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, uint32_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(uint32_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 uint64_t 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, uint64_t (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(uint64_t));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 float 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, float (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(float));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 double 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, double (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      readbuf((char *)arr, len * sizeof(double));
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 string 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <size_t N>
  bool decode(const char *key, std::string (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      for (int i = 0; i < len; i++) decode("", arr[i]);
      return true;
    }

    de_beginarray(key);
    for (size_t i = 0; i < N; i++) {
      decode("item", arr[i]);
    }
    de_endarray();
  }

  /**
   * @brief 固定长度 自定义类型 数组 数据的反序列化
   * @param key 对应的键值
   * @param arr 输出的数据
   * @param N 数组的长度
  */
  template <typename T, size_t N>
  bool decode(const char *key, T (&arr)[N]) {
    if (format() == 0) {
      int len = N;
      if (len < 0) {
        return false;
      }
      if (s_simple(arr[0]) == true) {
        readbuf((char *)arr, len * sizeof(T));
      } else {
        for (int i = 0; i < len; i++) {
          s_decode(arr[i], "", this);
          // decode("item",arr[i]);
        }
      }
      return true;
    }
    de_beginarray(key);
    for (size_t i = 0; i < N; i++)
      // decode("item",arr[i]);
      s_decode(arr[i], "item", this);
    de_endarray();
  }

  /**
  * @brief vector<char> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<char> &val);

  /**
  * @brief vector<int> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<int> &val);

  /**
  * @brief vector<int16_t> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<int16_t> &val);

  /**
  * @brief vector<int64_t> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<int64_t> &val);

  /**
  * @brief vector<uint8_t> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<uint8_t> &val);

  /**
  * @brief vector<uint16_t> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<uint16_t> &val);

  /**
  * @brief vector<uint32_t> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<uint32_t> &val);

  /**
  * @brief vector<uint64_t> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<uint64_t> &val);

  /**
  * @brief vector<float> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<float> &val);

  /**
  * @brief vector<double> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<double> &val);

  /**
  * @brief vector<string> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  bool decode(const char *key, std::vector<std::string> &val);

  /**
  * @brief 自定义类型T的 vector<T> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  template <typename T>
  bool decode(const char *key, std::vector<T> &val) {
    int count;
    de_beginlist(key, count);
    if (format() == 0) {
      int len = count;
      if (len < 0) {
        return false;
      }
      val.resize(len);
      if (s_simple(val[0]) == true) {
        readbuf((char *)val.data(), len * sizeof(T));
      } else {
        for (size_t i = 0; i < len; i++) s_decode(val[i], key, this);
      }
    } else {
      val.resize(count);
      for (size_t i = 0; i < count; i++)
        // decode("item",val[i]);
        s_decode(val[i], "item", this);
      de_endlist();
    }
  }

  /**
  * @brief 自定义类型T的 list<T> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  template <typename T>
  void decode(const char *key, std::list<T> &val) {
    int count;
    de_beginlist(key, count);
    val.resize(count);
    for (auto it = val.begin(); it != val.end(); it++) {
      decode("item", *it);
    }
    de_endlist();
  }

  /**
  * @brief 自定义类型K,T的 map<K,T> 类型进行反序列化
  * @param key 对应的键值
  * @param val 反序列化输出数据
  * @return true 反序列化成功
  * @return false 反序列化失败
  */
  template <typename K, typename T>
  void decode(const char *key, std::map<K, T> &val) {
    int count;
    de_beginlist(key, count);
    val.resize(count);
    for (auto it = val.begin(); it != val.end(); it++) {
      de_beginobject("");
      decode("key", it.key);
      decode("value", it.value);
      de_endobject();
    }
    de_endlist();
  }
};

#define GPACK(GTYP, GDS, ...)                                                \
  static bool s_simple(const GTYP &obj) { return GDS; }                      \
  static void s_encode(const GTYP &obj, const char *key,                     \
                       gomros::serialize::encoder *coder) {                  \
    coder->beginobject(key);                                                 \
    GPACK_N(__VA_ARGS__, _99, _98, _97, _96, _95, _94, _93, _92, _91, _90,   \
            _89, _88, _87, _86, _85, _84, _83, _82, _81, _80, _79, _78, _77, \
            _76, _75, _74, _73, _72, _71, _70, _69, _68, _67, _66, _65, _64, \
            _63, _62, _61, _60, _59, _58, _57, _56, _55, _54, _53, _52, _51, \
            _50, _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, _39, _38, \
            _37, _36, _35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, \
            _24, _23, _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, \
            _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N)                 \
    (__VA_ARGS__);                                                           \
    coder->endobject();                                                      \
  }                                                                          \
                                                                             \
  static bool s_decode(GTYP &obj, const char *key,                           \
                       gomros::serialize::decoder *decoder) {                \
    decoder->de_beginobject(key);                                            \
    DPACK_N(__VA_ARGS__, _99, _98, _97, _96, _95, _94, _93, _92, _91, _90,   \
            _89, _88, _87, _86, _85, _84, _83, _82, _81, _80, _79, _78, _77, \
            _76, _75, _74, _73, _72, _71, _70, _69, _68, _67, _66, _65, _64, \
            _63, _62, _61, _60, _59, _58, _57, _56, _55, _54, _53, _52, _51, \
            _50, _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, _39, _38, \
            _37, _36, _35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, \
            _24, _23, _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, \
            _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N)                 \
    (__VA_ARGS__);                                                           \
    decoder->de_endobject();                                                 \
    return true;                                                             \
  }

#define DT_BASE(CUS_TYPE, GDS) \
  struct ST_BASE_##CUS_TYPE {  \
    CUS_TYPE oval;             \
  };                           \
  GPACK(ST_BASE_##CUS_TYPE, GDS, oval)

/*
* @brief 基本数据类型int的序列化接口扩充
*/
DT_BASE(int, true)
DT_BASE(int8_t, true)
DT_BASE(int16_t, true)
DT_BASE(int32_t, true)
DT_BASE(int64_t, true)

DT_BASE(uint8_t, true)
DT_BASE(uint16_t, true)
DT_BASE(uint32_t, true)
DT_BASE(uint64_t, true)

/*
* @brief 基本数据类型 char 的序列化接口扩充
*/
DT_BASE(char, true)

/*
* @brief 基本数据类型 float 的序列化接口扩充
*/
DT_BASE(float, true)

/*
* @brief 基本数据类型 double 的序列化接口扩充
*/
DT_BASE(double, true)

/*
* @brief 基本数据类型 string 的序列化接口扩充
*/
struct ST_BASE_string {
  std::string oval;
};
GPACK(ST_BASE_string, false, oval)

/*
* @brief 基本数据类型 加外壳后 的序列化相关接口扩充
*/
#define DT_BASE_ENC(CUS_TYPE)                                                \
  static bool encode(const CUS_TYPE &o, int ntype,                           \
                     gomros::common::DataBuf &buf) {                         \
    ST_BASE_##CUS_TYPE &objT = (ST_BASE_##CUS_TYPE &)o;                      \
    bool ret = encode(objT, ntype, buf);                                     \
    return ret;                                                              \
  }                                                                          \
  static bool decode(int ntype, gomros::common::DataBuf &buf, CUS_TYPE &o) { \
    ST_BASE_##CUS_TYPE objT;                                                 \
    bool ret = decode(ntype, buf, objT);                                     \
    o = objT.oval;                                                           \
    return ret;                                                              \
  }                                                                          \
  static bool getsample(const CUS_TYPE &obj) { return true; }
/**
 * @brief 序列化及反序列化实施
 * 将不同类型的数据进行序列化，支持XML,JSON,二进制格式
*/
class utils {
 public:
  /**
  * @brief 基本数据类型 序列化 操作api接口
  * @param o 要序列化的int类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(int);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 int8_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(int8_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 int16_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(int16_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 int64_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(int64_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 uint8_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(uint8_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 uint16_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(uint16_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 uint32_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(uint32_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 uint64_t 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(uint64_t);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 char 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(char);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 float 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(float);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 double 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  DT_BASE_ENC(double);

  /**
  * @brief 基本数据类型 序列化操作api接口
  * @param o 要序列化的 string 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  static bool encode(const string &o, int ntype, gomros::common::DataBuf &buf) {
    ST_BASE_string objT = {o};
    bool ret = encode(objT, ntype, buf);
    return ret;
  }
  /**
  * @brief 基本数据类型 反序列化操作api接口
  * @param o 要反序列化的 string 类型数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 反序列化成功后输出结果
  * @return false 反序列化失败
  * @return true 反序列化成功
  */
  static bool decode(int ntype, gomros::common::DataBuf &buf, std::string &o) {
    ST_BASE_string objT;
    bool ret = decode(ntype, buf, objT);
    o = objT.oval;
    return ret;
  }

  /**
   * @brief 判断数据 string 类型是否是简单定长类型
  */
  static bool getsample(const std::string &obj) { return false; }

  /**
  * @brief 序列化操作api接口
  * @param o 要序列化的具体数据类型 T 数据
  * @param ntype 序列化格式 0-二进制  1-json  2-xml
  * @param buf 序列化成功后输出结果
  * @return false 序列化失败
  * @return true 序列化成功
  */
  template <typename T>
  static bool encode(const T &o, int ntype, gomros::common::DataBuf &buf) {
    encoder *coder = getencoder(ntype);
    coder->encode("root", o);
    coder->result(buf);
    if (coder->error_code > 0) {
      if (coder != nullptr) {
        delete coder;
        coder = nullptr;
      }
      return false;
    } else {
      if (coder != nullptr) {
        delete coder;
        coder = nullptr;
      }
      return true;
    }
  }

  /**
  * @brief 反序列化操作api接口
  * @param o 反序列化的具体数据
  * @param ntype 反序列化格式 0-二进制  1-json  2-xml
  * @param buf 反序列化成功后输出结果
  * @return false 反序列化失败
  * @return true 反序列化成功
  */
  template <typename T>
  static bool decode(int ntype, gomros::common::DataBuf &buf, T &o) {
    decoder *decoder = getdecoder(ntype);
    decoder->from(buf);
    decoder->decode("root", o);
    if (decoder->error_code > 0) {
      if (decoder != nullptr) {
        delete decoder;
        decoder = nullptr;
      }
      return false;
    } else {
      if (decoder != nullptr) {
        delete decoder;
        decoder = nullptr;
      }
      return true;
    }
  }
  static encoder *getencoder(int ntype);
  static decoder *getdecoder(int ntype);
  /**
   * @brief 判断数据类型是否是简单定长类型
   * @return true 定长数据
   * @return false 不定长数据
  */
  template <typename T>
  static bool getsample(T &obj) {
    return s_simple(obj);
  }
};

}  // namespace serialize
}  // namespace gomros
