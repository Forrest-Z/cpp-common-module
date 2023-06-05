
#include "include/common/node.h"

#include "include/common_logger_impl.h"
namespace common {

class Master {
 public:
  static MsgQueue *GetMsgQueue() {
    std::lock_guard<std::mutex> lck(mtx);
    if (mainQueue == nullptr) {
      mainQueue = std::make_shared<MsgQueue>();
    }
    return mainQueue.get();
  }

 private:
  Master() {}
  ~Master() {}
  // 禁止外部复制构造
  Master(const Master &signal) {}
  // 禁止外部赋值操作
  const Master &operator=(const Master &signal) { return *this; }

  static std::shared_ptr<MsgQueue> mainQueue;
  static std::mutex mtx;
};
std::shared_ptr<MsgQueue> Master::mainQueue = nullptr;
std::mutex Master::mtx;

//
RawPublisher::RawPublisher(std::string topic) {
  this->topic = topic;
  this->state = RUNNING;
}
RawPublisher::~RawPublisher() {}

void RawPublisher::Publish(const char *buff, const int size) {
  if (RUNNING == this->state)  //
    Master::GetMsgQueue()->send(this->topic, (char*)buff, size);
}

void RawPublisher::Stop() { this->state = STOPED; }

void RawPublisher::Resume() { this->state = RUNNING; }

std::string RawPublisher::GetTopic(void) { return this->topic; }

//

Node::~Node() { this->Clear(); }

bool Node::SubscribeTopic(std::string topic, CallBackFunc func) {
  std::lock_guard<std::mutex> lck(this->mtx);

  auto search = this->subscribe_list.find(topic);

  if (search == this->subscribe_list.end()) {
    this->subscribe_list.insert(
        std::pair<std::string, CallBackFunc>(topic, func));
    Master::GetMsgQueue()->add_listener(topic, this);
    return true;
  } else {
    warning_log("this topic has been subscribed . \n");
    return false;
  }
}

bool Node::UnsubscribeTopic(std::string topic) {
  std::lock_guard<std::mutex> lck(this->mtx);

  auto search = this->subscribe_list.find(topic);

  if (search != this->subscribe_list.end()) {
    this->subscribe_list.erase(search);
    Master::GetMsgQueue()->remove_listener(topic, this);
  }

  return true;
}

RawPublisher *Node::AdvertiseTopic(std::string topic) {
  std::lock_guard<std::mutex> lck(this->mtx);

  this->advertise_list.insert(topic);

  return new RawPublisher(topic);
}

bool Node::UnadvertiseTopic(std::string topic) {
  std::lock_guard<std::mutex> lck(this->mtx);

  /* topic is existed */
  auto ret = this->advertise_list.find(topic);

  if (ret != this->advertise_list.end()) {
    this->advertise_list.erase(ret);
    return true;
  } else {
    warning_log("topic not in advertise list . \n");
    return false;
  }
}

void Node::Clear() {
  std::lock_guard<std::mutex> lck(this->mtx);

  for (auto elem : this->subscribe_list)
    Master::GetMsgQueue()->remove_listener(elem.first, this);

  this->advertise_list.clear();
  this->subscribe_list.clear();
}

void Node::Debug() {
  std::lock_guard<std::mutex> lck(this->mtx);

  std::string ret;
  char s[UINT16_MAX] = "";
  int num = 0;

  num = snprintf(s, sizeof(s), "[ %s ]\n", this->name.c_str());
  ret += std::string(s, num);

  num = snprintf(s, sizeof(s), "advertise_list:\n{\n");
  ret += std::string(s, num);

  for (auto elem : this->advertise_list) {
    num = snprintf(s, sizeof(s), "\t%s\n", elem.c_str());
    ret += std::string(s, num);
  }

  num = snprintf(s, sizeof(s), "}\n");
  ret += std::string(s, num);

  num = snprintf(s, sizeof(s), "subscribe_list:\n{\n");
  ret += std::string(s, num);

  for (auto elem : this->subscribe_list) {
    num = snprintf(s, sizeof(s), "\t[%s , %p]\n", elem.first.c_str(),
                   elem.second);
    ret += std::string(s, num);
  }

  num = snprintf(s, sizeof(s), "}\n");
  ret += std::string(s, num);

  info_log("%s", ret.c_str());
}

void Node::recieve_message(std::string topic, const char *buf, const int size) {
  std::lock_guard<std::mutex> lck(this->mtx);

  auto target_event = this->subscribe_list.find(topic);
  if (target_event != this->subscribe_list.end()) {
    target_event->second(buf, size);
  }
}

}  // namespace common
