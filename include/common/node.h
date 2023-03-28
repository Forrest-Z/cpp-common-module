
#pragma once

#include <boost/function.hpp>
#include <map>
#include <set>
#include <string>

#include "./msg_queue.h"
// #include <functional>

namespace common {

/**
 * @brief 封装 MsgQueue 单例类
 *
 */
class Master;

/**
 * @brief 回调函数格式
 */
// using CallBackFunc = void (*)(const char*, const int);
typedef boost::function<void(const char*, const int)> CallBackFunc;

/**
 * @brief 发布者对象
 */
class RawPublisher {
 public:
  explicit RawPublisher(std::string topic);
  ~RawPublisher();

  /**
   * @brief 向topic话题发布数据
   * @param buff 数组指针
   * @param size 数组长度
   */
  void Publish(const char* buff, const int size);

  /**
   * @brief 停止发送；
   * 停止过后，再使用Publish函数不会向通道发布数据
   *
   */
  void Stop();

  void Resume();

  std::string GetTopic(void);

 private:
  std::string topic;
  enum { RUNNING, STOPED } state;
};

/**
 * @brief 节点类，提供订阅发布话题功能
 */
class Node : public MsgQueueListener {
 public:
  /**
   * @brief Node构造函数
   *
   * @param name	节点名称
   */
  Node() {}
  explicit Node(std::string name) { this->name = name; }
  ~Node();

  /**
   * @brief 订阅话题
   * @param topic 要订阅的话题
   * @param callback_event 注册回调事件
   * @return 是否订阅成功
   */
  bool SubscribeTopic(std::string topic, CallBackFunc func);

  /**
   * @brief 取消订阅话题，不再收到该话题信息
   * @param topic	要取消的订阅话题
   *
   * @return 是否取消订阅成功
   */
  bool UnsubscribeTopic(std::string topic);

  /**
   * @brief 声明发布话题，只有通过之后才可以通过send向该话题发布消息
   * @param topic	要发布的话题
   *
   * @return 是否成功
   */
  RawPublisher* AdvertiseTopic(std::string topic);

  /**
   * @brief 取消发布话题，不再可以从话题信息发布信息
   * @param topic	要取消的话题
   *
   * @return 是否取消成功
   */
  bool UnadvertiseTopic(std::string topic);

  /**
   * @brief清除所有的订阅和发布话题，该节点不再能收发消息
   *
   */
  void Clear();

  /**
   * @brief 使用printf打印节点的订阅和发布信息
   *
   */
  void Debug();

 protected:
  std::mutex mtx;
  std::map<std::string, CallBackFunc> subscribe_list; /**< 订阅话题列表 */
  std::set<std::string> advertise_list;               /**< 发布话题列表 */

  /**
   * @brief	处理某个topic上发送的消息 \n
   *			参数指向的内存区域保证在函数返回前有效
   *
   * @param topic	话题
   * @param buf	消息内容的首地址
   * @param size	内容长度，单位byte
   */
  virtual void recieve_message(std::string topic, const char* buf,
                               const int size);
};

}  // namespace common
