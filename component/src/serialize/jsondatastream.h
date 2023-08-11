#pragma once
#include "serialize/streambase.hpp"
#include "yyjson.h"
#include <stack>
namespace gomros {
namespace serialize {
enum jItemType
{
    jITEM_OBJECT = 10,
    jITEM_ARRAY,
    jITEM_LIST,
    jITEM_MAP,
};

typedef struct {
  char cCurItem = 0;
  char cParentItem = 0;
  yyjson_mut_val *Json;
  yyjson_val *nJson;
  std::string keyName;
  yyjson_arr_iter Arryiter;
} jItemSts;


class JsonEncode : public encoder
{
  public:      
    JsonEncode();
    ~JsonEncode(){}
    int format();
    void result(gomros::common::DataBuf& buf);
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
    // void encode(const char *key, const char * o);
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
    yyjson_mut_doc *JsonDoc;
    yyjson_mut_val *BaseObj;


  bool mbIsArrayT = false;    // 如果是ARRAY数组插入，单个插入周期有效
  bool mbIsListT = false;     // 如果是LIST数组插入，单个插入周期有效
  std::stack<jItemSts> m_Items;
  bool firstobj = true;     // 如果是最外层的对象
};

class JsonDecode : public decoder
{
  public:      
    JsonDecode();
    ~JsonDecode(){}
    int format();
    void from(gomros::common::DataBuf& buf);
              
  public:                
  
    void de_beginobject(const char *key);
    void de_endobject();
    void de_beginarray(const char *key);
    void de_endarray();    
    void de_beginlist(const char *key,int& count);
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

  yyjson_doc *JsonDoc;
  yyjson_val *BaseObj;

  int miSize = 0;
  int miCurid = 0;

  std::stack<jItemSts> m_Items;
private:
  std::vector<char> m_buf;
  int m_pos = 0;
  bool firstobj = true;     // 如果是最外层的对象
};
}  // namespace serialize
}  // namespace gomros