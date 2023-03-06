
#include "include/common/msg_queue.h"

#include <gtest/gtest.h>

#include <mutex>

using std::string;
using namespace common;

MsgQueue* mainQueue;
string topic1 = "TOPIC1";
string topic2 = "TOPIC2";
std::mutex mtx;

class node1 : public MsgQueueListener {
 public:
  node1(string name) { this->name = name; }

  virtual void recieve_message(string topic, const char* buf, const int size) {
    string s(buf, size);

    printf("node1-recv : %s\n", s.c_str());

    mainQueue->send(topic2, (char*)s.c_str(), s.size());
  }
};

class node2 : public MsgQueueListener {
 public:
  node2(string name) { this->name = name; }

  virtual void recieve_message(string topic, const char* buf, const int size) {
    string s(buf, size);

    printf("---node2-recv : %s\n", s.c_str());
  }
};

TEST(common, MsgQueueTest) {
  int count = 200;

  string name1 = "node1";
  string name2 = "node2";

  node1 n1 = node1(name1);
  node2 n2 = node2(name2);

  // mainQueue = new MsgQueue(4);
  mainQueue = new MsgQueue();

  mainQueue->add_listener(topic1, &n1);
  mainQueue->add_listener(topic2, &n2);

  mainQueue->print_debug_string();

  while (count--) {
    string s = "test messages";

    s.append(std::to_string(count));
    mainQueue->send(topic1, (char*)s.c_str(), s.size());
    printf(" add new task , count = %d \n", count);
  }

  EXPECT_TRUE(true);
  sleep(3);

  mainQueue->clear();
  delete mainQueue;

  EXPECT_TRUE(true);
}
