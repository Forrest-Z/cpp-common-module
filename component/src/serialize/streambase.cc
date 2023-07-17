#include "serialize/streambase.hpp"
#include "xmldatastream.hpp"
#include "bytestream.hpp"
#include "serial_log.hpp"
using namespace gomros::serialize;
namespace gomros {
namespace serialize {

databuf::databuf() {
  buf = nullptr;
  datalen = 0;
  buflen = 0;
}
databuf::~databuf() {
  if (buf != nullptr) {
  delete buf;
  }
}
void databuf::Free() {
  if (buf != nullptr) {
  delete buf;
  }
  buf = nullptr;
  datalen = 0;
  buflen = 0;
}
void databuf::Detach() {
  buf = nullptr;
  datalen = 0;
  buflen = 0;
}
void databuf::From(const char* buffer, size_t len, bool copydata) {
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


void databuf::From(databuf& src, bool copydata) {
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

void databuf::Checksize(size_t needlen, bool copydata) {
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

int encoder::GetType() {
    int ret = format();
    return ret;
}
// void encoder::encode(const char *key, char * o) {
//     printf(" char * len=%d\n",sizeof(*o));
//     const char* oT = o;
//     encode (key, oT);
// }

void encoder::encode(const char *key, bool & o) {
    const bool oT = o;
    encode (key, oT);
}

void encoder::encode(const char *key, char & o) {
    const char oT = o;
    encode (key, oT);
}

void encoder::encode(const char *key, int &o) {
    const int oT = o;
    encode (key, oT);
}
void encoder::encode(const char *key, float & o) {
    const float oT = o;
    encode (key, oT);
}
void encoder::encode(const char *key, double & o) {
    const double oT = o;
    encode (key, oT);
}
void encoder::encode(const char *key, std::string & o) {
    const std::string oT = o;
    encode (key, oT);
}

void encoder::encode(const char *key, int8_t & o) {
    const int8_t oT = o;
    encode (key, oT);  
}

void encoder::encode(const char *key, int16_t & o) {
    const int16_t oT = o;
    encode (key, oT);  
}
void encoder::encode(const char *key, int64_t & o) {
    const int64_t oT = o;
    encode (key, oT);   
}
void encoder::encode(const char *key, uint8_t & o) {
    const uint8_t oT = o;
    encode (key, oT);  
}
void encoder::encode(const char *key, uint16_t & o) {
    const uint16_t oT = o;
    encode (key, oT);
}
void encoder::encode(const char *key, uint32_t & o) {
    const uint32_t oT = o;
    encode (key, oT);
}
void encoder::encode(const char *key, uint64_t & o) {
    const uint64_t oT = o;
    encode (key, oT);
}

void encoder::encode(const char *key, std::vector<char> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        char& first=val[0];
        addbuf((char*)&first, sizeof(char)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("char",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<char> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(char)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("char",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<int> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        int& first=val[0];
        addbuf((char*)&first, sizeof(int)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<int> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(int)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<int8_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        int8_t& first=val[0];
        addbuf((char*)&first, sizeof(int8_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int8_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<int8_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(int8_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int8_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<int16_t> &val) {
  int count =val.size();
    beginlist(key,count);
    if (count > 0) {
      if(format() == 0) {
          int len = count;
          // int16_t& first=val[0];
          addbuf((char*)val.data(), sizeof(int16_t)*len);
      } else {
      for (size_t i = 0; i < count; i++)
          encode("int16_t",val[i]);
      }
    }
    endlist();
}

void encoder::encode(const char *key, const std::vector<int16_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        // int16_t& first=val[0];
        addbuf((char*)val.data(), sizeof(int16_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int16_t",val[i]);
    }
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<int64_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        int64_t& first=val[0];
        addbuf((char*)&first, sizeof(int64_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int64_t",val[i]);
    }
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<int64_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(int64_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("int64_t",val[i]);
    }
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<uint8_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        uint8_t& first=val[0];
        addbuf((char*)&first, sizeof(uint8_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint8_t",val[i]);
    } 
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<uint8_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(uint8_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint8_t",val[i]);
    } 
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<uint16_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        uint16_t& first=val[0];
        addbuf((char*)&first, sizeof(uint16_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint16_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<uint16_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(uint16_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint16_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<uint32_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        uint32_t& first=val[0];
        addbuf((char*)&first, sizeof(uint32_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint32_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<uint32_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(uint32_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint32_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<uint64_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        uint64_t& first=val[0];
        addbuf((char*)&first, sizeof(uint64_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint64_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<uint64_t> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(uint64_t)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("uint64_t",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<float> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        float& first=val[0];
        addbuf((char*)&first, sizeof(float)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("float",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<float> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(float)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("float",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<double> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        double& first=val[0];
        addbuf((char*)&first, sizeof(double)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("double",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<double> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(double)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("double",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, std::vector<std::string> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        for (int i = 0; i < len; i++)
        encode("str",val[i]);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("str",val[i]);
    }        
  }
  endlist();
}

void encoder::encode(const char *key, const std::vector<std::string> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        for (int i = 0; i < len; i++)
        encode("str",val[i]);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("str",val[i]);
    }        
  }
  endlist();
}

int decoder::GetType() {
    int ret = format();
    return ret;
}

bool decoder::decode(const char *key, std::vector<char> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(char));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("char",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<int> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(int));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("int",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<int16_t> &val) {
  int count;
  de_beginlist(key,count);

  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(int16_t));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("int16_t",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<int64_t> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(int64_t));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("int64_t",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<uint8_t> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(uint8_t));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("uint8_t",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<uint16_t> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(uint16_t));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("uint16_t",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<uint32_t> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(uint32_t));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("uint32_t",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<uint64_t> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(uint64_t));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("uint64_t",val[i]);
  de_endlist();
  }
}

bool decoder::decode(const char *key, std::vector<float> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(float));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("float",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<double> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
    if (len <  0) {
    return false;
    }
    val.resize(len);
    readbuf((char *)val.data(),len*sizeof(double));
    return true;
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("double",val[i]);
  de_endlist();
  }
}
bool decoder::decode(const char *key, std::vector<std::string> &val) {
  int count;
  de_beginlist(key,count);
  if(format() == 0) {
    int len = count;
      if (len <  0) {
      return false;
      }
      val.resize(len);
      for (int i = 0; i < len; i++)
      decode("str",val[i]);
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("str",val[i]);
  de_endlist();
  }
}

encoder * utils::getencoder(int ntype) {
    if (ntype == GOMROS_SERIAL_DEFAULT)
    return new ByteEncode;
    if (ntype == GOMROS_SERIAL_XML)
    return new XmlEncode;
}
decoder * utils::getdecoder(int ntype) {
    if (ntype == GOMROS_SERIAL_DEFAULT)
    return new ByteDecode;
    if (ntype == GOMROS_SERIAL_XML)
    return new XmlDecode;
}

}  // namespace serialize
}  // namespace gomros