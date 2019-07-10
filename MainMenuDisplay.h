#pragma once
#include "menuInteract.h"

#define  TITLE  "学生信息管理系统"
#define _QUIT 0
#define _SIGN_UP 1
#define _SIGN_IN 2
#define _ADMIN 3








//显示主菜单
char* mainMenu[] =
{
	(char*)"* 请选择您将要进行的操作：学生账号注册 ***************************      *",
	(char*)"* 请选择您将要进行的操作：学生账号登录 ***************************      *",
	(char*)"* 请选择您将要进行的操作：管理员账号登录 *************************      *",
	(char*)"* 请选择您将要进行的操作：退出程序  ******************************      *"
};




int MAIN_MainDisplay(int posY)
{
	int ret;
	int index = 0;
	HANDLE hOut;
	//获取当前的句柄---设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见 FALSE   
	cci.bVisible = 0;
	//设置(应用)光标信息
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
			case 0:     return 1;  	//学生账号注册
			case 1:     return 2;  	//学生账号登录
			case 2:     return 3;  	//管理员账号登录
			case 3:     return 0;		//退出
			}
		}
	}

}