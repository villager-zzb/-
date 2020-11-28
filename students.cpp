#include "students.h"
#include <fstream>
#include "global_file.h"
#include "Order_File.h"


//学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//显示学生菜单
		student->identity_Menu();

		Students* stu = (Students*)student;
		int select = 0;

		cin >> select;

		if (select == 1) //申请预约
		{
			stu->Apply_Order();
		}
		else if (select == 2) //查看自身预约
		{
			stu->Show_MyOrder();
		}
		else if (select == 3) //查看所有预约
		{
			stu->Show_AllOrder();
		}
		else if (select == 4) //取消预约
		{
			stu->Cancel_Order();
		}
		else
		{
			delete student;
			cout << "注销成功" << endl;
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
	//初始化
	this->S_id = id;
	this->m_Name = name;
	this->m_Password = password;

	this->Init_Vector();		//从机房文件中获得机房信息
}

Students::~Students()
{

}

void Students::identity_Menu()
{
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Students::Init_Vector()
{
	//获取机房信息
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
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	
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
		cout << "输入有误，请重新输入" << endl;
	}


	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请选择机房：" << endl;
	cout << "1号机房容量：" << SC_v[0].Max_Num<< endl;
	cout << "2号机房容量：" << SC_v[1].Max_Num << endl;
	cout << "3号机房容量：" << SC_v[2].Max_Num << endl;

	while (true)
	{
		cin >> room;		//选择预约的机房
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "预约成功！审核中" << endl;


	//写入保存预约信息的文件中,格式为：周几 上下午 学生id 学生姓名 机房房间
	//关键词提示与信息成对，是便于后期读取数据时使用map容器
	ofstream ofs(ORDER_FILE, ios::app);		
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->S_id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;				//标志，用于后面教师审核是否通过

	ofs.close();

	system("pause");
	system("cls");
}

void Students::Show_MyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)			//遍历map容器
	{
		if (atoi(of.m_Order_Data[i]["stuId"].c_str()) == this->S_id)			//atoi将一个指针指向的字符串转化为整形。用以找到到该学生自己的数据
		{
			cout << "预约日期： 周" << of.m_Order_Data[i]["date"];
			cout << " 时段：" << (of.m_Order_Data[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_Order_Data[i]["roomId"];
			string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
			if (of.m_Order_Data[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_Order_Data[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_Order_Data[i]["status"] == "-1")
			{
				status += "审核未通过，预约失败";
			}
			else
			{
				status += "预约已取消";
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
	if (of.m_Size == 0)		//判定是否有记录
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)		//遍历，打印，以下标的方式，也可以迭代器的方式遍历，或者使用算法for_each
	{
		cout << i + 1 << "、 ";

		cout << "预约日期： 周" << of.m_Order_Data[i]["date"];
		cout << " 时段：" << (of.m_Order_Data[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_Order_Data[i]["stuId"];
		cout << " 姓名：" << of.m_Order_Data[i]["stuName"];
		cout << " 机房：" << of.m_Order_Data[i]["roomId"];

		string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_Order_Data[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_Order_Data[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_Order_Data[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

void Students::Cancel_Order()
{
	OrderFile of;		//判定是否为空
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入要取消的记录" << endl;

	vector<int>v;		//存储满足条件的map容器的key值
	int index = 1;

	//遍历打印登录学生的正在审核中和预约成功的记录
	for (int i = 0; i < of.m_Size; i++)
	{
		if (atoi(of.m_Order_Data[i]["stuId"].c_str()) == this->S_id)	   //判定是否是该学生的记录
		{
			if (of.m_Order_Data[i]["status"] == "1" || of.m_Order_Data[i]["status"] == "2")	 //审核中或者预约成功的记录
			{
				v.push_back(i);

				//打印满足条件的
				cout << index++ << "、 ";	
				cout << "预约日期： 周" << of.m_Order_Data[i]["date"];
				cout << " 时段：" << (of.m_Order_Data[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_Order_Data[i]["roomId"];

				string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_Order_Data[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_Order_Data[i]["status"] == "2")
				{
					status += "预约成功";
				}

				cout << status << endl;

			}
		}
	}

	cout << "请输入取消的记录,0代表返回" << endl;

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
				//	cout << "记录所在位置： " << v[select - 1] << endl;
				of.m_Order_Data[v[select - 1]]["status"] = "0";
				of.UpdateOder();
				cout << "已取消预约" << endl;
				break;
			}

		}
		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
	system("cls");
}