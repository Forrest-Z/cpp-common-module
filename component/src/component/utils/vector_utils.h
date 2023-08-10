
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace gomros {
namespace entry {
namespace vector_utils {

/**
 * @brief 将vector信息转成string , 用于调试
 *
 * @tparam K
 * @tparam V
 * @param vec
 * @param ret vec转换后的信息
 */
template <typename V>
void ToString(const std::vector<V> &vec, std::string &ret) {
  ret.clear();

  std::stringstream ss;

  for (auto &i : vec) {
    ss << " [ " << i << " ] ;" << std::endl;
  }

  ret = ss.str();
}

} // namespace vector_utils

} // namespace entry

} // namespace gomros
