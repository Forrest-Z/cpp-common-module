#include "bytestream.hpp"
#include "serial_log.hpp"
namespace gomros {
namespace serialize {
ByteEncode::ByteEncode() {
    m_SizeWrited = 0;
    st_mem IniMem;
    m_buf.push_back(IniMem);
}
int ByteEncode::format() {
    return GOMROS_SERIAL_DEFAULT;
}
void ByteEncode::beginobject(const char *key) {
    return;
}
void ByteEncode::endobject() {
    return;
}
void ByteEncode::beginarray(const char *key) {
    return;
}
void ByteEncode::endarray() {
    return;
}
void ByteEncode::beginlist(const char *key,int count) {
    encode(key, count);
    return;
}
void ByteEncode::endlist() {
    return;
}
void ByteEncode::beginmap(const char *key,int count) {
    return;
}
void ByteEncode::endmap() {
    return;
}
void ByteEncode::addbuf(const char* buf,int len) {
    st_mem LastMem = m_buf.back();
    int MemSize = SIZE_LIST_SECTOR;
    int liWrited = m_SizeWrited / MemSize;
    int liCurIndex = m_SizeWrited % MemSize;
    int liRest = MemSize - liCurIndex;
    int liLenNeedWrite = len;
    int liStartCpy = 0;
    // m_buf.pop_back();
/***************压入最后一个缓冲list***********/
    if (liRest >= len) {
      std::memcpy(&LastMem.memSeg[liCurIndex], buf, liLenNeedWrite);
    //   m_buf.push_back(LastMem);
      m_buf.back() = LastMem;
      m_SizeWrited += len;
    //   for (int i=0; i<len; i++) {
    //     //MY_LOGDBG("buf=%d - %d ",buf[i], LastMem.memSeg[i]);
    //   }
    //   //MY_LOGDBG(" 写入数据 len = %d m_SizeWrited=%d,buf[0]=%d\n",len,m_SizeWrited,buf[0]);
      return;
    } else {
      std::memcpy(&LastMem.memSeg[liCurIndex], buf, liRest);
    //   m_buf.push_back(LastMem);
    m_buf.back() = LastMem;
      m_SizeWrited += liRest;
      liLenNeedWrite -= liRest;
      liStartCpy += liRest;
    }
/***************处理剩余的数据，开辟新缓冲list并压入数据***********/
    // int liSegNeedWrite = liLenNeedWrite / MemSize;
    // int liRestNeedWrite = liLenNeedWrite % MemSize;
    while (liLenNeedWrite > 0) {
        st_mem NewMem;
        int liWriteLenTemp = liLenNeedWrite;
        if (liLenNeedWrite >= MemSize)
        liWriteLenTemp = MemSize;
        std::memcpy(&NewMem.memSeg[0], &buf[liStartCpy], liWriteLenTemp);
        m_buf.push_back(NewMem);
        m_SizeWrited += liWriteLenTemp;
        liLenNeedWrite -= liWriteLenTemp;
        liStartCpy += liWriteLenTemp;
    }
}
void ByteEncode::encode(const char *key, const char & o) {
    addbuf((char *)&o, sizeof(char));
}
void ByteEncode::encode(const char *key, const bool & o) {
    addbuf((char *)&o, sizeof(char));
}
void ByteEncode::encode(const char *key, const int & o) {
    addbuf((char *)&o, sizeof(int32_t));
}
void ByteEncode::encode(const char *key, const int8_t & o) {
    addbuf((char *)&o, sizeof(int8_t));
}
void ByteEncode::encode(const char *key, const int16_t & o) {
    addbuf((char *)&o, sizeof(int16_t));
}
void ByteEncode::encode(const char *key, const int64_t & o) {
    addbuf((char *)&o, sizeof(int64_t));
}
void ByteEncode::encode(const char *key, const uint8_t & o) {
    addbuf((char *)&o, sizeof(uint8_t));
}
void ByteEncode::encode(const char *key, const uint16_t & o) {
    addbuf((char *)&o, sizeof(uint16_t));
}
void ByteEncode::encode(const char *key, const uint32_t & o) {
    addbuf((char *)&o, sizeof(uint32_t));
}
void ByteEncode::encode(const char *key, const uint64_t & o) {
    addbuf((char *)&o, sizeof(uint64_t));
}
void ByteEncode::encode(const char *key, const float & o) {
    addbuf((char *)&o, sizeof(float));
}
void ByteEncode::encode(const char *key, const double & o) {
    addbuf((char *)&o, sizeof(double));
};
// void ByteEncode::encode(const char *key, const char * o) {
//     char type = DataType::STRING;
//     addbuf((char *)&type, sizeof(char));
//     int len = sizeof(*&o);
//     // addbuf((char *)&len,sizeof(len));
//     //MY_LOGDBG("插入 char  array char * type len=%d, size=%d\n",len,sizeof(o));
//     encode("", len);
//     addbuf(o, len);
// };

void ByteEncode::encode(const char *key, const std::string & o) {
    // //MY_LOGDBG(" 写入STRING type= %d\n",type);
    int len = o.size();
    // addbuf((char *)&len,sizeof(len));
    encode("", len);
    //MY_LOGDBG(" 写入STRING len= %d\n",len);
    addbuf(o.data(), len);
    // //MY_LOGDBG(" 写入STRING string= %s\n",o.c_str());
};
void ByteEncode::result(databuf& buf) {
    std::vector<st_mem> vec;
    vec.assign(m_buf.begin(),m_buf.end());
    // st_mem begiin = m_buf.front();
    //buf.attch(data_buf.data(),m_SizeWrited);
    // buf.buf.resize(m_SizeWrited);
    // buf.len = m_SizeWrited;
    // std::memcpy(buf.buf.data(), vec.data(), m_SizeWrited);
    // std::string str(data_buf.begin(),data_buf.end());
    // databuf buf_temp;
    // int WriteByte = 0;
    // while (WriteByte < m_SizeWrited) {
    //     buf_temp.buf
    // }
    buf.From((char*)vec.data(), m_SizeWrited, true);
    // //MY_LOGDBG("result m_buf[0]=%d,data_buf[0]=%d,buf.buf[0]=%d\n\n",begiin.memSeg[0],data_buf[0],buf.buf[0]);
    //MY_LOGDBG(" 写入m_SizeWrited= %d\n",m_SizeWrited);
    // std::cout << "result size = " << vec.size() << "" << std::endl;

}

/********************反序列化类************************/
ByteDecode::ByteDecode() {

}
int ByteDecode::format() {
    int ret = GOMROS_SERIAL_DEFAULT;
    return ret;
}
void ByteDecode::from(databuf& buf) {
    m_buf.resize(buf.datalen);
    // m_buf.assign(buf.buf[0],buf.buf[buf.len-1]);
    std::memcpy(m_buf.data(),buf.buf,buf.datalen);
    m_pos = 0;
    // for (int i=0; i<m_buf.size(); i++) {
    //     //MY_LOGDBG(" %d ", m_buf[i]);
    // }
    //MY_LOGDBG("带读取数据大小=%ld,m_buf[0] =%d \n",buf.datalen,m_buf[0]);
}
void ByteDecode::de_beginobject(const char *key) {
    return;
}

void ByteDecode::de_endobject() {
    return;
}

void ByteDecode::de_beginarray(const char *key) {
    return;
}

void ByteDecode::de_endarray() {
    return;
}
    
void ByteDecode::de_beginlist(const char *key,int& count) {
    decode(key,count);
    return;
}

void ByteDecode::de_endlist() {
    return;
}

void ByteDecode::de_beginmap(const char *key,int& count) {
    return;
}

void ByteDecode::de_endmap() {
    return;
}


void ByteDecode::readbuf(char* buf,int len) {
    std::memcpy(buf, (char *)&m_buf[m_pos], len);
    m_pos += len;
    return;
}

bool ByteDecode::decode(const char *key, bool & o) {
    o = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool ByteDecode::decode(const char *key, char & o) {
    o = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool ByteDecode::decode(const char *key, int & o) {
    o = *((int32_t *)(&m_buf[m_pos]));
    m_pos += 4;
    return true;
}
bool ByteDecode::decode(const char *key, int8_t & o) {
    o = *((int8_t *)(&m_buf[m_pos]));
    m_pos += 1;
    return true;
}
bool ByteDecode::decode(const char *key, int16_t & o) {
    o = *((int16_t *)(&m_buf[m_pos]));
    m_pos += 2;
    return true;
}
bool ByteDecode::decode(const char *key, int64_t & o) {
    o = *((int64_t *)(&m_buf[m_pos]));
    m_pos += 8;
    return true;
}
bool ByteDecode::decode(const char *key, uint8_t & o) {
    o = *((uint8_t *)(&m_buf[m_pos]));
    m_pos += 1;
    return true;
}
bool ByteDecode::decode(const char *key, uint16_t & o) {
    o = *((uint16_t *)(&m_buf[m_pos]));
    m_pos += 2;
    return true;
}
bool ByteDecode::decode(const char *key, uint32_t & o) {
    o = *((uint32_t *)(&m_buf[m_pos]));
    m_pos += 4;
    return true;
}
bool ByteDecode::decode(const char *key, uint64_t & o) {
    o = *((uint64_t *)(&m_buf[m_pos]));
    m_pos += 8;
    return true;
}
bool ByteDecode::decode(const char *key, float & o) {
    o = *((float *)(&m_buf[m_pos]));
    m_pos += 4;
    return true;
}

bool ByteDecode::decode(const char *key, double & o) {
    o = *((double *)(&m_buf[m_pos]));
    m_pos += 8;
    return true;
}

bool ByteDecode::decode(const char *key, std::string & o) {
    int len;
    decode("",len);
    if (len < 0) {
        return false;
    }
    o.assign((char *)&(m_buf[m_pos]), len);
    m_pos += len;
    // //MY_LOGDBG("string 类型数据len=%d读取m_pos=%d\n",len,m_pos);
    return true;
};

}  // namespace serialize
}  // namespace gomros
