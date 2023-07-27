#include "common/data_buf.h"
#include <cstring>
namespace gomros {
namespace common {

DataBuf::DataBuf() {
  buf = nullptr;
  datalen = 0;
  buflen = 0;
}
DataBuf::~DataBuf() {
  if (buf != nullptr) {
  delete buf;
  }
}
void DataBuf::Free() {
  if (buf != nullptr) {
  delete buf;
  }
  buf = nullptr;
  datalen = 0;
  buflen = 0;
}
void DataBuf::Detach() {
  buf = nullptr;
  datalen = 0;
  buflen = 0;
}
void DataBuf::From(const char* buffer, size_t len, bool copydata) {
if (copydata) {
  if(len==0){
  this->datalen = 0;
} else if (len <= this->buflen) {
  memcpy(buf, buffer, len);
  datalen = len;
 } else {
  if (buf != nullptr) {
  delete buf;
  }
  buf = new char[len];
  memcpy(buf,buffer,len);
  datalen = len;
  buflen = len;
  }
} else {
  if (buf != nullptr) {
    delete buf;
  }
  this->buf = (char*)buffer;
  this->buflen = len;
  this->datalen = len;
}
}


void DataBuf::From(DataBuf& src, bool copydata) {
if (copydata) {
if (src.datalen== 0) {
  this->datalen = 0;
} else if (src .datalen <= this->buflen) {
  memcpy(buf, src.buf, src.datalen);
  datalen = src.datalen;
} else {
  if (buf != nullptr) {
  delete buf;
  }
  buf = new char[src.buflen];
  memcpy(buf, src.buf, src.datalen);
  datalen = src.datalen;
  buflen = src.buflen;
  }
} else {
  if (buf != nullptr) {
  delete buf;
  }
  this->buf = src.buf;
  this->buflen = src.buflen;
  this->datalen = src.datalen;
  src.Detach();
  }
}

void DataBuf::Checksize(size_t needlen, bool copydata) {
  if (buflen < needlen) {
    char * srcbuf = buf;
    buf = new char[needlen];
    buflen = needlen;
    if (copydata && srcbuf != nullptr) {
      memcpy(buf, srcbuf, datalen);
    } else {
      datalen = 0;
    }
    if (srcbuf != nullptr) {
      delete srcbuf;
    }
  }
}

}
}