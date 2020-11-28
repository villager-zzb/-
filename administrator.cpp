#include "administrator.h"
#include <fstream>
#include "global_file.h"
#include <algorithm>


//学生和老师和机房信息的打印函数
void Print_S(Students& s)
{
	cout << "学号： " << s.S_id << " 姓名： " << s.m_Name << " 密码：" << s.m_Password << endl;
}
void Print_T(Teacher& t)
{
	cout << "职工号： " << t.T_id << " 姓名： " << t.m_Name << " 密码：" << t.m_Password << endl;
}
void Print_C(Computer_Room& c)
{
	cout << "机房编号： " << c.Com_Id << " 机房最大容量： " << c.Max_Num << endl;
}


//管理员子菜单
void AdministratorMenu(Identity*& administrator)
{
	while (true)
	{
		//显示管理员功能菜单
		administrator->identity_Menu();

		Administrator* man = (Administrator*)administrator;	   //父类指针转为子类指针，用以实现多态
		
		int select = 0;

		cin >> select;

		switch (select)
		{
		case 1:			//添加账号

			cout << "添加账号" << endl;
			man->Add_Person();

			break;
		case 2:			//查看账号

			cout << "查看账号" << endl;
			man->Show_Person();

			break;
		case 3:			//查看机房

			cout << "查看机房" << endl;
			man->Show_Computer();

			break;
		case 4:			//清空预约

			cout << "清空预约" << endl;
			man->Clean_File();

			break;

		default:
			delete administrator;
			cout << "注销成功" << endl;

			system("pause");
			system("cls");
			return;
		}


		
	}
}


//教师子菜单

Administrator::Administrator()
{

}

Administrator::Administrator(string name, string password)
{
	this->m_Name = name;
	this->m_Password = password;

	//初始化学生和教师容器，获得文件中已有的数据
	this->InitVector();

}

Administrator::~Administrator()
{

}

void Administrator::identity_Menu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Administrator::Add_Person()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string FileName;
	string Ip;			//保存选择输出的信息
	ofstream ofs;
	
	string Error;		//检测重复，保存输出的错误信息

	int select = 0;

	while (true)
	{
		
		cin >> select;

		if (select == 1)
		{
			FileName = STUDENT_FILE;
			Ip = "请输入学号： ";
			Error = "学号重复，请重新输入";
		}
		else if (select == 2)
		{
			FileName = TEACHER_FILE;
			Ip = "请输入职工编号：";
			Error = "职工号重复，请重新输入";
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
			continue;
		}

	}

	ofs.open(FileName, ios::out | ios::app);	//写文件，输出，追加方式

	int id;
	string name;
	string password;
	cout << Ip << endl;			//输出对应选择的提示

	while (true)
	{
		cin >> id;
		bool ret = this->CheckRepeat(id, select);

		if (ret) //有重复
		{
			cout << Error << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名： " << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> password;

	ofs << id << " " << name << " " << password << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();

	this->InitVector();			//更新容器
}

void Administrator::Show_Person()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;

	while (true)
	{

		cin >> select;

		if (select == 1)
		{
			cout << "所有学生信息如下： " << endl;
			for_each(S_v.begin(), S_v.end(), Print_S);	//遍历算法遍历
			break;
		}
		else if (select == 2)
		{
			cout << "所有老师信息如下： " << endl;
			for_each(T_v.begin(), T_v.end(), Print_T);	//遍历并打印
			break;
		}
		else
		{
			cout << "输入有误，重新输入： " << endl;
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
	cout << "机房信息如下： " << endl;
	
	for_each(C_v.begin(), C_v.end(), Print_C);

	system("pause");
	system("cls");
}

void Administrator::Clean_File()
{
	ofstream ofs(ORDER_FILE, ios::trunc);	//写方法打开，并清空里面内容
	
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

void Administrator::InitVector()
{
	//读取学生文件中信息
	
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	S_v.clear();		//清空
	T_v.clear();

	Students s;
	while (ifs >> s.S_id && ifs >> s.m_Name && ifs >> s.m_Password)
	{
		S_v.push_back(s);		//将文件中的数据压入学生容器中
	}
	cout << "当前学生数量为： " << S_v.size() << endl;
	
	ifs.close(); //学生初始化完成

	//读取老师文件信息
	ifs.open(TEACHER_FILE, ios::in);

	Teacher t;
	while (ifs >> t.T_id && ifs >> t.m_Name && ifs >> t.m_Password)
	{
		T_v.push_back(t);		//将文件中的数据压入教师容器中		
	}
	cout << "当前教师数量为： " << T_v.size() << endl;

	ifs.close();		//教师信息初始化完成

		//从文件中获取机房信息，并写入到管理员类中的机房容器中

	ifs.open(COMPUTER_FILE, ios::in);

	Computer_Room c;
	while (ifs >> c.Com_Id && ifs >> c.Max_Num)
	{
		C_v.push_back(c);
	}
	cout << "当前机房数量为： " << C_v.size() << endl;

	ifs.close();
}

bool Administrator::CheckRepeat(int id,int type)
{
	if (type == 1)   //添加的数据是学生，遍历学生容器
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
	return false;			//无重复false,有重复ture
}

