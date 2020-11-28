#include "identity_class.h"
#include <fstream>
#include "global_file.h"
#include "students.h"
#include "teachers.h"
#include "administrator.h"



void Login_In(string fileName, int type);		//����ȫ�ֵ�¼����   ##����1���������ļ���   ����2�����(ѧ��/��ʦ/����Ա)



int main()
{

	int select = 0;					//���ڽ����û�ѡ������

	while (true)
	{

		cout << "======================  ����ԤԼϵͳ  =====================" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.ѧ    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ʦ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.�� �� Ա           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "��������ѡ��: ";

		cin >> select;				

		switch (select)
		{
		case 1:  //ѧ�����
			Login_In(STUDENT_FILE, 1);
			break;

		case 2:  //��ʦ���
			Login_In(TEACHER_FILE, 2);
			break;

		case 3:  //����Ա���
			Login_In(ADMIN_FILE, 3);
			break;

		case 0:  //�˳�ϵͳ
			
			cout << "�˳�ϵͳ�ɹ���" << endl;
			system("pause");
			return 0;

			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;


}


//��½�͵�¼��֤
void Login_In(string fileName, int type)
{
	
	ifstream ifs;

	int id = 0;
	string name;
	string password;
	
	Identity* person = NULL;
	
	ifs.open(fileName, ios::in);



	//�ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������!" << endl;
		ifs.close();
		return;
	}




	if (type == 1)		//ѧ����½
	{
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}

	if (type == 2)		//��ʦ��½
	{
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> password;

	if (type == 1)
	{
		int fid;
		string fname;
		string fpassword;

		while (ifs >> fid && ifs >> fname && ifs >> fpassword)
		{
			//cout << fid << endl << fname << endl << fpassword << endl;

			if (id == fid && name == fname && password == fpassword)
			{
				cout << "ѧ����֤��½�ɹ���" << endl;

				system("pause");
				system("cls");

				//����ѧ������,ʵ�ֶ�̬���������Ա�Ӳ˵�
				person = new Students(id, name, password);
				studentMenu(person);


				return;
			}
		}
	}
	
		else if (type == 2)		//��ʦ��½��֤
		{
		int fId;
		string fName;
		string fPassword;
		while (ifs >> fId && ifs >> fName && ifs >> fPassword)
		{
			if (id == fId && name == fName && password == fPassword)
			{
				cout << "��ʦ��֤��¼�ɹ�!" << endl;
				system("pause");
				system("cls");

				//������ʦ����,ʵ�ֶ�̬�������ʦ�Ӳ˵�
				person = new Teacher(id, name, password);
				TeacherMenu(person);

				return;
			}
		}
	}
		else if (type == 3)		//����Ա��½��֤
		{
		string fName;
		string fPassword;
		while (ifs >> fName && ifs >> fPassword)
		{
			if (name == fName && password == fPassword)
			{
				cout << "��֤��¼�ɹ�!" << endl;
				//��¼�ɹ��󣬰�������������Ա����
				system("pause");
				system("cls");

				//��������Ա����,ʵ�ֶ�̬���������Ա�Ӳ˵�
				person = new Administrator(name, password);
				AdministratorMenu(person);

				return;
			}
		}
		}
		cout << "������˺Ŵ�������������!" << endl;

	system("pause");
	system("cls");

	return;


}



