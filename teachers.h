#pragma once

/*��ʦ����ʵ�ֹ��ܣ�

1����ʾ��ʦ�����Ĳ˵�����

2���鿴����ԤԼ

3�����ԤԼ

*/

#include "identity_class.h"

void TeacherMenu(Identity*& teacher);

class Teacher : public Identity
{
public:
	Teacher();

	Teacher(int id, string name, string password);

	virtual void identity_Menu();	//�˵�����

	void Show_AllOrder();		//�鿴����ԤԼ

	void Valid_Order();			//���ԤԼ

	~Teacher();

public:
	int T_id;					//��ʦid
};