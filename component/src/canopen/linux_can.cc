#include "linux_can.h"

#include <errno.h>
#include <fcntl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>

LinuxCan::LinuxCan(const std::string& name, uint32_t bitrate_k,
                   uint32_t restart_ms)
    : name(name), bitrate_k(bitrate_k), restart_ms(restart_ms) {
  this->sock = -1;
  {
    ExecBash("modprobe can");
    ExecBash("modprobe can_raw");
    ExecBash("modprobe mttcan");
  }

  {
    std::string cmd = "ip link set ";
    ExecBash((cmd + " down " + name));

    ExecBash((cmd + name + " type can bitrate " +
              std::to_string(bitrate_k * 1000) + " restart-ms " +
              std::to_string(restart_ms) + " tq 10"));
    ExecBash((cmd + " up " + name));
  }

  Init();
}

bool LinuxCan::IsConnect() { return this->sock.load() != -1; }

uint32_t LinuxCan::AddFlag(uint32_t id, bool RTR, bool EFF, bool ERR) {
  uint32_t ret = id;
  if (RTR) {
    ret |= CAN_RTR_FLAG;
  }
  if (EFF) {
    ret |= CAN_EFF_FLAG;
  }
  if (ERR) {
    ret |= CAN_ERR_FLAG;
  }

  return ret;
}

uint32_t LinuxCan::Mask(uint32_t id, bool SFF, bool EFF) {
  uint32_t ret = id;

  if (EFF) {
    ret &= CAN_EFF_MASK;
  }

  if (SFF) {
    ret &= CAN_SFF_MASK;
  }

  return ret;
}

int LinuxCan::Recv(uint32_t& id, uint8_t& len, uint8_t* data) {
  can_frame fr;
  int nbytes;
  nbytes = read(this->sock.load(), &fr, sizeof(can_frame));

  if (nbytes < 0) {
    printf("error : CAN read error : %d , restart... \n", errno);
    this->sock = -1;
    this->Init();
    return -1;
  } else {
    id = fr.can_id;
    len = fr.can_dlc;
    std::memcpy(data, fr.data, len);
  }
  return 0;
}

int LinuxCan::Send(const uint32_t& id, const uint8_t& len,
                   const uint8_t* data) {
  int nbytes;
  struct can_frame fr;
  memset(&fr, 0, sizeof(fr));
  fr.can_id = id;
  fr.can_dlc = std::min(len, (uint8_t)8);

  std::memcpy(fr.data, data, fr.can_dlc);

  nbytes = write(this->sock, &fr, sizeof(fr));

  if (nbytes < 0) {
    printf("error : CAN send error : %d , restart... \n", errno);
    this->sock = -1;
    this->Init();
    return -1;
  }

  return 0;
}

void LinuxCan::ExecBash(const std::string& cmd) {
  printf("exec : %s \n", cmd.c_str());
  system(cmd.c_str());
}

void LinuxCan::Init() {
  int ret, s;
  struct sockaddr_can addr;
  struct ifreq ifr;
  bool can_enable = true;

  memset(&addr, 0, sizeof(addr));

  // 1.Create socket
  s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (s < 0) {
    printf("socket PF_CAN failed .\n");
    can_enable = false;
  }
  // 2.Specify can channel
  strcpy(ifr.ifr_name, this->name.c_str());  // NOLINT

  ret = ioctl(s, SIOCGIFINDEX, &ifr);

  // 3.Bind the socket to can
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  ret = bind(s, (struct sockaddr*)&addr, sizeof(addr));

  can_enable = true;

  ///* 数据过滤配置参数 */
  // const int size = this_config.filter_size;
  // struct can_filter rfilter[20];

  // /* 数据加入过滤器 */
  // for (int i = 0; i < size; i++) {
  //   rfilter[i].can_id = this_config.rfilter[i];
  //   rfilter[i].can_mask = CAN_SFF_MASK;
  // }
  // setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter,
  // sizeof(rfilter));

  if (!can_enable) {
    printf("can channel not initialize!\n");
    return;
  }
  printf("can channel initialize success=%d!\n", s);
  this->sock = s;
}
