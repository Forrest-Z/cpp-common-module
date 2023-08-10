
#include "config_struct.h"
#include <gtest/gtest.h>
#include "common/file_utils.h"

TEST(entry, config_struct) {
  gomros::entry::ProductCfgTypedef p;
  p.name = "test";
  p.version = "2.0";

  gomros::entry::ProcessCfgTypedef a;
  a.name = "a";
  gomros::entry::ComponentFixCfgTypedef fix_cfg;
  fix_cfg.name = "fix";
  fix_cfg.running_name = "fix_running";
  fix_cfg.fixed_keyval_map.insert({"fix_key1", "fix_val1"});
  a.component.push_back(fix_cfg);
  p.processes.push_back(a);

  // gomros::entry::ProcessCfgTypedef b;
  // b.name = "b";
  // b.component.push_back({"1", "2", "3"});
  // b.component.push_back({"4", "5", "6"});
  // p.processes.push_back(b);

  gomros::entry::ProcessCfgTypedef c;
  c.name = "c";
  p.processes.push_back(c);

  gomros::common::DataBuf buf;

  std::cout << "---------------start-------------------" << std::endl;

  gomros::serialize::utils::encode(p, GOMROS_SERIAL_XML, buf);
  std::string xml_str(buf.buf, buf.datalen);
  std::cout << "----------------------------------" << std::endl;
  std::cout << xml_str << std::endl;

  buf.Free();
}

void ConfigStructTest();

TEST(entry, write_config) { ConfigStructTest(); }


void ConfigStructTest_comp() {
  gomros::entry::ComponentCfgTypedef cfg;

  cfg.name = "framwork";
  cfg.keyval_map.insert({"key1", "val1"});
  cfg.keyval_map.insert({"key2", "val2"});
  cfg.keyval_map.insert({"key3", "val3"});

  gomros::common::DataBuf buf;

  std::cout << "---------------start-------------------" << std::endl;

  gomros::serialize::utils::encode(cfg, GOMROS_SERIAL_XML, buf);
  std::string xml_str(buf.buf, buf.datalen);
  std::cout << "----------------------------------" << std::endl;
  std::cout << xml_str << std::endl;

  gomros::common::FileUtils::WriteSmallFile("component.xml", xml_str);

  buf.Free();
}

void ConfigStructTest() {

  ConfigStructTest_comp();

  gomros::entry::ProductCfgTypedef p;
  p.name = "gomros_test";
  p.version = "1.0";

  gomros::entry::ProcessCfgTypedef a;
  a.name = "process1";
  gomros::entry::ComponentFixCfgTypedef fix_cfg;
  fix_cfg.name = "framwork";
  fix_cfg.running_name = "framwork__";
  fix_cfg.fixed_keyval_map.insert({"key1", "val1--"});
  fix_cfg.fixed_keyval_map.insert({"key2", "val2--"});
  a.component.push_back(fix_cfg);
  p.processes.push_back(a);

  gomros::common::DataBuf buf;

  std::cout << "---------------start-------------------" << std::endl;

  gomros::serialize::utils::encode(p, GOMROS_SERIAL_XML, buf);
  std::string xml_str(buf.buf, buf.datalen);
  std::cout << "----------------------------------" << std::endl;
  std::cout << xml_str << std::endl;

  gomros::common::FileUtils::WriteSmallFile("product.xml", xml_str);

  buf.Free();
}