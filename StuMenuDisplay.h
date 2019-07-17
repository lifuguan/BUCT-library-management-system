#pragma once

#include "menuInteract.h"
#include "StuJsonOperate.h"
#include "BookJsonOperate.h"

char* stuMenu[] =
{
	(char*)"* 请选择您将要进行的操作：借阅书籍     ***************************      *",
	(char*)"* 请选择您将要进行的操作：归还书籍     ***************************      *",
	(char*)"* 请选择您将要进行的操作：查看个人信息 ***************************      *",
	(char*)"* 请选择您将要进行的操作：学生账号退出 ***************************      *"
};


int stuNumber, classNumber;
char name[50], passwd[50], passwdText[50];



void MAIN_StuSignUpDisplay()
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

bool STU_SignInDisplay()
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
			return true;
		}
		else
		{
			color(4);
			printf_s("                                           <<<<<<<<<<密码错误,请重新输入!>>>>>>>>>>>>              \n\n");
			color(3);
		}
	}
	return false;
}

int STU_MainMenuDisplay()
{
	//变绿色
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("\n\n\n\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
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
		MAIN_MenuDisplay(hOut, stuMenu, NR(stuMenu), index, 5, 26);
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

int STU_QueryAllBookDisplay()
{
	system("cls");
	printf("                          *************************************************************************\n");
	printf("      书名                   出版社                     书籍编号                剩余数量           时间\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
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
		MAIN_MenuDisplay(hOut, stuQueryMenu, bookCnt, index, 4, 5);
		ret = MAIN_GetUserInput(&index, bookCnt);
		if (ret == ESC)
			return 0;
		if (ret == ENTER)
		{
			return index + 1;
		}
	}
}

void STU_BookSelectedEvent(int selected)
{
	system("cls");
	printf("\n\n                                                    是否选择借阅此书\n");
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("\n\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
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
		MAIN_MenuDisplay(hOut, selectedMenu, 2, index, 5, 26);
		ret = MAIN_GetUserInput(&index, 2);
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			if (index == 0)
			{
				FILE_ModifyBookInfoToJson(bookJson, bookName[selected - 1], -1);
				break;
			}
			else
			{
				break;
			}
		}
	}
}



int STU_ReturnBookDisplay(int bookCnt)
{
	system("cls");
	printf("           ************************************选择要归还的书籍*************************************\n");
	printf("      书名                   出版社                     书籍编号                剩余数量           时间\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
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
	while (true)
	{
		MAIN_MenuDisplay(hOut, stuReturnMenu, bookCnt, index, 4, 5);
		ret = MAIN_GetUserInput(&index, bookCnt);
		if (ret == ESC)
			return 0;
		if (ret == ENTER)
		{
			return index + 1;
		}
	}
}

void STU_BookReturnEvent(int selected, char name[50])
{
	system("cls");
	printf("\n\n                                                    是否选择归还此书\n");
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("\n\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
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
		MAIN_MenuDisplay(hOut, selectedMenu, 2, index, 5, 26);
		ret = MAIN_GetUserInput(&index, 2);
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			if (index == 0)
			{
				stuReturnMenu[selected - 1] = NULL;
				
				break;
			}
			else
			{
				break;
			}
		}
	}
}


void MAIN_StuPersonalInfoDisplay(cJSON* stuJson, char name[50])
{
	system("cls");
	cJSON* stu = cJSON_GetObjectItem(stuJson, name);
	
	HANDLE hOut;
	//获取当前的句柄---设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	cci.bVisible = 1;
	//设置(应用)光标信息
	SetConsoleCursorInfo(hOut, &cci);
	color(3);
	printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("                          * 学生姓名   :                                                          *\n"); // 38
	printf("                          * 学生学号   :                                                          *\n");
	printf("                          * 学生班级   :                                                          *\n");
	printf("                          * 已借书目   :                                                          *\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
	color(15);
	pos.X = 41;   pos.Y = 4;

	//清空输入缓存区
	int c;  while ((c = getchar()) != '\n' && c != EOF);
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); printf("%s", name);
	pos.X = 41;   pos.Y = 5;
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); printf("%d", stu->child->valueint);
	pos.X = 41;   pos.Y = 6;
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); printf("%d", stu->child->next->valueint);
	pos.X = 41;   pos.Y = 7;
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); printf("%d\n\n\n", stu->child->next->next->next->valueint);
	pos.X = 41;   pos.Y = 10;
	color(2);
	system("pause");
	color(3);
}
