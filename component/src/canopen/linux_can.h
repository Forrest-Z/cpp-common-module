
#pragma once

#include <atomic>
#include <string>

class LinuxCan {
 public:
  LinuxCan(const std::string& name, uint32_t bitrate_k = 500,
           uint32_t restart_ms = 100);
  ~LinuxCan() {}

  bool IsConnect();

  uint32_t AddFlag(uint32_t id, bool RTR = false, bool EFF = false,
                   bool ERR = false);

  uint32_t Mask(uint32_t id, bool SFF = true, bool EFF = true);

  /**
   * @brief block
   *
   * @param id
   * @param len
   * @param data
   * @return int
   */
  int Recv(uint32_t& id, uint8_t& len, uint8_t* data);

  int Send(const uint32_t& id, const uint8_t& len, const uint8_t* data);

 private:
  void ExecBash(const std::string& cmd);

  void Init();

 private:
  std::string name;
  uint32_t bitrate_k;
  uint32_t restart_ms;

  std::atomic<int> sock;
};
