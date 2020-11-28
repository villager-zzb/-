#include "administrator.h"
#include <fstream>
#include "global_file.h"
#include <algorithm>


//ѧ������ʦ�ͻ�����Ϣ�Ĵ�ӡ����
void Print_S(Students& s)
{
	cout << "ѧ�ţ� " << s.S_id << " ������ " << s.m_Name << " ���룺" << s.m_Password << endl;
}
void Print_T(Teacher& t)
{
	cout << "ְ���ţ� " << t.T_id << " ������ " << t.m_Name << " ���룺" << t.m_Password << endl;
}
void Print_C(Computer_Room& c)
{
	cout << "������ţ� " << c.Com_Id << " ������������� " << c.Max_Num << endl;
}


//����Ա�Ӳ˵�
void AdministratorMenu(Identity*& administrator)
{
	while (true)
	{
		//��ʾ����Ա���ܲ˵�
		administrator->identity_Menu();

		Administrator* man = (Administrator*)administrator;	   //����ָ��תΪ����ָ�룬����ʵ�ֶ�̬
		
		int select = 0;

		cin >> select;

		switch (select)
		{
		case 1:			//����˺�

			cout << "����˺�" << endl;
			man->Add_Person();

			break;
		case 2:			//�鿴�˺�

			cout << "�鿴�˺�" << endl;
			man->Show_Person();

			break;
		case 3:			//�鿴����

			cout << "�鿴����" << endl;
			man->Show_Computer();

			break;
		case 4:			//���ԤԼ

			cout << "���ԤԼ" << endl;
			man->Clean_File();

			break;

		default:
			delete administrator;
			cout << "ע���ɹ�" << endl;

			system("pause");
			system("cls");
			return;
		}


		
	}
}


//��ʦ�Ӳ˵�

Administrator::Administrator()
{

}

Administrator::Administrator(string name, string password)
{
	this->m_Name = name;
	this->m_Password = password;

	//��ʼ��ѧ���ͽ�ʦ����������ļ������е�����
	this->InitVector();

}

Administrator::~Administrator()
{

}

void Administrator::identity_Menu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

void Administrator::Add_Person()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string FileName;
	string Ip;			//����ѡ���������Ϣ
	ofstream ofs;
	
	string Error;		//����ظ�����������Ĵ�����Ϣ

	int select = 0;

	while (true)
	{
		
		cin >> select;

		if (select == 1)
		{
			FileName = STUDENT_FILE;
			Ip = "������ѧ�ţ� ";
			Error = "ѧ���ظ�������������";
		}
		else if (select == 2)
		{
			FileName = TEACHER_FILE;
			Ip = "������ְ����ţ�";
			Error = "ְ�����ظ�������������";
		}
		else
		{
			cout << "������������������" << endl;
			continue;
		}

	}

	ofs.open(FileName, ios::out | ios::app);	//д�ļ��������׷�ӷ�ʽ

	int id;
	string name;
	string password;
	cout << Ip << endl;			//�����Ӧѡ�����ʾ

	while (true)
	{
		cin >> id;
		bool ret = this->CheckRepeat(id, select);

		if (ret) //���ظ�
		{
			cout << Error << endl;
		}
		else
		{
			break;
		}
	}
	cout << "������������ " << endl;
	cin >> name;

	cout << "���������룺 " << endl;
	cin >> password;

	ofs << id << " " << name << " " << password << " " << endl;
	cout << "��ӳɹ�" << endl;
	system("pause");
	system("cls");
	ofs.close();

	this->InitVector();			//��������
}

void Administrator::Show_Person()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0;

	while (true)
	{

		cin >> select;

		if (select == 1)
		{
			cout << "����ѧ����Ϣ���£� " << endl;
			for_each(S_v.begin(), S_v.end(), Print_S);	//�����㷨����
			break;
		}
		else if (select == 2)
		{
			cout << "������ʦ��Ϣ���£� " << endl;
			for_each(T_v.begin(), T_v.end(), Print_T);	//��������ӡ
			break;
		}
		else
		{
			cout << "���������������룺 " << endl;
			system("pause");
			system("cls");
			this->identity_Menu();
			continue;

		}
	}
	system("pause");
	system("cls");
}

void Administrator::Show_Computer()
{
	cout << "������Ϣ���£� " << endl;
	
	for_each(C_v.begin(), C_v.end(), Print_C);

	system("pause");
	system("cls");
}

void Administrator::Clean_File()
{
	ofstream ofs(ORDER_FILE, ios::trunc);	//д�����򿪣��������������
	
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

void Administrator::InitVector()
{
	//��ȡѧ���ļ�����Ϣ
	
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	S_v.clear();		//���
	T_v.clear();

	Students s;
	while (ifs >> s.S_id && ifs >> s.m_Name && ifs >> s.m_Password)
	{
		S_v.push_back(s);		//���ļ��е�����ѹ��ѧ��������
	}
	cout << "��ǰѧ������Ϊ�� " << S_v.size() << endl;
	
	ifs.close(); //ѧ����ʼ�����

	//��ȡ��ʦ�ļ���Ϣ
	ifs.open(TEACHER_FILE, ios::in);

	Teacher t;
	while (ifs >> t.T_id && ifs >> t.m_Name && ifs >> t.m_Password)
	{
		T_v.push_back(t);		//���ļ��е�����ѹ���ʦ������		
	}
	cout << "��ǰ��ʦ����Ϊ�� " << T_v.size() << endl;

	ifs.close();		//��ʦ��Ϣ��ʼ�����

		//���ļ��л�ȡ������Ϣ����д�뵽����Ա���еĻ���������

	ifs.open(COMPUTER_FILE, ios::in);

	Computer_Room c;
	while (ifs >> c.Com_Id && ifs >> c.Max_Num)
	{
		C_v.push_back(c);
	}
	cout << "��ǰ��������Ϊ�� " << C_v.size() << endl;

	ifs.close();
}

bool Administrator::CheckRepeat(int id,int type)
{
	if (type == 1)   //��ӵ�������ѧ��������ѧ������
	{
		for (vector<Students>::iterator it = S_v.begin(); it != S_v.end(); it++)
		{
			if (id == it->S_id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = T_v.begin(); it != T_v.end(); it++)
		{
			if (id == it->T_id)
			{
				return true;
			}
		}
	}
	return false;			//���ظ�false,���ظ�ture
}

