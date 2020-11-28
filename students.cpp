#include "students.h"
#include <fstream>
#include "global_file.h"
#include "Order_File.h"


//ѧ���Ӳ˵�
void studentMenu(Identity*& student)
{
	while (true)
	{
		//��ʾѧ���˵�
		student->identity_Menu();

		Students* stu = (Students*)student;
		int select = 0;

		cin >> select;

		if (select == 1) //����ԤԼ
		{
			stu->Apply_Order();
		}
		else if (select == 2) //�鿴����ԤԼ
		{
			stu->Show_MyOrder();
		}
		else if (select == 3) //�鿴����ԤԼ
		{
			stu->Show_AllOrder();
		}
		else if (select == 4) //ȡ��ԤԼ
		{
			stu->Cancel_Order();
		}
		else
		{
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

Students::Students()
{

}

Students::Students(int id, string name, string password)
{
	//��ʼ��
	this->S_id = id;
	this->m_Name = name;
	this->m_Password = password;

	this->Init_Vector();		//�ӻ����ļ��л�û�����Ϣ
}

Students::~Students()
{

}

void Students::identity_Menu()
{
	cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

void Students::Init_Vector()
{
	//��ȡ������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	Computer_Room c;
	while (ifs >> c.Com_Id && ifs >> c.Max_Num)
	{
		SC_v.push_back(c);
	}

	ifs.close();
}

void Students::Apply_Order()
{
	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	
	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "������������������" << endl;
	}


	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "��ѡ�������" << endl;
	cout << "1�Ż���������" << SC_v[0].Max_Num<< endl;
	cout << "2�Ż���������" << SC_v[1].Max_Num << endl;
	cout << "3�Ż���������" << SC_v[2].Max_Num << endl;

	while (true)
	{
		cin >> room;		//ѡ��ԤԼ�Ļ���
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;


	//д�뱣��ԤԼ��Ϣ���ļ���,��ʽΪ���ܼ� ������ ѧ��id ѧ������ ��������
	//�ؼ�����ʾ����Ϣ�ɶԣ��Ǳ��ں��ڶ�ȡ����ʱʹ��map����
	ofstream ofs(ORDER_FILE, ios::app);		
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->S_id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;				//��־�����ں����ʦ����Ƿ�ͨ��

	ofs.close();

	system("pause");
	system("cls");
}

void Students::Show_MyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)			//����map����
	{
		if (atoi(of.m_Order_Data[i]["stuId"].c_str()) == this->S_id)			//atoi��һ��ָ��ָ����ַ���ת��Ϊ���Ρ������ҵ�����ѧ���Լ�������
		{
			cout << "ԤԼ���ڣ� ��" << of.m_Order_Data[i]["date"];
			cout << " ʱ�Σ�" << (of.m_Order_Data[i]["interval"] == "1" ? "����" : "����");
			cout << " ������" << of.m_Order_Data[i]["roomId"];
			string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
			if (of.m_Order_Data[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_Order_Data[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_Order_Data[i]["status"] == "-1")
			{
				status += "���δͨ����ԤԼʧ��";
			}
			else
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;

		}
	}

	system("pause");
	system("cls");
}


void Students::Show_AllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)		//�ж��Ƿ��м�¼
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)		//��������ӡ�����±�ķ�ʽ��Ҳ���Ե������ķ�ʽ����������ʹ���㷨for_each
	{
		cout << i + 1 << "�� ";

		cout << "ԤԼ���ڣ� ��" << of.m_Order_Data[i]["date"];
		cout << " ʱ�Σ�" << (of.m_Order_Data[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << of.m_Order_Data[i]["stuId"];
		cout << " ������" << of.m_Order_Data[i]["stuName"];
		cout << " ������" << of.m_Order_Data[i]["roomId"];

		string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
		if (of.m_Order_Data[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_Order_Data[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_Order_Data[i]["status"] == "-1")
		{
			status += "���δͨ����ԤԼʧ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

void Students::Cancel_Order()
{
	OrderFile of;		//�ж��Ƿ�Ϊ��
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������Ҫȡ���ļ�¼" << endl;

	vector<int>v;		//�洢����������map������keyֵ
	int index = 1;

	//������ӡ��¼ѧ������������к�ԤԼ�ɹ��ļ�¼
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_Order_Data[i]["stuId"].c_str()) == this->S_id)	   //�ж��Ƿ��Ǹ�ѧ���ļ�¼
		{
			if (of.m_Order_Data[i]["status"] == "1" || of.m_Order_Data[i]["status"] == "2")	 //����л���ԤԼ�ɹ��ļ�¼
			{
				v.push_back(i);

				//��ӡ����������
				cout << index++ << "�� ";	
				cout << "ԤԼ���ڣ� ��" << of.m_Order_Data[i]["date"];
				cout << " ʱ�Σ�" << (of.m_Order_Data[i]["interval"] == "1" ? "����" : "����");
				cout << " ������" << of.m_Order_Data[i]["roomId"];

				string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
				if (of.m_Order_Data[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_Order_Data[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}

				cout << status << endl;

			}
		}
	}

	cout << "������ȡ���ļ�¼,0������" << endl;

	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//	cout << "��¼����λ�ã� " << v[select - 1] << endl;
				of.m_Order_Data[v[select - 1]]["status"] = "0";
				of.UpdateOder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}

		}
		cout << "������������������" << endl;
	}

	system("pause");
	system("cls");
}