#pragma once

/*用于管理与预约相关的操作*/

#include <iostream>
#include <map>
#include "global_file.h"

using namespace std;

//预约文件管理类
class OrderFile
{
public:

	OrderFile();

	void UpdateOder();		//更新

	map<int, map<string, string>> m_Order_Data;	   //记录信息的容器，key值：记录的条数   value值：键值对信息（因为学生预约时，写入文件中的各个信息都有其标识符成对）

	//记录条数
	int m_Size;
};