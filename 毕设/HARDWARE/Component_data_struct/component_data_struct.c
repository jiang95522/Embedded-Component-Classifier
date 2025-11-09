#include "component_data_struct.h"

/** 
* @Description:数据库初始化
* @component_db*:数据库结构体指针
*/
void Init_component_db(component_db* db) 
{
	memset(db,0,sizeof(component_db));
	
}
/** 
* @Description:查找类别空闲位置
* @component_db*:数据库结构体指针
* @return 成功：i，失败：-1 
*/
int find_category_available(component_db* db) 
{
	u8 i=0;
	for(i = 0; i < db->current_categories; i++)
	{
		if(db->categories[i].category_flag_empty==0)
		{
			return i;// 返回下一个可用的位置
		}
	}
	if(i<MAX_CATEGORIES)
	{
		return i;// 返回下一个可用的位置
	}else
	{
		return -1;//种类满了
	}
}
/** 
* @Description:类别索引
* @component_db*:数据库结构体指针
* @return 找到：i，没找到：-1 
*/
int find_category_index(component_db* db,const char * category_name) 
{
	u8 i=0;
	for(i=0; i<MAX_CATEGORIES;i++)
	{
		if(strcmp((const char *)(db->categories[i].name),category_name)==0)  //索引到目标
		{
			return i;
		}
	}
	return -1;
}
/** 
* @Description:添加新类别
* @component_db*:数据库结构体指针
* @category_name:类别名字
*/
int add_category(component_db* db,const char * category_name)
{
	if(db->current_categories>=MAX_CATEGORIES)
	{
		printf("错误：类别数量达到上限！ \r\n");
		return -1;
	}
	
	
}




















