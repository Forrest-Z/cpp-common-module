#pragma once
#include "serialize/streambase.hpp"
#include "common/data_buf.h"
#include "pugixml.hpp"
#include <stack>
namespace gomros {
namespace serialize {
using namespace pugi;
enum ItemType
{
    ITEM_OBJECT = 10,
    ITEM_ARRAY,
    ITEM_LIST,
    ITEM_MAP,
};

typedef struct {
  char cCurItem = 0;
  char cParentItem = 0;
} ItemSts;

class XmlEncode : public encoder
{
  public:      
    XmlEncode();
    ~XmlEncode(){}
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
    xml_document XmlDoc;
    xml_node mXmlBaseNode;
    xml_node mXmlCurNode;
  bool mbIsArrayT = false;    // 如果是ARRAY数组插入，单个插入周期有效
  bool mbIsListT = false;     // 如果是LIST数组插入，单个插入周期有效
};

class XmlDecode : public decoder
{
  public:      
    XmlDecode();
    ~XmlDecode(){}
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
  xml_document XmlDoc;
  xml_node mXmlBaseNode;
  xml_node mXmlCurNode;

  xml_node mXmlArrNodeT;

  int miSize = 0;
  int miCurid = 0;

  std::stack<ItemSts> m_Items;
private:
  std::vector<char> m_buf;
  int m_pos = 0;
};
}  // namespace serialize
}  // namespace gomros