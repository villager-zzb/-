#pragma once

#include <iostream>
#include <string>

using namespace std;

class Identity			//抽象身份类
{
public:
	virtual void identity_Menu() = 0;		//各个类的子菜单界面
	

public:
	string m_Name;				//用户名和密码
	string m_Password;

};

