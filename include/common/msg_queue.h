
#pragma once

#include <map>
#include <memory>
#include <mutex>  //NOLINT
#include <string>
#include <thread>  //NOLINT
#include <vector>

#include "./threadpool.h"

namespace common {

/**
 * @brief 忽略通道
 */
constexpr auto TOPIC_IGNORE = "";

/**
 * @brief MsgQueue监听者
 */
class MsgQueueListener {
 public:
  MsgQueueListener() {}

  std::string name;
  /**
   * @brief	处理某个topic上发送的消息 \n
   *			参数指向的内存区域保证在函数返回前有效
   *
   * @param topic	话题
   * @param buf	消息内容的首地址
   * @param size	内容长度，单位byte
   */
  virtual void recieve_message(std::string topic, const char* buf,
                               const int size) = 0;
};

class MsgQueueEntry {
 public:
  MsgQueueEntry(std::string t, MsgQueueListener* p) : topic(t), listener(p) {}
  std::string topic;
  MsgQueueListener* listener;
  bool equals(MsgQueueEntry& e2) {                              // NOLINT
    return ((topic == e2.topic) && (listener == e2.listener));  // NOLINT
  }
};

struct message_param {
  MsgQueueListener* p;
  std::shared_ptr<std::vector<char>> m;
  std::string topic;
};

class MsgQueueWork : public basic_work {
 private:
  MsgQueueListener* listener;
  std::shared_ptr<std::vector<char>> data;
  std::string topic;

 public:
  MsgQueueWork(MsgQueueListener* listener,
               std::shared_ptr<std::vector<char>> data, std::string topic)
      : listener(listener), data(data), topic(topic) {}
  ~MsgQueueWork() {}

  virtual void run() {
    listener->recieve_message(topic, data->data(), data->size());
  }
};

/**
 * @brief 异步消息队列
 */
class MsgQueue {
 public:
  MsgQueue();
  ~MsgQueue();

  /**
   * @brief	将某个listener绑定到给定的频道编号上	\n
   *			该linstener会收到所有发到该频道上的信息	\n
   *			原则上不允许重复绑定	\n
   *
   * @param topic 接听的频道编号
   * @param p_listener 接听者对象的指针
   * @return listener_id 为本次绑定分配的唯一编号
   */
  int add_listener(const std::string topic, MsgQueueListener* p_listener);

  /**
   * @brief	根据绑定listener时分配的id移除该绑定 \n
   *			移除后listener将不再收到此次绑定的频道上的消息
   *
   * @param listener_id 执行add_listener函数时返回的ID
   */
  void remove_listener(const int listener_id);

  /**
   * @brief	移除后listener将不再收到此次绑定的频道上的消息
   *
   * @param topic 接听的频道编号
   * @param p_listener 接听者对象的指针
   */
  void remove_listener(const std::string topic, MsgQueueListener* p_listener);

  /**
   * @brief	清空所有绑定信息
   */
  void clear();

  /**
   * @brief	向每个接听该频道的listener发送消息	\n
   *			为每个listener启动一个单独的线程进行处理
   *
   * @param topic 发送到的频道编号
   * @param buf 要发送的消息在内存中的位置
   * @param size 要发送的消息的长度
   */
  void send(std::string topic, char* buf, int size);

  /**
   * @brief 处理消息任务
   * @param param message_param指针
   */
  // static void message_queue_handle_message(void* param);

  /**
   * @brief 使用printf打印msgQueue中绑定的信息
   */
  void print_debug_string();

 private:
  std::mutex mtx;

  std::map<std::string, std::vector<MsgQueueListener*>> topic_list;
  std::map<int, MsgQueueEntry> id_entry;
  int id_allocated = 1;

  std::shared_ptr<ThreadPool> tpool;
};

}  // namespace common
