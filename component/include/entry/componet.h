#pragma once 

#include <map>
#include <string>


#define COMPONENT_OBJECT(OBJ)                                            \
  void ComponentInit(Componet* comp) { comp->instance = new OBJ(comp); } \
  void ComponentUninit(Componet* comp) { delete (OBJ*)(comp->instance); }


class thread_pool;

class componet_config;  //   virtual std::string
                                  //   GetConfig(std::string& key) = 0;
                                  //   virtual std::string
                                  //   GetConfig(map& key_value) = 0;
                                  // 合并xml配置文件，同名参数 ，
//   SetConfig(std::string& key) = 0; -> 数据目录 发通知消息
// 合并xml配置文件，同名参数 ，

// template a bool ReadConfigFile(filename , a &oo);
// bool ReadAndMergeConfigFile(filename , &key_value_map);
// 根据优先级合并配置文件，如product.xml   规定几个目录查找



class Componet {
 private:
  /* data */
 public:
  virtual std::string GetName() = 0;
  virtual std::string GetPath() = 0;

  void* instance = nullptr;

  
};

