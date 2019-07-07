/*
@author : Li Hao, Shen Penghui
*/
#define _CRT_SECURE_NO_WARNINGS
#define _SIGN_UP 1
#define wow 2018040215
#define _SIGN_IN 2
#define _ADMIN 3
#define _ADMIN_ACCOUNT "root"
#define _ADMIN_PASSWD "root"
#include "StuJsonOperate.h"
#include "BookJsonOperate.h"
#include<stdio.h>
#include<string.h>
#include <Windows.h>
#include <windows.h>
void color(short x)	//自定义函根据参数改变颜色 
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
int rabit()
{
	color(15);
	printf("	                          	             ▃ 				\n");
	printf("	                          	　　　 　▋ 　　 ▋　◢▀　▀◣ 				\n");
	printf("	                          	　　　　▌　 　 　▌　▌ 　 .▌ 				\n");
	printf("	                          	　　 　 ▌　　　　▌ ▌　　　▌ 				\n");
	printf("	                          	　 　　▐ 　 　　 ▌ ▌ 　 　▌ 				\n");
	printf("	                          	　 　　 ▐ 　 　 ▀■▀ 　 　▌ 				\n");
	printf("	                          	　　　◢◤　　　　　　　　　▀▃ 				\n");
	printf("	                          	　　◢◤　　　　　　　　　 　　◥◣ 				\n");
	printf("	                          	　　▌　　　　　　　　　　 　　　▌ 				\n");
	printf("	                          	　▐　 　●　　 　　　　●　　　　▌			\n");
	printf("	                          	　　▌　　　　　　　　　　　　　 ▌				\n");
	printf("	                          	　　◥◣ 　 　　 ╳ 　　　　　　◢◤ 				\n");
	printf("	                          	　　 ◢▀▅▃▂　　　▂▂▃▅▀▅ 				\n");
	printf("	                          	　◢◤　　　　▂▂▂　　　　◥◣ 				\n");
	printf("	                          	▐◣▃▌　　　　　　　　　　　▐▃◢▌ 				\n");
	printf("	                          	◥◣▃▌　　　　 　　 　　　　▐▃◢◤ 				\n");
	printf("	                          	　 ▀▅▃　　　　　 　 　　▂▅▀ 				\n");
	printf("	                          	　　 　 ▀■▆▅▅▅▅▅▆■█▀ 				\n");
	printf("	                          	　　　 　▐▃▃▃▲▃▃▃◢ 				\n\n\n");
	color(3);
	return 0;
}



//全局保存json学生对象,图书对象
cJSON* stuJson, * bookJson;

