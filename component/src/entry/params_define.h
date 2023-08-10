
#pragma once

/**
 * @brief gomros 安装路径
 *
 */
#define GOMROS_INSTALL_PATH "/opt/gomros/run"

/**
 * @brief gomros 安装路径，下一级目录为每个产品的名称
 *
 */
#define GOMROS_DATA_PATH "/opt/gomros/data"

/**
 * @brief 产品配置文件名
 *
 */
#define PRODUCT_CONFIG_FILENAME "product.xml"

/** 
 * @brief 产品修改配置文件名，在 GOMROS_DATA_PATH/${product_name}/
 */
#define PRODUCT_CONFIG_FIX_FILENAME "config.xml"

/**
 * @brief 组件配置文件名
 *
 */
#define COMPONENT_CONFIG_FILENAME "component.xml"

/**
 * @brief CMD 指令
 *
 */
#define CMD_PRODUCT "-product"
#define CMD_PROCESS "-process"
#define CMD_ADD_COMPONENT_PATH "-add_component_path"