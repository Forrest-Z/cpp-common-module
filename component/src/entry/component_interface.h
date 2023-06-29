#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void ComponentInit(char* config_xml_string, int len);


void ComponentSetConfigFunc(void (*f)(char* config_xml_string, int len));

void ComponentDestroy();

void ComponentExitAction();

#ifdef __cplusplus
}
#endif