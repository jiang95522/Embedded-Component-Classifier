#include "component_data_struct.h"

//定义全局变量
component_db component_classifier;   //整个元器件数据库

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
* @return 添加成功：index，添加失败：-1 
*/
int add_category(component_db* db,const char * category_name)
{
	int index;
	if(db->current_categories >= MAX_CATEGORIES)
	{
		printf("错误：类别数量达到上限！ \r\n");
		return -1;
	}
	if(find_category_index(db,category_name) != -1)  
	{
		printf("错误：已有该类别！ \r\n");
	}
	index = find_category_available(db);
	if(index == -1)
	{
		printf("错误：没有可用的类别空间！ \r\n");
		return -1;
	}
	strncpy((char *)(db->categories[index].name), category_name, sizeof(db->categories[index].name) - 1);
	db->categories[index].category_flag_empty=1;
	db->categories[index].available_component_space=MAX_COMPONENT;
	
	db->current_categories++;
	db->available_category_space=MAX_CATEGORIES-db->current_categories;
	printf("成功添加类别：%s \r\n",category_name);
	
	return index;
}
/** 
* @Description:测试添加新类别函数
* @component_db*:数据库结构体指针
*/
void Test_add_categoties(component_db* db)
{
	u8 i=0;
	u8 j=0;
	printf("当前类别个数 %d \r\n", (int)db->current_categories);
	printf("剩余种类空间个数 %d \r\n", (int)db->available_category_space);
	printf("元器件总数 %d \r\n", (int)db->total_components);
	add_category(db, "电容");
	add_category(db, "电阻");
	add_category(db, "电感");
	printf("当前类别个数 %d \r\n", (int)db->current_categories);
	printf("剩余种类空间个数 %d \r\n", (int)db->available_category_space);
	printf("元器件总数 %d \r\n", (int)db->total_components);
	for(i=0;i<MAX_CATEGORIES;i++)
	{
		if(db->categories[i].category_flag_empty!=0)
		{
			j++;
			printf("位置 %d 种类名称: %s \r\n",(int)i,db->categories[i].name);
		}
		if(j == db->current_categories)
		{
			break;
		}
	}
}


















