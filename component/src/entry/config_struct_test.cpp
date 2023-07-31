
#include "config_struct.h"
#include <gtest/gtest.h>

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