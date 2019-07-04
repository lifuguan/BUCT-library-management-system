/*
@author : Li Hao, Shen Penghui
*/
#define _CRT_SECURE_NO_WARNINGS
#define _SIGN_UP 1
#define _SIGN_IN 2
#define _ADMIN 3
#define _ADMIN_ACCOUNT "root"
#define _ADMIN_PASSWD "root"
#include "StuJsonOperate.h"
#include<stdio.h>
#include<string.h>
//#include <Windows.h>
//全局保存json学生对象
cJSON * stuJson;

int main(int argc, char* argv[])
{
	printf("\n\n\n\033[31m*                **********             **          **              *********           ************                  *\n");
	//Sleep(100);
	printf("*                **********             **          **             **********           ************                  *\n");
	//Sleep(100);
	printf("*                **       **            **          **            **                         **                       *\n");
	//Sleep(100);
	printf("*                **        **           **          **            **                         **                       *\n");
	//Sleep(100);
	printf("*                **        **           **          **           **                          **                       *\n");
	//Sleep(100);
	printf("*                **       **            **          **           **                          **                       *\n");
	//Sleep(100);
	printf("*                **********             **          **           **                          **                       *\n");
	//Sleep(100);
	printf("*                **********             **          **           **                          **                       *\n");
	//Sleep(100);
	printf("*                **       **            **          **           **                          **                       *\n");
	//Sleep(100);
	printf("*                **        **           **          **           **                          **                       *\n");
	//Sleep(100);
	printf("*                **        **           **          **            **                         **                       *\n");
	//Sleep(100);
	printf("*                **       **             **        **             **                         **                       *\n");
	//Sleep(100);
	printf("*                **********               **********               **********                **                       *\n");
	//Sleep(100);
	printf("*                **********                ********                 *********                **                       *\n\033[0m\n");
	//Sleep(100);
	printf_s("\n------------------------------------------------------------------------------------------------------------------------\n");
	//Sleep(100);
	printf_s("------------------------------------------------------------------------------------------------------------------------\n");
	//Sleep(100);
	printf_s("                          *********************欢迎使用北京化工大学图书管理系统********************\n");
	int actionSelect;
	int stuNumber, classNumber;
	char name[10], passwd[10], passwdText[10];
	while (true)
	{
		printf_s("                          * 请选择您将要进行的操作：注册请输入'1'，登陆请输入'2'，管理员请输入'3'\n");
		printf_s("                          * 请在此输入:");
		scanf("%d", &actionSelect);

		//printf_s("----------------------------------------------------------------------\n");

		//注册
		if (actionSelect == _SIGN_UP)
		{
			printf_s("                          * 欢迎注册北京化工大学图书馆信息管理系统，下面请跟随系统提示注册您的账号\n");
			printf_s("                          * 请输入您的姓名:");
			scanf("%s", &name);
			printf_s("                          * 请输入您的学号:");
			scanf("%d", &stuNumber);
			while (2017000000 > stuNumber || stuNumber > 2019999999)
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
			stuJson = File_AddStuInfoToJson(File_ReadStueInfoToJson(), name, passwd, classNumber, stuNumber);
			printf("                          ");
			printf_s("\033[32;32m<<<<<<<<<<<<<<<<注册成功！>>>>>>>>>>>>>>>>>>\n\033[0m");
			printf("                          \n");
			printf_s("------------------------------------------------------------------------------------------------------------------------\n");
			printf("                          \n");
		}
		//登录
		else if (actionSelect == _SIGN_IN)
		{
			printf("                          \n");
			printf_s("------------------------------------------------------------------------------------------------------------------------\n");
			printf("                          \n");
			printf_s("                          * 欢迎登陆北京化工大学图书馆信息管理系统\n");
			printf_s("                          * 请输入您的姓名:");
			scanf("%s", &name);
			
			while (true)
			{
				printf_s("                          * 请输入您的密码:");
				scanf("%s", &passwd);
				stuJson = File_ReadStueInfoToJson();
				bool res = FILE_StuPasswdCompare(stuJson, name, passwd);

				if (res == true)
				{
					printf("                          ");
					printf_s("\033[32;32m* <<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>\n\033[0m");
					printf("                          \n");
					printf_s("------------------------------------------------------------------------------------------------------------------------\n");
					printf("                          \n");
					break;
				}
				else
				{
					printf("                          ");
					printf_s("\033[32;31m* <<<<<<<<<<<密码错误,请重新输入>>>>>>>>>>>>\n\033[0m");
				}
			}

		}
		else if (actionSelect == _ADMIN)
		{
			char admin_account[10], admin_passwd[10];
			scanf("%s", &admin_account);
			scanf("%s", &admin_passwd);
			if (strcmp(admin_account, _ADMIN_ACCOUNT) != 0)
			{
				//printf("")
			}
		}
		else
		{
			printf_s("                          * 注册请输入'1'，登陆请输入'2'，管理员请输入'3'\n");
			printf_s("                          * 请再次输入:");
			scanf("%d", &actionSelect);
		}
	}

	return 0;
}



