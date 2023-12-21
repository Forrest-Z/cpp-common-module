

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>

#include "co_driver.h"

namespace canopen {

class CoSlave {
 public:
  CoSlave(std::shared_ptr<CoDriver> driver, uint32_t node_id)
      : driver(driver), node_id(node_id) {}

  uint32_t GetNodeId() { return node_id; }

  friend class CoMaster;

 private:
  void HandleFrame(uint32_t& id, uint8_t& len, uint8_t* data);

 protected:
  virtual void RecvTpdo1(const uint8_t len, uint8_t* data) {}
  virtual void RecvTpdo2(const uint8_t len, uint8_t* data) {}
  virtual void RecvTpdo3(const uint8_t len, uint8_t* data) {}
  virtual void RecvTpdo4(const uint8_t len, uint8_t* data) {}

 protected:
  inline void SendRpdo1(const uint8_t len, uint8_t* data) {
    uint32_t frame_id = node_id + 200;
    driver->Send(frame_id, len, data);
  }
  inline void SendRpdo2(const uint8_t len, uint8_t* data) {
    uint32_t frame_id = node_id + 300;
    driver->Send(frame_id, len, data);
  }
  inline void SendRpdo3(const uint8_t len, uint8_t* data) {
    uint32_t frame_id = node_id + 400;
    driver->Send(frame_id, len, data);
  }
  inline void SendRpdo4(const uint8_t len, uint8_t* data) {
    uint32_t frame_id = node_id + 500;
    driver->Send(frame_id, len, data);
  }

 protected:
  template <class T>
  bool SdoRead(int16_t index, int8_t sub_index, T& data, int timeout_ms = 5) {
    std::lock_guard<std::mutex> lck(this->mtx);

    uint8_t buff[8];

    buff[0] = 0x40;
    LittleEndianWrite(&buff[1], index);
    buff[3] = sub_index;
    this->driver->Send(0x600 + node_id, sizeof(buff), buff);

    std::cv_status ret =
        this->tsdo_cv.wait_for(lck, std::chrono::milliseconds(timeout_ms));

    if (ret == std::cv_status::timeout) {
      return false;
    }

    if (this->tsdo.size() < (4 + sizeof(T))) {
      return false;
    }

    if (std::memcmp(&buff[1], &tsdo[1], 3) == 0) {
      data = LittleEndianRead<T>(&(this->tsdo[4]));
      return true;
    }

    return false;
  }

  template <class T>
  bool SdoWrite(uint32_t index, uint32_t sub_index, T data,
                int timeout_ms = 5) {
    std::lock_guard<std::mutex> lck(this->mtx);

    uint8_t buff[8];

    switch (sizeof(T)) {
      case 1:
        buff[0] = 0x2F;
        break;
      case 2:
        buff[0] = 0x2B;
        break;
      case 4:
        buff[0] = 0x23;
        break;
      default:
        return false;
        break;
    }

    LittleEndianWrite(&buff[1], index);
    buff[3] = sub_index;
    this->driver->Send(0x600 + node_id, sizeof(buff), buff);

    std::cv_status ret =
        this->tsdo_cv.wait_for(lck, std::chrono::milliseconds(timeout_ms));

    if (ret == std::cv_status::timeout) {
      return false;
    }

    if (this->tsdo.size() < 4) {
      return false;
    }

    if (std::memcmp(&buff[1], &tsdo[1], 3) == 0) {
      return true;
    }

    return false;
  }

 private:
  void RecvTsdo(const uint8_t len, uint8_t* data);

 protected:
  std::mutex mtx;
  uint32_t node_id;
  std::shared_ptr<CoDriver> driver;

  uint32_t heartbeat = 0;

  std::vector<uint8_t> tsdo;
  std::condition_variable tsdo_cv;
};

}  // namespace canopen
