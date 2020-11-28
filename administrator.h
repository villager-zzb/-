#pragma once

/*管理员类需实现功能：

1、显示管理员操作的菜单界面

2、添加账号(管理员可以添加学生与教师账号)

3、查看账号

4、查看机房信息

5、清空预约记录

6、注销登陆

*/

#include "identity_class.h"
#include <vector>
#include "students.h"
#include "teachers.h"
#include "Computer_Room.h"


//管理员相应功能菜单函数
void AdministratorMenu(Identity*& administrator);



//管理员类
class Administrator : public Identity
{
public:
	Administrator();

	Administrator(string name, string password);	//有参构造函数用于初始数据（如从文件中获得） 


	virtual void identity_Menu();	//选择菜单

	void Add_Person();	//添加账号  

	void Show_Person();	//查看账号

	void Show_Computer();	//查看机房信息

	void Clean_File();	//清空预约记录（即清空保存预约记录信息的文件夹）

	void InitVector();	//初始化，获得学生和教师文件中的内容

	bool CheckRepeat(int id,int type);		//检测添加的数据与已有文件是否重复

	~Administrator();

public:
	vector<Students> S_v;		//学生信息容器

	vector<Teacher> T_v;		//教师信息容器

	vector<Computer_Room> C_v;	//机房信息容器
};