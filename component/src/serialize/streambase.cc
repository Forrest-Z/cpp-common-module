#include "serialize/streambase.hpp"
#include "xmldatastream.hpp"
#include "bytestream.hpp"
// #include "jsondatastream.h"
#include "serial_log.hpp"
using namespace gomros::serialize;
namespace gomros {
namespace serialize {


int encoder::GetType() {
    int ret = format();
    return ret;
}
// void encoder::encode(const char *key, char * o) {
//     printf(" char * len=%d\n",sizeof(*o));
//     const char* oT = o;
//     encode (key, oT);
// }



// void encoder::encode(const char *key, std::string & o) {
//     const std::string oT = o;
//     encode (key, oT);
// }

void encoder::encode(const char *key, const std::vector<char> &val) {
  int count =val.size();
  beginlist(key,count);
  if (count > 0) {
    if(format() == 0) {
        int len = count;
        addbuf((char*)val.data(), sizeof(char)*len);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
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
        encode("item",val[i]);
    } else {
    for (size_t i = 0; i < count; i++)
        encode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
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
      decode("item",val[i]);
  } else {
  val.resize(count);
  for (size_t i = 0; i < count; i++)
      decode("item",val[i]);
  de_endlist();
  }
}

encoder * utils::getencoder(int ntype) {
    if (ntype == GOMROS_SERIAL_DEFAULT)
    return new ByteEncode;
    if (ntype == GOMROS_SERIAL_XML)
    return new XmlEncode;
    // if (ntype == GOMROS_SERIAL_JSON)
    // return new XmlEncode;
}
decoder * utils::getdecoder(int ntype) {
    if (ntype == GOMROS_SERIAL_DEFAULT)
    return new ByteDecode;
    if (ntype == GOMROS_SERIAL_XML)
    return new XmlDecode;
}

}  // namespace serialize
}  // namespace gomros