#pragma once

/*���ڹ�����ԤԼ��صĲ���*/

#include <iostream>
#include <map>
#include "global_file.h"

using namespace std;

//ԤԼ�ļ�������
class OrderFile
{
public:

	OrderFile();

	void UpdateOder();		//����

	map<int, map<string, string>> m_Order_Data;	   //��¼��Ϣ��������keyֵ����¼������   valueֵ����ֵ����Ϣ����Ϊѧ��ԤԼʱ��д���ļ��еĸ�����Ϣ�������ʶ���ɶԣ�

	//��¼����
	int m_Size;
};