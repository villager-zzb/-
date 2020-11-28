#pragma once

/*  ѧ������ʵ�ֹ��ܣ�
1�� ��ʾѧ�������Ĳ˵�����
2�� ����ԤԼ
1�� �鿴����ԤԼ
4�� �鿴����ԤԼ
5�� ȡ��ԤԼ*/


#include "identity_class.h"
#include <vector>
#include "Computer_Room.h"


//ѧ����Ӧ���ܲ˵�����
void studentMenu(Identity*& student);

class Students : public Identity
{
public:
	Students();


	Students(int id, string name, string password);			//�вι���

	virtual void identity_Menu();			//ѧ���˵�����

	void Apply_Order();						//����ԤԼ

	void Init_Vector();						//��û�����Ϣ

	void Show_MyOrder();					//�鿴�ҵ�ԤԼ

	void Show_AllOrder();					//�鿴����ԤԼ

	void Cancel_Order();					//ȡ��ԤԼ

	~Students();


public:
	int S_id;			//ѧ��id
	vector<Computer_Room> SC_v;		//ѧ�����Կ���������Ϣ

};