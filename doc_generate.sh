#!/bin/bash

### 使用软件为doxygen,graphviz, 确保运行脚本前软件安装正常
# sudo apt install doxygen
# sudo apt install graphviz

# 文档生成源路径 ./prebuilt/include/
# 文档存放目标路径 ./__build/doc/

mkdir -p ./Build/doc/

doxygen doc_generate_cfg.doxy