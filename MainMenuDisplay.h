#pragma once
#include "menuInteract.h"

#define  TITLE  "ѧ����Ϣ����ϵͳ"
#define _QUIT 0
#define _SIGN_UP 1
#define _SIGN_IN 2
#define _ADMIN 3








//��ʾ���˵�
char* mainMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺�ע�� ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺ŵ�¼ ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ���������Ա�˺ŵ�¼ *************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������˳�����  ******************************      *"
};




int MAIN_MainDisplay(int posY)
{
	int ret;
	int index = 0;
	HANDLE hOut;
	//��ȡ��ǰ�ľ��---����Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	//���ù�겻�ɼ� FALSE   
	cci.bVisible = 0;
	//����(Ӧ��)�����Ϣ
	SetConsoleCursorInfo(hOut, &cci);
	while (true)
	{
		MAIN_MenuDisplay(hOut, mainMenu, NR(mainMenu), index, posY);
		ret = MAIN_GetUserInput(&index, NR(mainMenu));
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			switch (index)
			{
			case 0:     return 1;  	//ѧ���˺�ע��
			case 1:     return 2;  	//ѧ���˺ŵ�¼
			case 2:     return 3;  	//����Ա�˺ŵ�¼
			case 3:     return 0;		//�˳�
			}
		}
	}

}