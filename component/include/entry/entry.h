
#pragma once

#include <string>

#include "task_manager.h"

namespace gomros {
namespace entry {

// 供组件写数据
// 运行时目录文件相对路径名 ， map/ale.smap
void SaveDataToFile(const std::string& relative_file,
                    const std::string& context);

}  // namespace entry
}  // namespace gomros
