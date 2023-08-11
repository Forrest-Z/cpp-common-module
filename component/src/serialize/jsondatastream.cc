#include "jsondatastream.h"
#include <iostream>
#include<sstream>
#include <cmath>
#include "serial_log.hpp"
namespace gomros {
namespace serialize {

JsonEncode::JsonEncode() {
    error_code = 0;
    JsonDoc = yyjson_mut_doc_new(NULL);
    jItemSts item;
    m_Items.push(item);
    MY_LOGDBG(" json 开始序列化——————————————————————\n");
}
int JsonEncode::format() {
    return GOMROS_SERIAL_JSON;
}
void JsonEncode::beginobject(const char *key) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_OBJECT;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_mut_val * Jval;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_mut_arr_add_obj(JsonDoc, Jsonbase);
    } else {
        Jval = yyjson_mut_obj(JsonDoc);
        if (firstobj) {
        BaseObj = Jval;
        yyjson_mut_doc_set_root(JsonDoc, BaseObj);
        firstobj = false;
        } else
        ret = yyjson_mut_obj_add_val(JsonDoc,Jsonbase,key,Jval);
    }
    
    CurItem.Json = Jval;
    CurItem.keyName = key;
    m_Items.push(CurItem);
    
    mbIsArrayT = false;
    mbIsListT = false;
    if ((Jval == nullptr)||(!ret)) {
        error_code = 1;
        MY_LOGDBG(" beginobject  key=%s item=%d size=%ld,ret=%d\n", key, CurItem.cParentItem, m_Items.size(),ret);
    }
    return;
}
void JsonEncode::endobject() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    yyjson_mut_val * JsonObj = m_Items.top().Json;
    std::string sObjKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG(" endobject fatherkey=%s key=%s item=%d size=%ld\n", m_Items.top().keyName.c_str(), sObjKey.c_str(), cItem, m_Items.size());
    // string str = yyjson_mut_write(JsonDoc, 0, NULL);
    // printf("%s\n",str.c_str());
    return;
}
void JsonEncode::beginarray(const char *key) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_ARRAY;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_mut_val * Jval;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_mut_arr_add_arr(JsonDoc, Jsonbase);
    } else {
        Jval = yyjson_mut_arr(JsonDoc);
        ret = yyjson_mut_obj_add_val(JsonDoc,Jsonbase,key,Jval);
    }

    CurItem.Json = Jval;
    CurItem.keyName = key;
    m_Items.push(CurItem);
    
    mbIsArrayT = true;
    if ((Jval == nullptr) || (!ret)) {
        error_code = 2;
        MY_LOGDBG(" beginarray  key=%s item=%d size=%ld, ret=%d\n", key, cItem, m_Items.size(),ret);
    }
    return;
}
void JsonEncode::endarray() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    yyjson_mut_val * JsonArr = m_Items.top().Json;
    std::string sArrKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG(" endarray  key=%s item=%d size=%ld\n", sArrKey.c_str(), cItem, m_Items.size());
    mbIsArrayT = false;

    return;
}
void JsonEncode::beginlist(const char *key,int count) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_LIST;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_mut_val * Jval;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_mut_arr_add_arr(JsonDoc, Jsonbase);
    } else {
        Jval = yyjson_mut_arr(JsonDoc);
        ret = yyjson_mut_obj_add_val(JsonDoc,Jsonbase,key,Jval);
    }

    CurItem.Json = Jval;
    CurItem.keyName = key;
    m_Items.push(CurItem);
    mbIsListT = true;
    if ((Jval == nullptr) || (!ret)) {
        error_code = 3;
        MY_LOGDBG(" beginlist  key=%s item=%d size=%ld\n", key, cItem, m_Items.size());
    }
    return;
}
void JsonEncode::endlist() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    yyjson_mut_val * JsonArr = m_Items.top().Json;
    std::string sArrKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG(" endlist  key=%s item=%d size=%ld\n", sArrKey.c_str(), cItem, m_Items.size());
    mbIsListT = false;
    return;
}
void JsonEncode::beginmap(const char *key,int count) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_MAP;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_mut_val * Jval;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_mut_arr_add_arr(JsonDoc, Jsonbase);
    } else {
        Jval = yyjson_mut_arr(JsonDoc);
        ret = yyjson_mut_obj_add_val(JsonDoc,Jsonbase,key,Jval);
    }

    CurItem.Json = Jval;
    CurItem.keyName = key;
    m_Items.push(CurItem);
    
    if ((Jval == nullptr) || (!ret)) {
        error_code = 4;
        MY_LOGDBG(" beginmap  key=%s item=%d size=%ld\n", key, cItem, m_Items.size());
    }
    return;
}
void JsonEncode::endmap() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    yyjson_mut_val * JsonArr = m_Items.top().Json;
    std::string sArrKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG(" endmap  key=%s item=%d size=%ld\n", sArrKey.c_str(), cItem, m_Items.size());
    return;
}
void JsonEncode::addbuf(const char* buf,int len) {
    return;
}
void JsonEncode::encode(const char *key, const char & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_int(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####char insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_int(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@char insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const bool & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_bool(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####bool insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_bool(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@bool insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}
void JsonEncode::encode(const char *key, const int & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_int(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####int insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_int(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@int insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}
void JsonEncode::encode(const char *key, const int8_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_int(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####int insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_int(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@int insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}
void JsonEncode::encode(const char *key, const int16_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_int(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####int insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_int(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@int insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const int64_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_int(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####int insert father=%s  key=%s val=%ld size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_int(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@int insert  key=%s val=%ld size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const uint8_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_uint(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####uint insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_uint(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@uint insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const uint16_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_uint(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####uint insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_uint(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@uint insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const uint32_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_uint(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####uint insert father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_uint(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@uint insert  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const uint64_t & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_uint(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####uint insert father=%s  key=%s val=%ld size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_uint(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@uint insert  key=%s val=%ld size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const float & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_real(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####float insert father=%s  key=%s val=%f size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_real(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@float insert  key=%s val=%f size=%ld\n", key, o, m_Items.size());
    }
}

void JsonEncode::encode(const char *key, const double & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_real(JsonDoc, Jsonbase, o);
        MY_LOGDBG("#####double insert father=%s  key=%s val=%f size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        yyjson_mut_obj_add_real(JsonDoc, Jsonbase, key, o);
        MY_LOGDBG("@@@@@double insert  key=%s val=%f size=%ld\n", key, o, m_Items.size());
    }
};

void JsonEncode::encode(const char *key, const std::string & o) {
    if (error_code > 0) return;
    char cItem = m_Items.top().cCurItem;
    yyjson_mut_val * Jsonbase = m_Items.top().Json;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        yyjson_mut_arr_add_str(JsonDoc, Jsonbase, o.c_str());
        MY_LOGDBG("#####str insert father=%s  key=%s val=%s size=%ld\n", m_Items.top().keyName.c_str(), key, o.c_str(), m_Items.size());
    } else {
        yyjson_mut_obj_add_str(JsonDoc, Jsonbase, key, o.c_str());
        MY_LOGDBG("@@@@@str insert  key=%s val=%s size=%ld\n", key, o.c_str(), m_Items.size());
    }
};
void JsonEncode::result(gomros::common::DataBuf& buf) {
    const char *json = yyjson_mut_write(JsonDoc, 0, NULL);
    MY_LOGDBG(" 序列化————结果数据=%s\n",json);
    buf.From(json,strlen(json)+YYJSON_PADDING_SIZE,true);
    buf.buf[buf.buflen-YYJSON_PADDING_SIZE] = ('\0');
    buf.buf[buf.buflen-YYJSON_PADDING_SIZE+1] = ('\0');
    buf.buf[buf.buflen-YYJSON_PADDING_SIZE+2] = ('\0');
    buf.buf[buf.buflen-YYJSON_PADDING_SIZE+3] = ('\0');
    MY_LOGDBG(" 数据长度=%ld  strlen(json)=%ld\n",buf.buflen, strlen(json));
    yyjson_mut_doc_free(JsonDoc);
}



/********************反序列化类************************/
JsonDecode::JsonDecode() {

}
int JsonDecode::format() {
    int ret = GOMROS_SERIAL_XML;
    return ret;
}
void JsonDecode::from(gomros::common::DataBuf& buf) {
    error_code = 0;
    m_pos = 0;
    if (buf.datalen <= 0) {
        error_code = 1;
        MY_LOGDBG(" 待序列化的json 数据 长度异常\n");
        return;
    }
    std::string str = (buf.buf);
    MY_LOGDBG(" 待序列化的json 数据 = %s\n",str.c_str());
    JsonDoc = yyjson_read(str.c_str(), str.length(), 0);
    if( JsonDoc == nullptr ) {
        MY_LOGDBG(" Failed to load Json:  = %s\n",str.c_str());
        error_code = 1;
    }
    
    jItemSts item;
    m_Items.push(item);
}
void JsonDecode::de_beginobject(const char *key) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_OBJECT;
    CurItem.cParentItem = m_Items.top().cCurItem;
    
    char cItem = CurItem.cParentItem;
    yyjson_val * Jval;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_arr_iter_next(&curIter);
        m_Items.top().Arryiter = curIter;
    } else {
        Jval = yyjson_obj_get(Jsonbase,key);
        if (firstobj) {
        Jval= yyjson_doc_get_root(JsonDoc);
        BaseObj = Jval;
        firstobj = false;
        if(yyjson_obj_size(Jval) <= 0)
        ret = false;
        }
    }
    
    CurItem.nJson = Jval;
    CurItem.keyName = key;
    m_Items.push(CurItem);
    MY_LOGDBG(" de beginobject  key=%s item=%d size=%ld,ret=%d\n", key, CurItem.cParentItem, m_Items.size(),ret);
    if ((!yyjson_is_ctn(Jval))||(!ret)) {
        error_code = 2;
     MY_LOGDBG(" de beginobject  ret=%d\n",ret);
    }
    return;
}

void JsonDecode::de_endobject() {
    if (error_code > 0) return;
    std::string sObjKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG("de endobject fatherkey=%s size=%ld\n", sObjKey.c_str(), m_Items.size());
    if (m_Items.size() == 1)
    yyjson_doc_free(JsonDoc);
    return;
}

void JsonDecode::de_beginarray(const char *key) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_ARRAY;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_val * Jval;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_arr_iter_next(&curIter);
    } else {
        Jval = yyjson_obj_get(Jsonbase,key);
        MY_LOGDBG("debeginarry  key=%s \n", key);
        ret = yyjson_arr_iter_init(Jval, &curIter);
    }

    CurItem.nJson = Jval;
    CurItem.keyName = key;
    CurItem.Arryiter = curIter;
    m_Items.push(CurItem);

    if ((Jval == NULL)|| (!ret)) {
        error_code = 3;
        MY_LOGDBG("de beginarray  key=%s item=%d size=%ld, ret=%d\n", key, cItem, m_Items.size(),ret);
    }
    return;
}

void JsonDecode::de_endarray() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    std::string sArrKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG("de endarray father key=%s item=%d size=%ld\n", sArrKey.c_str(), cItem, m_Items.size());
    return;
}
    
