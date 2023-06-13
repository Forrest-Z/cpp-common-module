
### 使用python3 运行

module_name = input('name :')
print(module_name)

module_name = module_name.replace(' ','')

### h
def creat_head():
  f = open("./"+module_name+'.h','w+',1024,'utf-8')
  f.write(' \n\
#pragma once \n\
          \n\
namespace gomros { \n\
namespace common { \n\
  \n\
}  // namespace common\n\
}  // namespace gomros\n\
')
  f.close()
  return

### cc
def creat_cc():
  f = open("./"+module_name+'.cc','w+',1024,'utf-8')
  f.write('\n\
#include \"'+module_name+'.h\" \n'
+ '\n\
namespace gomros { \n\
namespace common { \n\
  \n\
}  // namespace common\n\
}  // namespace gomros\n\
')
  f.close()
  return

### test
def creat_test():
  f = open("./"+module_name+'_test.cpp','w+',1024,'utf-8')
  f.write('\n\
#include \"'+module_name+'.h\" \n'
+'#include <gtest/gtest.h> \n')
  f.close()
  return

creat_head()
creat_cc()
creat_test()

