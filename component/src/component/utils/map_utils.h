
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace gomros {
namespace entry {
namespace map_utils {

/**
 * @brief 将map信息转成string , 用于调试，eg: [key1,val1];[key2,val2];
 *
 * @tparam K
 * @tparam V
 * @param map
 * @param ret map转换后的信息
 */
template <typename K, typename V>
void ToString(const std::map<K, V> &map, std::string &ret) {
  ret.clear();

  std::stringstream ss;

  for (auto &i : map) {
    ss << " [ " << i.first << " , ";
    ss << i.second << " ] ;" << std::endl;
  }

  ret = ss.str();
}

/**
 * @brief 将map2 字段插入map1,如果重复则会替换map1原先的内容
 *
 * @tparam K key type
 * @tparam V value type
 * @param map1
 * @param map2
 */
template <typename K, typename V>
void InsertAndMerge(std::map<K, V> &map1, const std::map<K, V> &map2) {

  for (auto &i : map2) {

    if (map1.find(i.first) != map1.end()) {
      map1[i.first] = i.second;
    } else {
      map1.insert({i.first, i.second});
    }
  }
}

template <typename K, typename V>
void InsertAndMerge(std::map<K, V> &map1, K &key, V &val) {

  if (map1.find(key) != map1.end()) {
    map1[key] = val;
  } else {
    map1.insert({key, val});
  }
}

} // namespace map_utils

} // namespace entry
} // namespace gomros
