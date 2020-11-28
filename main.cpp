#include "identity_class.h"
#include <fstream>
#include "global_file.h"
#include "students.h"
#include "teachers.h"
#include "administrator.h"



void Login_In(string fileName, int type);		//声明全局登录函数   ##参数1：操作的文件名   参数2：身份(学生/老师/管理员)



int main()
{

	int select = 0;					//用于接收用户选择输入

	while (true)
	{

		cout << "======================  机房预约系统  =====================" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学    生           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		cin >> select;				

		switch (select)
		{
		case 1:  //学生身份
			Login_In(STUDENT_FILE, 1);
			break;

		case 2:  //老师身份
			Login_In(TEACHER_FILE, 2);
			break;

		case 3:  //管理员身份
			Login_In(ADMIN_FILE, 3);
			break;

		case 0:  //退出系统
			
			cout << "退出系统成功！" << endl;
			system("pause");
			return 0;

			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;


}


//登陆和登录验证
void Login_In(string fileName, int type)
{
	
	ifstream ifs;

	int id = 0;
	string name;
	string password;
	
	Identity* person = NULL;
	
	ifs.open(fileName, ios::in);



	//文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在!" << endl;
		ifs.close();
		return;
	}




	if (type == 1)		//学生登陆
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}

	if (type == 2)		//教师登陆
	{
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
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
				cout << "学生验证登陆成功！" << endl;

				system("pause");
				system("cls");

				//创建学生对象,实现多态，进入管理员子菜单
				person = new Students(id, name, password);
				studentMenu(person);


				return;
			}
		}
	}
	
		else if (type == 2)		//教师登陆验证
		{
		int fId;
		string fName;
		string fPassword;
		while (ifs >> fId && ifs >> fName && ifs >> fPassword)
		{
			if (id == fId && name == fName && password == fPassword)
			{
				cout << "教师验证登录成功!" << endl;
				system("pause");
				system("cls");

				//创建教师对象,实现多态，进入教师子菜单
				person = new Teacher(id, name, password);
				TeacherMenu(person);

				return;
			}
		}
	}
		else if (type == 3)		//管理员登陆验证
		{
		string fName;
		string fPassword;
		while (ifs >> fName && ifs >> fPassword)
		{
			if (name == fName && password == fPassword)
			{
				cout << "验证登录成功!" << endl;
				//登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");

				//创建管理员对象,实现多态，进入管理员子菜单
				person = new Administrator(name, password);
				AdministratorMenu(person);

				return;
			}
		}
		}
		cout << "密码或账号错误，请重新输入!" << endl;

	system("pause");
	system("cls");

	return;


}



