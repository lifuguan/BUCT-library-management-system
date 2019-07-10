#pragma once

#include "menuInteract.h"
#include "StuJsonOperate.h"


char* stuMenu[] =
{
	(char*)"* 请选择您将要进行的操作：借阅书籍     ***************************      *",
	(char*)"* 请选择您将要进行的操作：归还书籍     ***************************      *",
	(char*)"* 请选择您将要进行的操作：查看个人信息 ***************************      *",
	(char*)"* 请选择您将要进行的操作：学生账号退出 ***************************      *"
};


int stuNumber, classNumber;
char name[50], passwd[50], passwdText[50];



void MAIN_SignUpDisplay()
{
	system("cls");
	printf_s("                          *************************************************************************\n");
	printf_s("                          *                                                                       *\n");
	printf_s("                          * 欢迎注册北京化工大学图书馆信息管理系统，下面请跟随系统提示注册您的账号*\n");
	printf_s("                          * 请输入您的姓名:");
	scanf("%s", &name);
	printf_s("                          * 请输入您的学号:");
	scanf("%d", &stuNumber);
	while (2015000000 > stuNumber || stuNumber > 2019999999)
	{
		printf_s("                          * 请再次确认您的学号:");
		scanf("%d", &stuNumber);;
	}
	printf_s("                          * 请输入您的班级:");
	scanf("%d", &classNumber);
	printf_s("                          * 请设置您的密码:");
	scanf("%s", &passwd);
	printf_s("                          * 请再次确认您的密码:");
	scanf("%s", &passwdText);
	while (strcmp(passwd, passwdText) != 0)
	{
		printf_s("                          * 请再次确认您的密码:");
		scanf("%s", &passwdText);
	}
	//Json交互
	stuJson = File_AddStuInfoToJson(File_ReadStuInfoToJson(), name, passwd, classNumber, stuNumber);
	//printf("                          ");
	color(2);
	printf_s("                                           <<<<<<<<<<<<<<<<注册成功！>>>>>>>>>>>>>>>>>>            \n\n");
	color(3);
	printf_s("                          *************************************************************************\n\n");
	printf_s("-----------------------------------------------------------------------------------------------------------------------\n");
	system("pause");
}

int MAIN_SignInDisplay()
{
	system("cls");
	printf("                          \n");
	printf_s("                          *************************************************************************\n");
	printf_s("                          *                                                                       *\n");
	printf_s("                          * 欢迎登陆北京化工大学图书馆信息管理系统\n");
	printf_s("                          * 请输入您的姓名:");
	scanf("%s", &name);
	for (int i = 0; i <= 2; i++)
	{
		printf_s("                          * 您有'%d'次机会，请输入正确的密码*\n", 3 - i);
		printf_s("                          * 请输入您的密码:");
		scanf("%s", &passwd);
		//若未登录，首次读取
		if (stuJson == NULL)
		{
			stuJson = File_ReadStuInfoToJson();
		}
		bool res = FILE_StuPasswdCompare(stuJson, name, passwd);

		if (res == true)
		{
			system("cls");
			//变绿色
			color(2);
			printf_s("\n                                           <<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>>              \n\n");
			color(3);
			printf_s("                          *************************************************************************\n");
			printf_s("                          *                                                                       *\n");
			printf("\n\n\n\n");
			printf_s("                          *                                                                       *\n");
			printf_s("                          *************************************************************************\n");
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
				MAIN_MenuDisplay(hOut, stuMenu, NR(stuMenu), index, 5);
				ret = MAIN_GetUserInput(&index, NR(stuMenu));
				if (ret == ESC)
					break;
				if (ret == ENTER)
				{
					switch (index)
					{
					case 0:     return 1;  	//添加新的书籍
					case 1:     return 2;  	//删除已有的书籍
					case 2:     return 3;
					case 3:		return 0;	//退出
					}
				}
			}
		}
		else
		{
			color(4);
			printf_s("                                           <<<<<<<<<<密码错误,请重新输入!>>>>>>>>>>>>              \n\n");
			color(3);
		}
	}
}

