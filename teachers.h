#pragma once

/*老师类需实现功能：

1、显示教师操作的菜单界面

2、查看所有预约

3、审核预约

*/

#include "identity_class.h"

void TeacherMenu(Identity*& teacher);

class Teacher : public Identity
{
public:
	Teacher();

	Teacher(int id, string name, string password);

	virtual void identity_Menu();	//菜单界面

	void Show_AllOrder();		//查看所有预约

	void Valid_Order();			//审核预约

	~Teacher();

public:
	int T_id;					//老师id
};