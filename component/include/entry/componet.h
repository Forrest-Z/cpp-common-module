#include <map>
#include <string>

#define COMPONENT_OBJECT(OBJ)                                            \
  void ComponentInit(Componet* comp) { comp->instance = new OBJ(comp); } \
  void ComponentUninit(Componet* comp) { delete (OBJ*)(comp->instance); }

class thread_interface;
class log_interface;
class message_queue_interface;
class link_interface;
class componet_params_interface;  //   virtual std::string
                                  //   GetKeyVale(std::string& key) = 0;
                                  // 合并xml配置文件，同名参数 ，
//   SetKeyVale(std::string& key) = 0; -> 数据目录
// 合并xml配置文件，同名参数 ，

// bool ReadFile(std::string& filename,std::string& context);
// bool WriteFile(std::string& filename,std::string& context);

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
