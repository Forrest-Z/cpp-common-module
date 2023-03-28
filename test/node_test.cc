
#include "include/common/node.h"

#include <gtest/gtest.h>

#include "boost/bind.hpp"

static void PublishDataThread(common::RawPublisher* pub) {
  int count = 20;

  while (count--) {
    std::string msg = "test msg : " + std::to_string(count);
    pub->Publish(msg.data(), msg.size());
    sleep(1);
  }
}

class Consumer {
 public:
  Consumer(std::string name, std::string sub_topic) {
    this->name = name;
    this->node = new common::Node(name);

    // _1 _2 站位符 ，为实际调用时的传参
    common::CallBackFunc func =
        boost::bind(HandleDataCallBackFunc, this, _1, _2);
    this->node->SubscribeTopic(sub_topic, func);
  }

  ~Consumer() {
    this->node->Clear();
    delete this->node;
  }

  common::Node* node;
  std::string name;

  void NodeObjectTest() {
    printf("NodeObjectTest : %s \n", this->name.c_str());
  }

  static void HandleDataCallBackFunc(Consumer* obj, const char* buf,
                                     const int size) {
    obj->NodeObjectTest();

    std::string msg(buf, size);
    printf("msg : %s \n", msg.c_str());
  }
};

TEST(common_test, node) {
  std::string msg_topic = "test_topic";
  // pub
  auto pub_node = std::make_shared<common::Node>("pub_node");
  pub_node->Debug();

  auto publisher = pub_node->AdvertiseTopic(msg_topic);
  std::thread pub_thr = std::thread(PublishDataThread, publisher);

  // sub
  Consumer c1 = Consumer("c1", msg_topic);
  Consumer c2 = Consumer("c2", msg_topic);
  
  sleep(25);

  pub_thr.join();
  delete publisher;
  EXPECT_TRUE(true);
}
