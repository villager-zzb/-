#pragma once

/*����Ա����ʵ�ֹ��ܣ�

1����ʾ����Ա�����Ĳ˵�����

2������˺�(����Ա�������ѧ�����ʦ�˺�)

3���鿴�˺�

4���鿴������Ϣ

5�����ԤԼ��¼

6��ע����½

*/

#include "identity_class.h"
#include <vector>
#include "students.h"
#include "teachers.h"
#include "Computer_Room.h"


//����Ա��Ӧ���ܲ˵�����
void AdministratorMenu(Identity*& administrator);



//����Ա��
class Administrator : public Identity
{
public:
	Administrator();

	Administrator(string name, string password);	//�вι��캯�����ڳ�ʼ���ݣ�����ļ��л�ã� 


	virtual void identity_Menu();	//ѡ��˵�

	void Add_Person();	//����˺�  

	void Show_Person();	//�鿴�˺�

	void Show_Computer();	//�鿴������Ϣ

	void Clean_File();	//���ԤԼ��¼������ձ���ԤԼ��¼��Ϣ���ļ��У�

	void InitVector();	//��ʼ�������ѧ���ͽ�ʦ�ļ��е�����

	bool CheckRepeat(int id,int type);		//�����ӵ������������ļ��Ƿ��ظ�

	~Administrator();

public:
	vector<Students> S_v;		//ѧ����Ϣ����

	vector<Teacher> T_v;		//��ʦ��Ϣ����

	vector<Computer_Room> C_v;	//������Ϣ����
};