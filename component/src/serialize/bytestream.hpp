#pragma once
#include "serialize/streambase.hpp"
#define SIZE_LIST_SECTOR 1000
namespace gomros {
namespace serialize {
class ByteEncode : public encoder
{
  public:      
    ByteEncode();
    ~ByteEncode(){}
    int format();
    void result(databuf& buf);
  public:
    void beginobject(const char *key);
    void endobject();
    void beginarray(const char *key);
    void endarray();      
    void beginlist(const char *key,int count);
    void endlist();
    void beginmap(const char *key,int count);
    void endmap();
    
    void addbuf(const char* buf,int len);

  public:
    void encode(const char *key, const bool & o);
    void encode(const char *key, const char & o);
    void encode(const char *key, const int & o);
    void encode(const char *key, const int8_t & o);
    void encode(const char *key, const int16_t & o);
    void encode(const char *key, const int64_t & o);
    void encode(const char *key, const uint8_t & o);
    void encode(const char *key, const uint16_t & o);
    void encode(const char *key, const uint32_t & o);
    void encode(const char *key, const uint64_t & o);
    void encode(const char *key, const float & o);
    void encode(const char *key, const double & o);
    void encode(const char *key, const std::string & o);

  private:
    struct st_mem {
    char memSeg[SIZE_LIST_SECTOR];
    };
    std::list<st_mem> m_buf;
    int m_SizeWrited = 0;
};

class ByteDecode : public decoder
{
  public:      
    ByteDecode();
    ~ByteDecode(){}
    int format();
    void from(databuf& buf);
              
  public:                
  
    void de_beginobject(const char *key);
    void de_endobject();
    void de_beginarray(const char *key);
    void de_endarray();    
    void de_beginlist(const char *key,int&count);
    void de_endlist();
    void de_beginmap(const char *key,int& count);
    void de_endmap();
    
    void readbuf(char* buf,int len);

public:
  bool decode(const char *key, bool & o);
  bool decode(const char *key, char & o);  
  bool decode(const char *key, int & o);
  bool decode(const char *key, int8_t & o);
  bool decode(const char *key, int16_t & o);
  bool decode(const char *key, int64_t & o);
  bool decode(const char *key, uint8_t & o);
  bool decode(const char *key, uint16_t & o);
  bool decode(const char *key, uint32_t & o);
  bool decode(const char *key, uint64_t & o);
  bool decode(const char *key, float & o);
  bool decode(const char *key, double & o);
  bool decode(const char *key, std::string & o);
private:
  std::vector<char> m_buf;
  int m_pos = 0;
};
}  // namespace serialize
}  // namespace gomros