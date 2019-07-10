#pragma once

#include "menuInteract.h"
#include "BookJsonOperate.h"


#define _ADMIN_ACCOUNT "root"
#define _ADMIN_PASSWD "root"

char* adminMenu[] =
{
	(char*)"* 请选择您将要进行的操作：添加新的书籍 ***************************      *",
	(char*)"* 请选择您将要进行的操作：删除已有书籍 ***************************      *",
	(char*)"* 请选择您将要进行的操作：管理员账号退出  *************************     *"
};



int MAIN_AdminSignInDisplay()
{
	system("cls");
	int i;

	for (i = 0; i <= 2; i++)
	{
		printf_s("                          * 您有'%d'次机会，请输入正确的密码*\n", 3 - i);
		printf_s("                          * 请输入您的密码:");
		char passwd[10];
		scanf("%s", &passwd);

		if (strcmp(passwd, _ADMIN_PASSWD) == 0)
		{
			system("cls");
			//变绿色
			color(2);
			printf_s("\n                                           <<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>>              \n\n");
			color(3);
			printf_s("                          *************************************************************************\n");
			printf_s("                          *                                                                       *\n");
			printf("\n\n\n");
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
				MAIN_MenuDisplay(hOut, adminMenu, NR(adminMenu), index, 5);
				ret = MAIN_GetUserInput(&index, NR(adminMenu));
				if (ret == ESC)
					break;
				if (ret == ENTER)
				{
					switch (index)
					{
					case 0:     return 1;  	//添加新的书籍
					case 1:     return 2;  	//删除已有的书籍
					case 2:		return 0;	//退出
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

void MAIN_AdminAddBookDisplay()
{
	char bookname[50], publisher[50], date[20]; int bookNo, count;
	system("cls");
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
	printf("                          * 请输入书名 :                                                          *\n"); // 38
	printf("                          * 请输入编号 :                                                          *\n");
	printf("                          * 请输入出版社 :                                                        *\n");
	printf("                          * 请输入收录数目 :                                                      *\n");
	printf("                          * 生成创建时间 :                                                        *\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
	color(15);
	pos.X = 41;   pos.Y = 4;

	//清空输入缓存区
	int c;  while ((c = getchar()) != '\n' && c != EOF);
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); gets_s(bookname, 50);
	pos.X = 41;   pos.Y = 5;
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); scanf("%d", &bookNo);
	pos.X = 43;   pos.Y = 6;
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); scanf("%s", &publisher);
	pos.X = 45;   pos.Y = 7;
	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); scanf("%d", &count);

	pos.X = 43;   pos.Y = 8;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char str[10];
	strcpy(date, ""); strcat(date, _itoa(timeinfo->tm_year + 1900, str, 10)); strcat(date, ".");
	strcat(date, _itoa(timeinfo->tm_mon + 1, str, 10)); strcat(date, ".");
	strcat(date, _itoa(timeinfo->tm_mday, str, 10));

	if (bookJson == NULL)
	{
		bookJson = File_ReadBooksInfoFromJson();
	}
	File_AddBookInfoToJson(bookJson, bookNo, bookname, publisher, date, count);

	strcat(date, " ");
	strcat(date, _itoa(timeinfo->tm_hour, str, 10)); strcat(date, ":");
	strcat(date, _itoa(timeinfo->tm_min, str, 10)); strcat(date, ":");
	strcat(date, _itoa(timeinfo->tm_sec, str, 10));

	//设置光标坐标
	SetConsoleCursorPosition(hOut, pos); printf(date);

	color(2);
	printf_s("\n\n\n                                            <<<<<<<<<<书籍加载成功！>>>>>>>>>>>>              \n\n");
	system("pause");
	color(3);
}
