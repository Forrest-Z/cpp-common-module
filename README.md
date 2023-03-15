# cpp-common-module
Some generic CPP modules. (base on c++11 , boost )

# boost 安装

使用apt安装或用源码安装

```bash

sudo apt install libboost-all-dev

```

# gtest 安装

使用apt安装或用源码安装
```bash

sudo apt install libgtest-dev

```

# clang-format 安装使用

apt 安装clang-format，并使用vscode中对应插件；  
>快捷键指令 alt+shift+f

```bash

sudo apt install clang-format

```

# valgrind 安装

```bash

sudo apt install valgrind

### 检查main文件内存泄漏情况
valgrind --leak-check=full ./main

### 检查main文件内存泄漏情况(indirect,definite,possible)
valgrind -v --leak-check=full --show-leak-kinds=indirect,definite,possible ./main

```
> 注意：valgrind 在arm64工控机上可能会检测不出内存泄漏的位置，在x86_64上可以；

# lcov 代码测试覆盖率检查

```bash

sudo apt-get install lcov

sh ReportCoverage.sh

```

# cpplint 代码格式检查

```bash

pip install cpplint

```

# 使用vscode Extention C++ TestMate

>用Extention:Markplace 安装

>在settings.json 里加入如下字段，参数为可执行文件路径

```json
"testMate.cpp.test.advancedExecutables": [
    {
      "pattern": "${workspaceFolder}/Build/test/common/bin/*"
    }
  ]
```

>点击左侧栏小药水图标(Testing)


####

