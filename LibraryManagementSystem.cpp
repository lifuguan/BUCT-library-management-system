/*
@author : Li Hao, Shen Penghui
*/
#define _CRT_SECURE_NO_WARNINGS
#include "StuJsonOperate.h"
#include<stdio.h>
#include<string.h>



int main(int argc, char* argv[])
{
	int actionSelect;
	int stuNumber, classNumber;
	char name[10], passwd[10], passwdText[10];
	printf_s("----------------------------------------------------------------------\n");
	printf_s("-----------------欢迎使用北京化工大学图书管理系统------------------------\n");
	printf_s("-----请选择您将要进行的操作：注册请输入'1'，登陆请输入'2'\n");
	printf_s("-----请在此输入:");
	scanf("%d", &actionSelect);
	while (actionSelect != 1 && actionSelect != 2)
	{
		printf_s("-----注册请输入'1'，登陆请输入'2'\n");
		printf_s("-----请再次输入:");
		scanf("%d", &actionSelect);
	}

	printf_s("----------------------------------------------------------------------\n");

	if (actionSelect == 1)
	{
		printf_s("欢迎注册北京化工大学图书馆信息管理系统，下面请跟随系统提示注册您的账号\n");
		printf_s("请输入您的姓名:");
		scanf("%s", &name);
		printf_s("请输入您的学号:");
		scanf("%d", &stuNumber);
		while (2017000000 > stuNumber || stuNumber > 2019999999)
		{
			printf_s("请再次确认您的学号:");
			scanf("%d", &stuNumber);;
		}
		printf_s("请输入您的班级:");
		scanf("%d", &classNumber);
		printf_s("请设置您的密码:");
		scanf("%s", &passwd);
		printf_s("请再次确认您的密码:");
		scanf("%s", &passwdText);
		while (strcmp(passwd, passwdText) != 0)
		{
			printf_s("请再次确认您的密码:");
			scanf("%s", &passwdText);
		}
		File_AddStuInfoToJson(File_ReadStueInfoToJson(), name, passwd, classNumber,stuNumber);
		printf_s("\033[47;31m<<<<<<<<<<<<<<<<注册成功！>>>>>>>>>>>>>>>>>>\n\033[0m");
		actionSelect = 2;
	}
	printf_s("----------------------------------------------------------------------\n");

	if (actionSelect == 2)
	{
		printf_s("欢迎登陆北京化工大学图书馆信息管理系统\n");
		printf_s("请输入您的学号:");
		scanf("%d", &stuNumber);
		while (2017000000 > stuNumber || stuNumber > 2019999999)
		{
			printf_s("请再次确认您的学号:");
			scanf("%d", &stuNumber);;
		}
		printf_s("请输入您的密码:");
		scanf("%s", &passwd);

		int k = 0;
		/*此处需要密码判断函数*/
		if (k == 0)
			printf_s("<<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>");
		else
		{

			while (k == 1)
			{
				printf_s("密码错误,请重新输入");
				scanf("%s", &passwd);;
			}
		}
	}


	return 0;
}