int main(int argc, char* argv[])
{
	color(3);
	printf_s("------------------------------------------------------------------------------------------------------------------------");
	color(4);
	printf_s("\n------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n*                **********             **          **              *********           ************                  *\n");
	Sleep(100);
	printf("*                **********             **          **             **********           ************                  *\n");
	Sleep(100);
	printf("*                **       **            **          **            **                         **                       *\n");
	Sleep(100);
	printf("*                **        **           **          **            **                         **                       *\n");
	Sleep(100);
	printf("*                **        **           **          **           **                          **                       *\n");
	Sleep(100);
	printf("*                **       **            **          **           **                          **                       *\n");
	Sleep(100);
	printf("*                **********             **          **           **                          **                       *\n");
	Sleep(100);
	printf("*                **********             **          **           **                          **                       *\n");
	Sleep(100);
	printf("*                **       **            **          **           **                          **                       *\n");
	Sleep(100);
	printf("*                **        **           **          **           **                          **                       *\n");
	Sleep(100);
	printf("*                **        **           **          **            **                         **                       *\n");
	Sleep(100);
	printf("*                **       **             **        **             **                         **                       *\n");
	Sleep(100);
	printf("*                **********               **********               **********                **                       *\n");
	Sleep(100);
	printf("*                **********                ********                 *********                **                       *\n");
	Sleep(100);
	printf_s("\n------------------------------------------------------------------------------------------------------------------------\n");
	Sleep(100);
	color(3);

	printf_s("------------------------------------------------------------------------------------------------------------------------\n");
	Sleep(100);

	printf_s("                          *********************欢迎使用北京化工大学图书管理系统********************\n");
	printf_s("                          *                                                                       *\n");
	int actionSelect;
	int stuNumber, classNumber;
	char name[50], passwd[50], passwdText[50];
	while (true)
	{

		printf_s("                          * 请选择您将要进行的操作：注册请输入'1',*********************************\n");
		Sleep(150);
		printf_s("                          *                                                                       *\n");
		Sleep(150);
		printf_s("                          * 请选择您将要进行的操作：              登陆请输入'2'，************     *\n");
		Sleep(150);
		printf_s("                          *                                                                       *\n");
		Sleep(150);
		printf_s("                          * 请选择您将要进行的操作：                             管理员请输入'3'  *\n");
		Sleep(150);
		printf_s("                          *                                                                       *\n");
		Sleep(150);
		printf_s("                          *************************************************************************\n");
		Sleep(150);
		printf_s("                          *                                                                       *\n");
		printf_s("                            请-在-此-输-入 :");
		scanf("%d", &actionSelect);
		printf_s("                          *                                                                       *\n");
		printf_s("                          *************************************************************************\n");

		//printf_s("----------------------------------------------------------------------\n");

		//注册
		if (actionSelect == _SIGN_UP)
		{
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
			printf_s("------------------------------------------------------------------------------------------------------------------------\n");
			printf("                          \n");
		}
		//登录
		else if (actionSelect == _SIGN_IN)
		{
			printf("                          \n");
			printf_s("------------------------------------------------------------------------------------------------------------------------\n");
			printf("                          \n");
			printf_s("                          *************************************************************************\n");
			printf_s("                          *                                                                       *\n");
			printf_s("                          * 欢迎登陆北京化工大学图书馆信息管理系统\n");
			printf_s("                          * 请输入您的姓名:");
			scanf("%s", &name);

			while (true)
			{
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
					color(2);
					printf_s("                                           <<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>>              \n\n");
					color(3);
					printf_s("                          *************************************************************************\n");
					printf("                          \n");
					printf_s("------------------------------------------------------------------------------------------------------------------------\n");
					printf("                          \n");
					break;
				}
				else
				{

					color(4);
					printf_s("                                           <<<<<<<<<<密码错误,请重新输入!>>>>>>>>>>>>              \n\n");
					color(3);
				}
			}

		}
		else if (actionSelect == _ADMIN)
		{
			int i;
			for (i = 0; i <= 2; i++)
			{
				printf_s("                          * 您有'%d'次机会，请输入正确的密码*\n", 3 - i);
				printf_s("                          * 请输入您的密码:");
				int secret;
				int kk = 123345;
				scanf("%d", &secret);
				if (secret == kk)
				{
					//变绿色
					color(2);
					printf_s("                                           <<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>>              \n\n");
					color(3);
					break;
				}
				else
				{
					color(4);
					printf_s("                                           <<<<<<<<<<密码错误,请重新输入!>>>>>>>>>>>>              \n\n");
					color(3);
				}
			}
			printf_s("                          *************************************************************************\n");
			printf_s("                          *                                                                       *\n");

			if (bookJson == NULL)
			{
				bookJson = File_ReadBooksInfoFromJson();
			}
			char bookName[50] = "bookName";
			FILE_ModifyBookInfoToJson(bookJson, bookName, 1);
		}
		else if (actionSelect == wow)
		{
			color(15);
			printf("	                          	             ▃ 				\n");
			printf("	                          	　　　 　▋ 　　 ▋　◢▀　▀◣ 				\n");
			printf("	                          	　　　　▌　 　 　▌　▌ 　 .▌ 				\n");
			printf("	                          	　　 　 ▌　　　　▌ ▌　　　▌ 				\n");
			printf("	                          	　 　　▐ 　 　　 ▌ ▌ 　 　▌ 				\n");
			printf("	                          	　 　　 ▐ 　 　 ▀■▀ 　 　▌ 				\n");
			printf("	                          	　　　◢◤　　　　　　　　　▀▃ 				\n");
			printf("	                          	　　◢◤　　　　　　　　　 　　◥◣ 				\n");
			printf("	                          	　　▌　　　　　　　　　　 　　　▌ 				\n");
			printf("	                          	　▐　 　●　　 　　　　●　　　　▌			\n");
			printf("	                          	　　▌　　　　　　　　　　　　　 ▌				\n");
			printf("	                          	　　◥◣ 　 　　 ╳ 　　　　　　◢◤ 				\n");
			printf("	                          	　　 ◢▀▅▃▂　　　▂▂▃▅▀▅ 				\n");
			printf("	                          	　◢◤　　　　▂▂▂　　　　◥◣ 				\n");
			printf("	                          	▐◣▃▌　　　　　　　　　　　▐▃◢▌ 				\n");
			printf("	                          	◥◣▃▌　　　　 　　 　　　　▐▃◢◤ 				\n");
			printf("	                          	　 ▀▅▃　　　　　 　 　　▂▅▀ 				\n");
			printf("	                          	　　 　 ▀■▆▅▅▅▅▅▆■█▀ 				\n");
			printf("	                          	　　　 　▐▃▃▃▲▃▃▃◢ 				\n\n\n");
			color(3);

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




