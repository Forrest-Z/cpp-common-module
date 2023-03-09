
#include "include/common/msg_queue.h"

#include "include/common_logger_impl.h"

namespace common {

MsgQueue::MsgQueue(void) {
  this->tpool = std::make_shared<ThreadPool>();
  info_log("msgqueue , new thread pool creat. \n");
}

MsgQueue::~MsgQueue() {}

int MsgQueue::add_listener(const std::string topic,
                           MsgQueueListener* p_listener) {
  std::lock_guard<std::mutex> lck(this->mtx);

  int ret = -1;

  auto search1 = this->topic_list.find(topic);
  bool exist = false;
  if (search1 == topic_list.end()) {
    std::vector<MsgQueueListener*> tmp;
    topic_list.insert(
        std::pair<std::string, std::vector<MsgQueueListener*>>(topic, tmp));
    search1 = topic_list.find(topic);
  } else {
    for (MsgQueueListener* p : search1->second) {
      if (p == p_listener) {
        exist = true;
        break;
      }
    }
  }
  if (!exist) {
    search1->second.push_back(p_listener);
    ret = id_allocated++;
    MsgQueueEntry entry(topic, p_listener);
    id_entry.insert(std::pair<int, MsgQueueEntry>(ret, entry));
  }
  return ret;
}

void MsgQueue::remove_listener(const int listener_id) {
  std::lock_guard<std::mutex> lck(this->mtx);

  auto search1 = id_entry.find(listener_id);
  if (search1 != id_entry.end()) {
    MsgQueueEntry entry = search1->second;
    auto search2 = this->topic_list.find(entry.topic);
    if (search2 != this->topic_list.end()) {
      for (auto it = search2->second.begin(); it != search2->second.end();
           it++) {
        if (*it == entry.listener) {
          search2->second.erase(it);
          break;
        }
      }
      if (search2->second.empty()) {
        this->topic_list.erase(search2);
      }
    }
    id_entry.erase(search1);
  }
}

void MsgQueue::remove_listener(const std::string topic,
                               MsgQueueListener* p_listener) {
  this->mtx.lock();

  int id = -1;
  MsgQueueEntry entry(topic, p_listener);
  for (auto& e : id_entry) {
    if (entry.equals(e.second)) {
      id = e.first;
      break;
    }
  }

  this->mtx.unlock();

  if (id > 0) {
    remove_listener(id);
  }
}

void MsgQueue::clear() {
  std::lock_guard<std::mutex> lck(this->mtx);

  topic_list.clear();
  id_entry.clear();
}

void MsgQueue::send(std::string topic, char* buf, int size) {
  if (topic == TOPIC_IGNORE) {
    return;
  }

  this->mtx.lock();
  auto search1 = topic_list.find(topic);
  if (search1 != topic_list.end()) {
    auto m = std::make_shared<std::vector<char>>();
    m->reserve(size);
    for (int i = 0; i < size; i++) {
      m->push_back(buf[i]);
    }

    for (auto iter = search1->second.begin(); iter != search1->second.end();
         iter++) {
      MsgQueueListener* p = *iter;
      // struct message_param* param = new struct message_param();
      // param->p = p;
      // param->m = m;
      // param->topic = topic;

      // this->tpool->AddNewWork(void, topic);
      auto work = std::make_shared<MsgQueueWork>(p, m, topic);
      this->tpool->AddNewWork(work, topic);
    }
  }

  this->mtx.unlock();
}

void MsgQueue::print_debug_string() {
  std::lock_guard<std::mutex> lck(this->mtx);

  printf("[DEBUG PRINT]\n");
  for (auto& entry : topic_list) {
    printf("topic %s:\n", entry.first.c_str());
    for (MsgQueueListener* p : entry.second) {
      printf("\t %s \n", p->name.c_str());
    }
  }
  printf("ID list:\n");
  for (auto& entry : id_entry) {
    printf("\t<%d, %s, %s> \n", entry.first, entry.second.topic.c_str(),
           entry.second.listener->name.c_str());
  }
  printf("[DEBUG PRINT END]\n");
}

}  // namespace common
