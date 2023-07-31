#include "xmldatastream.hpp"
#include <iostream>
#include<sstream>
#include <cmath>
#include "serial_log.hpp"

namespace gomros {
namespace serialize {
struct xml_string_writer : xml_writer {
    std::string result;
    virtual void write( const void* data, size_t size ) {
        result += std::string( (const char*)data, (int)size );
    }
};

XmlEncode::XmlEncode() {
    error_code = 0;
    XmlDoc.reset();
    xml_node decl = XmlDoc.prepend_child( pugi::node_declaration );
    decl.append_attribute( "version" ) = "1.0";
    decl.append_attribute( "encoding" ) = "utf-8";
    mXmlBaseNode = XmlDoc;
    mXmlCurNode = mXmlBaseNode;
    if (mXmlCurNode == nullptr) {
    error_code = 1;
    }
    MY_LOGDBG(" 开始序列化——————————————————————\n");
}
int XmlEncode::format() {
    return GOMROS_SERIAL_XML;
}
void XmlEncode::beginobject(const char *key) {
    if (error_code > 0) return;
    xml_node lnode;
    {
        if (strcmp(key, "") == 0) {
        lnode = mXmlCurNode.append_child("obj");
        } else
      lnode = mXmlCurNode.append_child(key);
    }
    mXmlCurNode = lnode;
    mbIsArrayT = false;
    mbIsListT = false;
    if (mXmlCurNode == nullptr) {
    error_code = 3;
    }
    return;
}
void XmlEncode::endobject() {
    if (error_code > 0) return;
    mXmlCurNode = mXmlCurNode.parent();
    if (mXmlCurNode == nullptr) {
    error_code = 4;
    }
    return;
}
void XmlEncode::beginarray(const char *key) {
    if (error_code > 0) return;
    xml_node lnode;
    if (strcmp(key, "") == 0) {
      lnode = mXmlCurNode.append_child("arr");
    } else
    lnode = mXmlCurNode.append_child(key);
    mXmlCurNode = lnode;
    mbIsArrayT = true;
    if (mXmlCurNode == nullptr) {
    error_code = 5;
    }
    return;
}
void XmlEncode::endarray() {
    if (error_code > 0) return;
    mXmlCurNode = mXmlCurNode.parent();
    mbIsArrayT = false;
    if (mXmlCurNode == nullptr) {
    error_code = 6;
    }
    return;
}
void XmlEncode::beginlist(const char *key,int count) {
    if (error_code > 0) return;
    xml_node lnode;
    if (strcmp(key, "") == 0) {
      lnode = mXmlCurNode.append_child("list");
    } else
    lnode = mXmlCurNode.append_child(key);
    mXmlCurNode = lnode;
    mbIsListT = true;
    if (mXmlCurNode == nullptr) {
    error_code = 7;
    }
    return;
}
void XmlEncode::endlist() {
    if (error_code > 0) return;
    mXmlCurNode = mXmlCurNode.parent();
    mbIsListT = false;
    if (mXmlCurNode == nullptr) {
    error_code = 8;
    }
    return;
}
void XmlEncode::beginmap(const char *key,int count) {
    if (error_code > 0) return;
    xml_node lnode;
    if (strcmp(key, "") == 0) {
      lnode = mXmlCurNode.append_child("item");
    } else
    lnode = mXmlCurNode.append_child(key);
    mXmlCurNode = lnode;
    if (mXmlCurNode == nullptr) {
    error_code = 9;
    }
    return;
}
void XmlEncode::endmap() {
    if (error_code > 0) return;
    mXmlCurNode = mXmlCurNode.parent();
    if (mXmlCurNode == nullptr) {
    error_code = 10;
    }
    return;
}
void XmlEncode::addbuf(const char* buf,int len) {
    return;
}
void XmlEncode::encode(const char *key, const char & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}
void XmlEncode::encode(const char *key, const bool & o) {
    if (error_code > 0) return;
    if (mbIsListT || mbIsArrayT) {
    if(o)
     mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value("true");
    else
     mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value("false");
     } else {
    if(o)
    mXmlCurNode.append_attribute(key) =
     "true";
    else
    mXmlCurNode.append_attribute(key) =
     "false";
     }
}
void XmlEncode::encode(const char *key, const int & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    MY_LOGDBG(" xml 序列化 插入 int 类型数据 =%d\n",o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}
void XmlEncode::encode(const char *key, const int8_t & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}
void XmlEncode::encode(const char *key, const int16_t & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}

void XmlEncode::encode(const char *key, const int64_t & o) {
    if (error_code > 0) return;
    char buf[17];
    snprintf(buf, sizeof(buf), "%ld", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}

void XmlEncode::encode(const char *key, const uint8_t & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}

void XmlEncode::encode(const char *key, const uint16_t & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}

void XmlEncode::encode(const char *key, const uint32_t & o) {
    if (error_code > 0) return;
    char buf[10];
    snprintf(buf, sizeof(buf), "%d", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}

void XmlEncode::encode(const char *key, const uint64_t & o) {
    if (error_code > 0) return;
    char buf[17];
    snprintf(buf, sizeof(buf), "%ld", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}


void XmlEncode::encode(const char *key, const float & o) {
    if (error_code > 0) return;
    char buf[17];
    float out = o;
    if(std::isnan(o)) out = 0.0;
    if(!std::isnormal(out)) {out = 0.0;
     //printf(fei zheng chang shuju\n");
     }
    snprintf(buf, sizeof(buf), "%.5f", out);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
}
void XmlEncode::encode(const char *key, const double & o) {
    if (error_code > 0) return;
    char buf[17];
    snprintf(buf, sizeof(buf), "%.5f", o);
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(buf);
    else
    mXmlCurNode.append_attribute(key) = buf;
};

void XmlEncode::encode(const char *key, const std::string & o) {
    if (error_code > 0) return;
    if (mbIsListT || mbIsArrayT)
    mXmlCurNode.append_child(key).append_child(pugi::node_pcdata).set_value(o.c_str());
    else
    mXmlCurNode.append_attribute(key) = o.c_str();
};
void XmlEncode::result(gomros::common::DataBuf& buf) {
    xml_string_writer writer;
    XmlDoc.save( writer, "  ");
    MY_LOGDBG(" 序列化————结果数据=%s\n",writer.result.data());
    buf.From(writer.result.data(),writer.result.size()+1,true);
    buf.buf[buf.buflen] = ('\0');
    MY_LOGDBG(" 数据长度=%ld\n",buf.buflen);
}

/********************反序列化类************************/
XmlDecode::XmlDecode() {

}
int XmlDecode::format() {
    int ret = GOMROS_SERIAL_XML;
    return ret;
}
void XmlDecode::from(gomros::common::DataBuf& buf) {
    error_code = 0;
    m_pos = 0;
    std::string str = (buf.buf);
    MY_LOGDBG(" 待序列化的数据 = %s\n",str.c_str());
    xml_parse_result res = XmlDoc.load_string(str.c_str());
    if( !res ) {
        std::string err_str =
        std::string("Failed to load xml: ").append(res.description());
        std::cout << err_str <<std::endl;
        error_code = 1;
    }
    mXmlBaseNode = XmlDoc;
    mXmlCurNode = mXmlBaseNode;
    ItemSts item;
    m_Items.push(item);
}
void XmlDecode::de_beginobject(const char *key) {
    if (error_code > 0) return;
    ItemSts CurItem;
    CurItem.cCurItem = ITEM_OBJECT;
    CurItem.cParentItem = m_Items.top().cCurItem;
    m_Items.push(CurItem);
    xml_node lnode;
    if ((CurItem.cParentItem == ITEM_LIST) ||
     (CurItem.cParentItem == ITEM_ARRAY) ||
     (CurItem.cParentItem == ITEM_MAP)) {
        if (miCurid <= 0)
        lnode = mXmlCurNode.first_child();
        else
        lnode = mXmlCurNode.next_sibling();
        miCurid ++;
    } else {
    {
        if (strcmp(key, "") == 0) {
        lnode = mXmlCurNode.child("obj");
        } else
        lnode = mXmlCurNode.child(key); 
        }
    }
    mXmlCurNode = lnode;
    if (mXmlCurNode == nullptr) {
    error_code = 3;
    }
    return;
}

void XmlDecode::de_endobject() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    if ((cItem == ITEM_LIST) ||
     (cItem == ITEM_ARRAY) ||
      (cItem == ITEM_MAP)) {
    if (mXmlCurNode.next_sibling() != nullptr) {
    // std::cout << "obj is in array or list" << std::endl;
    } else {
    // std::cout << "obj is out of the array or list" << std::endl;
    mXmlCurNode = mXmlCurNode.parent();  
    }
    } else {
    // std::cout << "obj is out" << std::endl;
    mXmlCurNode = mXmlCurNode.parent();    
    }
    if (m_Items.size() > 0)
    m_Items.pop();
    if (mXmlCurNode == nullptr) {
    error_code = 4;
    }
    return;
}

void XmlDecode::de_beginarray(const char *key) {
    if (error_code > 0) return;
    ItemSts CurItem;
    CurItem.cCurItem = ITEM_ARRAY;
    CurItem.cParentItem = m_Items.top().cCurItem;
    m_Items.push(CurItem);
    MY_LOGDBG("de_beginarray key=%s,\n", key);
    xml_node lnode;
    if ((CurItem.cParentItem == ITEM_LIST) ||
     (CurItem.cParentItem == ITEM_ARRAY) ||
     (CurItem.cParentItem == ITEM_MAP)) {
        if (miCurid <= 0)
        lnode = mXmlCurNode.first_child();
        else
        lnode = mXmlCurNode.next_sibling();
        miCurid ++;
    } else {
    if (strcmp(key, "") == 0) {
      lnode = mXmlCurNode.child("arr");
    } else
    lnode = mXmlCurNode.child(key); }
    mXmlCurNode = lnode;
    // int size = 0;
    // for (auto it = mXmlCurNode.children().begin();
    //     it != mXmlCurNode.children().end(); it++)
    //     size++;
    // miSize = size;
    miCurid = 0;
    if (mXmlCurNode == nullptr) {
    error_code = 5;
    }
    return;
}

void XmlDecode::de_endarray() {
    if (error_code > 0) return;

    char cItem = m_Items.top().cParentItem;
    if ((cItem == ITEM_LIST) ||
     (cItem == ITEM_ARRAY) ||
      (cItem == ITEM_MAP)) {
        if (mXmlCurNode.next_sibling() != nullptr) {
        } else {
        mXmlCurNode = mXmlCurNode.parent();
        }
    } else {
    mXmlCurNode = mXmlCurNode.parent();
    }
    if (m_Items.size() > 0)
    m_Items.pop();
    MY_LOGDBG("\nde_endarray----------------------------------------------\n");
    if (mXmlCurNode == nullptr) {
    error_code = 6;
    }
    miCurid = 1;
    return;
}
    
void XmlDecode::de_beginlist(const char *key,int& count) {
    if (error_code > 0) return;
    ItemSts CurItem;
    CurItem.cCurItem = ITEM_LIST;
    CurItem.cParentItem = m_Items.top().cCurItem;
    m_Items.push(CurItem);
    xml_node lnode;
    if ((CurItem.cParentItem == ITEM_LIST) ||
     (CurItem.cParentItem == ITEM_ARRAY) ||
     (CurItem.cParentItem == ITEM_MAP)) {
        if (miCurid <= 0)
        lnode = mXmlCurNode.first_child();
        else
        lnode = mXmlCurNode.next_sibling();
        miCurid ++;
    } else {
    if (strcmp(key, "") == 0) {
      lnode = mXmlCurNode.child("list");
    } else
    lnode = mXmlCurNode.child(key); 
    }
    mXmlCurNode = lnode;
    int size = 0;
    for (auto it = mXmlCurNode.children().begin();
        it != mXmlCurNode.children().end(); it++)
        size++;
    count = size;
    miSize = size;
    MY_LOGDBG("de_beginlist key =%s size=%d\n",key ,count);
    
    if (mXmlCurNode == nullptr) {
    error_code = 7;
    }
    miCurid = 0;
    return;
}

void XmlDecode::de_endlist() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    if ((cItem == ITEM_LIST) ||
     (cItem == ITEM_ARRAY) ||
      (cItem == ITEM_MAP)) {
        if (mXmlCurNode.next_sibling() != nullptr) {
        } else {
        mXmlCurNode = mXmlCurNode.parent();
        }
    } else {
    mXmlCurNode = mXmlCurNode.parent();
    }
    if (mXmlCurNode == nullptr) {
    error_code = 8;
    }
    if (m_Items.size() > 0)
    m_Items.pop();
    miCurid = 1;
    return;
}

void XmlDecode::de_beginmap(const char *key,int& count) {
    if (error_code > 0) return;
    ItemSts CurItem;
    CurItem.cCurItem = ITEM_MAP;
    CurItem.cParentItem = m_Items.top().cCurItem;
    m_Items.push(CurItem);
    xml_node lnode;
    if ((CurItem.cParentItem == ITEM_LIST) ||
     (CurItem.cParentItem == ITEM_ARRAY) ||
     (CurItem.cParentItem == ITEM_MAP)) {
        if (miCurid <= 0)
        lnode = mXmlCurNode.first_child();
        else
        lnode = mXmlCurNode.next_sibling();
        miCurid ++;
    } else {
    if (strcmp(key, "") == 0) {
      lnode = mXmlCurNode.child("item");
    } else
    lnode = mXmlCurNode.child(key); }
    mXmlCurNode = lnode;
    if (mXmlCurNode == nullptr) {
    error_code = 9;
    }
    miCurid = 0;
    return;
}

void XmlDecode::de_endmap() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    if ((cItem == ITEM_LIST) ||
     (cItem == ITEM_ARRAY) ||
      (cItem == ITEM_MAP)) {
        if (mXmlCurNode.next_sibling() != nullptr) {
        } else {
        mXmlCurNode = mXmlCurNode.parent();
        }
    } else {
    mXmlCurNode = mXmlCurNode.parent();
    }
    if (mXmlCurNode == nullptr) {
    error_code = 10;
    }
    if (m_Items.size() > 0)
    m_Items.pop();
    miCurid = 1;
    return;
}


void XmlDecode::readbuf(char* buf,int len) {
    buf[0] = GOMROS_SERIAL_XML;
    return;
}

bool XmlDecode::decode(const char *key, bool & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
    } else {
    v = mXmlCurNode.attribute(key).value();
    }
    o = false;
    if (strcmp(v, "true") == 0)
    o = true;
    return true;
}

bool XmlDecode::decode(const char *key, char & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml char array miCurid =%d decode %s ", miCurid, key);
    } else {
        MY_LOGDBG(" xml char decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    char_t* pEnd;
    o = strtol(v, NULL, 10);
    MY_LOGDBG("  %d \n", o);
    return true;
}

bool XmlDecode::decode(const char *key, int & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml int arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml int decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    char_t* pEnd;
    o = strtol(v, NULL, 10);
    MY_LOGDBG("  %d \n", o);
    return true;
}

bool XmlDecode::decode(const char *key, int8_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml int8_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml int8_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = atoi(v);
    MY_LOGDBG("  %d \n", o);
    return true;
}
bool XmlDecode::decode(const char *key, int16_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml int16_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml int16_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = atoi(v);
    MY_LOGDBG("  %d \n", o);
    return true;
}
bool XmlDecode::decode(const char *key, int64_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml int64_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml int64_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = strtol(v, NULL, 10);
    MY_LOGDBG("  %ld \n", o);
    return true;
}
bool XmlDecode::decode(const char *key, uint8_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml uint8_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml uint8_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = atoi(v);
    MY_LOGDBG("  %d \n", o);
    return true;
}
bool XmlDecode::decode(const char *key, uint16_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml uint16_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml uint16_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = atoi(v);
    MY_LOGDBG("  %d \n", o);
    return true;
}
bool XmlDecode::decode(const char *key, uint32_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml uint32_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml uint32_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = atoi(v);
    MY_LOGDBG("  %d \n", o);
    return true;
}
bool XmlDecode::decode(const char *key, uint64_t & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    if (mXmlCurNode.empty()) return false;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml uint64_t arr decode %s ",key);
    } else {
    MY_LOGDBG(" xml uint64_t decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = strtol(v, NULL, 10);
    MY_LOGDBG("  %ld \n", o);
    return true;
}

bool XmlDecode::decode(const char *key, float & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml float array decode %s ",key);
    } else {
        MY_LOGDBG(" xml float decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    char_t* pEnd;
    o = strtof(v, &pEnd);
    MY_LOGDBG("  %f \n", o);
    return true;
}

bool XmlDecode::decode(const char *key, double & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
    } else {
    v = mXmlCurNode.attribute(key).value();
    }
    char_t* pEnd;
    o = strtof(v, &pEnd);
    return true;
}

bool XmlDecode::decode(const char *key, std::string & o) {
    if (error_code > 0) return false;
    if (mXmlCurNode == nullptr) {
    error_code = 2;
    return false;}
    const char_t* v;
    char CurItem = m_Items.top().cCurItem;
    if ((CurItem == ITEM_LIST) || (CurItem == ITEM_ARRAY)) {
        if (miCurid <= 0)
        mXmlArrNodeT = mXmlCurNode.first_child();
        else
        mXmlArrNodeT = mXmlArrNodeT.next_sibling();
        miCurid++;
        v = mXmlArrNodeT.child_value();
        MY_LOGDBG(" xml string array decode %s ---",key);
    } else {
        MY_LOGDBG(" xml string decode %s ",key);
    v = mXmlCurNode.attribute(key).value();
    }
    o = v;
    MY_LOGDBG(" %s \n", o.c_str());
    return true;
};

}  // namespace serialize
}  // namespace gomros