void JsonDecode::de_beginlist(const char *key,int& count) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_LIST;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_val * Jval;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_arr_iter_next(&curIter);
    } else {
        Jval = yyjson_obj_get(Jsonbase,key);
        MY_LOGDBG("debeginlist  key=%s\n",key);
        ret = yyjson_arr_iter_init(Jval, &curIter);
    }
    
    CurItem.nJson = Jval;
    CurItem.keyName = key;
    CurItem.Arryiter = curIter;
    m_Items.push(CurItem);
    int size = 0;
    yyjson_arr_iter iter = curIter;
    yyjson_val * val;
    while ((val = yyjson_arr_iter_next(&iter))) {
    size++;
    }
    count = size;
    if ((Jval == NULL)|| (!ret)) {
        error_code = 4;
        MY_LOGDBG("de beginlist  key=%s item=%d size=%ld, ret=%d\n", key, cItem, m_Items.size(),ret);
    }
    return;
}

void JsonDecode::de_endlist() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    std::string sArrKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG(" de_endlist father key=%s item=%d size=%ld\n", sArrKey.c_str(), cItem, m_Items.size());
    return;
}

void JsonDecode::de_beginmap(const char *key,int& count) {
    if (error_code > 0) return;
    jItemSts CurItem;
    CurItem.cCurItem = jITEM_MAP;
    CurItem.cParentItem = m_Items.top().cCurItem;
    char cItem = CurItem.cParentItem;
    yyjson_val * Jval;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    bool ret = true;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        Jval = yyjson_arr_iter_next(&curIter);
    } else {
        Jval = yyjson_obj_get(Jsonbase,key);
        MY_LOGDBG("de_beginmap  key=%s\n",key);
        ret = yyjson_arr_iter_init(Jval, &curIter);
    }

    CurItem.nJson = Jval;
    CurItem.keyName = key;
    CurItem.Arryiter = curIter;
    m_Items.push(CurItem);
    int size = 0;
    yyjson_arr_iter iter = curIter;
    yyjson_val * val;
    while ((val = yyjson_arr_iter_next(&iter))) {
    size++;
    }
    count = size;
    if ((Jval == NULL)|| (!ret)) {
        error_code = 5;
        MY_LOGDBG("de_beginmap  key=%s item=%d size=%ld, ret=%d\n", key, cItem, m_Items.size(),ret);
    }
    return;
}

