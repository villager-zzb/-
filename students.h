#pragma once

/*  学生类需实现功能：
1、 显示学生操作的菜单界面
2、 申请预约
1、 查看自身预约
4、 查看所有预约
5、 取消预约*/


#include "identity_class.h"
#include <vector>
#include "Computer_Room.h"


//学生相应功能菜单函数
void studentMenu(Identity*& student);

class Students : public Identity
{
public:
	Students();


	Students(int id, string name, string password);			//有参构造

	virtual void identity_Menu();			//学生菜单界面

	void Apply_Order();						//申请预约

	void Init_Vector();						//获得机房信息

	void Show_MyOrder();					//查看我的预约

	void Show_AllOrder();					//查看所有预约

	void Cancel_Order();					//取消预约

	~Students();


public:
	int S_id;			//学生id
	vector<Computer_Room> SC_v;		//学生可以看到机房信息

};