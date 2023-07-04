#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void ComponentInit(char* config_xml_string, int len){}

void ComponentChangeParams(char* changed_params_xml_string, int len){}

/**
 * @brief 供组件内部设置修改config
 * 
 * @param f 
 */
void ComponentSetConfigFunc(void (*f)(char* config_xml_string, int len)){}

void ComponentDestroy(){}

#ifdef __cplusplus
}
#endif