void JsonDecode::de_endmap() {
    if (error_code > 0) return;
    char cItem = m_Items.top().cParentItem;
    std::string sArrKey = m_Items.top().keyName;
    if (m_Items.size()>0)
    m_Items.pop();

    MY_LOGDBG(" de_endmap father key=%s item=%d size=%ld\n", sArrKey.c_str(), cItem, m_Items.size());
    return;
}


void JsonDecode::readbuf(char* buf,int len) {
    buf[0] = GOMROS_SERIAL_JSON;
    return;
}

bool JsonDecode::decode(const char *key, bool & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_bool(val);
        MY_LOGDBG("#####bool pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_bool(val);
        MY_LOGDBG("@@@@@bool pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, char & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_int(val);
        MY_LOGDBG("#####char pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_int(val);
        MY_LOGDBG("@@@@@char pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, int & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_int(val);
        MY_LOGDBG("#####int pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_int(val);
        MY_LOGDBG("@@@@@int pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, int8_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_int(val);
        MY_LOGDBG("#####int8_t pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_int(val);
        MY_LOGDBG("@@@@@int8_t pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, int16_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_int(val);
        MY_LOGDBG("#####int16_t pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_int(val);
        MY_LOGDBG("@@@@@int16_t pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, int64_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_int(val);
        MY_LOGDBG("#####int64_t pull father=%s  key=%s val=%ld size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_int(val);
        MY_LOGDBG("@@@@@int64_t pull  key=%s val=%ld size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, uint8_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_uint(val);
        MY_LOGDBG("#####uint8_t pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_uint(val);
        MY_LOGDBG("@@@@@uint8_t pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, uint16_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_uint(val);
        MY_LOGDBG("#####uint16_t pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_uint(val);
        MY_LOGDBG("@@@@@uint16_t pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, uint32_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_uint(val);
        MY_LOGDBG("#####uint32_t pull father=%s  key=%s val=%d size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_uint(val);
        MY_LOGDBG("@@@@@uint32_t pull  key=%s val=%d size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, uint64_t & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_uint(val);
        MY_LOGDBG("#####uint64_t pull father=%s  key=%s val=%ld size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_uint(val);
        MY_LOGDBG("@@@@@uint64_t pull  key=%s val=%ld size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, float & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_real(val);
        MY_LOGDBG("#####float pull father=%s  key=%s val=%f size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_real(val);
        MY_LOGDBG("@@@@@float pull  key=%s val=%f size=%ld\n", key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, double & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_real(val);
        MY_LOGDBG("#####double pull father=%s  key=%s val=%f size=%ld\n", m_Items.top().keyName.c_str(), key, o, m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_real(val);
        MY_LOGDBG("@@@@@double pull  key=%s val=%f size=%ld\n",key, o, m_Items.size());
    }
    return true;
}

bool JsonDecode::decode(const char *key, std::string & o) {
    if (error_code > 0) return false;
    char cItem = m_Items.top().cCurItem;
    yyjson_val * Jsonbase = m_Items.top().nJson;
    yyjson_arr_iter curIter= m_Items.top().Arryiter;
    yyjson_val *val;
    if ((cItem == jITEM_LIST) ||
    (cItem == jITEM_ARRAY) ||
    (cItem == jITEM_MAP)) {
        if ((val = yyjson_arr_iter_next(&curIter)))
        m_Items.top().Arryiter = curIter;
        else
        return false;
        o = yyjson_get_str(val);
        MY_LOGDBG("#####string pull father=%s  key=%s val=%s size=%ld\n", m_Items.top().keyName.c_str(), key, o.c_str(), m_Items.size());
    } else {
        val = yyjson_obj_get(Jsonbase, key);
        o = yyjson_get_str(val);
        MY_LOGDBG("@@@@@string pull  key=%s val=%s size=%ld\n", key, o.c_str(), m_Items.size());
    }
    return true;
};

}  // namespace serialize
}  // namespace gomros
