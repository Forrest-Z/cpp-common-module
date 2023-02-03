
### 使用python3 运行

module_name = input('name :')
print(module_name)

module_name = module_name.replace(' ','')

### h
def creat_head():
  f = open("./include/common/"+module_name+'.h','w+',1024,'utf-8')
  f.write(' \n\
#pragma once \n\
namespace common {}  // namespace common\n\
')
  f.close()
  return

### cpp
def creat_cpp():
  f = open("./src/"+module_name+'.cpp','w+',1024,'utf-8')
  f.write('\n\
#include \"include/common/'+module_name+'.h\" \n'
+ 'namespace common {}  // namespace common')
  f.close()
  return

### test
def creat_test():
  f = open("./test/"+module_name+'_test.cpp','w+',1024,'utf-8')
  f.write('\n\
#include \"include/common/'+module_name+'.h\" \n'
+'#include <gtest/gtest.h> \n')
  f.close()
  return

creat_head()
creat_cpp()
creat_test()

