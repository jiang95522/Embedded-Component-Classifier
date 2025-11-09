#ifndef __COMPONENT_DATA_STRUCTH_H
#define __COMPONENT_DATA_STRUCTH_H
#include "sys.h"
/** 
* @file component_data_struct
* @brief 元器件数据结构的定义和管理以及相应操作的实现（增删查改）
* @version 1.0 （版本声明） 
* @author jjh
* @date  2025年11月8日 9
*/ 

#define MAX_COMPONENT 100   //元器件最大数量
#define MAX_CATEGORIES 20   //种类最大数量

//元器件
typedef struct component
{
	u8 name[20];    				//名称 100nf电容
	u8 package[10];  				//封装 0603
	u8 location_box;    		//存储的盒子 A B C D 
	u8 row;                 //行
	u8 column;              //列
	u16 search_count;				//搜索次数
	u8 description[150]; 		//描述
	u8 stock_level;  				//库存等级
	u8 extension;      			//扩展
	u8 search_level;				//搜索等级
	u8 component_flag_empty;//是否为空标志位
	
}component;

//元器件种类管理
typedef struct category
{
	u8 name[20];  												//种类名称
	component components[MAX_COMPONENT];  //一种元器件的所有元器件 如电容类别 有最多一百种电容
	u8 component_current_count;     		  //该种类现有元器件数量
	u16 total_searches;             		  //该种类搜索总次数
	u8 category_flag_empty;							  //是否为空标志位
	u8 available_component_space;         //剩余元器件空间个数
	
}category;

//数据库管理
typedef struct component_db
{
	category categories[MAX_CATEGORIES];  //所有类别数组
	u8 current_categories;								//当前类别数量
	u16 total_components; 								//元器件总数
	u32 total_searches;   								//总共搜索次数
	u16 low_stock_count;  								//低库存元器件个数
	u8 available_category_space;          //剩余种类空间个数
	
}component_db;



#endif










