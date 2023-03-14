
#pragma once

#include <string>
#include <vector>

namespace common {

/**
 * @brief hex to char array
 *
 * @param hex
 * @param out
 * @return true convert success
 * @return false convert fail
 */
bool HexToCharArray(const std::string &hex, std::vector<char> *out);

/**
 * @brief char array to hex
 *
 * @return true convert success
 * @return false convert fail
 */
bool CharArrayToHex(const std::vector<char> &array, std::string *out_hex);

}  // namespace common
