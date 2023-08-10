/**
 * @file component_manager.h
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */
#pragma once

#include <vector>

#include "../entry/config_struct.h"
#include "async/semaphore.h"
#include "componet_impl.h"
#include "entry/componet.h"

namespace gomros {
namespace entry {

class ComponentManager {
public:
  static ComponentManager &Instance();

  // 主进程 中 初始化
  void Init(std::map<std::string, std::vector<std::string>> &cmd_map);
  // 子进程 中 初始化
  void Init(const std::string &process_name,
            std::map<std::string, std::vector<std::string>> &cmd_map);
  void Uninit();

  void LoadAllComponent();

  void WaitEnd();

  void InitAllComponent();
  void UnInitAllComponent();

  void GetProcessNameList(std::vector<std::string> &process_name_list);

  bool GetComponentPath(const std::string &name, std::string &path);

  void GetDataPath(std::string &data_path) { data_path = this->data_path; }

  void ChangeProductCfg(ComponentFixCfgTypedef &fix_cfg);

private:
  ComponentManager() {}
  ~ComponentManager() {}

  void ProductCfgInit();

  static ComponentManager *instance;

  std::string data_path; // 数据目录

  // name , component_path
  std::map<std::string, std::string> comp_name_path_map;

  std::vector<ComponetImpl *> component_list;
  ProductCfgTypedef product_cfg, fix_product;

  std::string process_name;
  std::vector<std::string> subprocess_name;

  std::shared_ptr<gomros::async::Semaphore> end_sem;
};

} // namespace entry
} // namespace gomros
