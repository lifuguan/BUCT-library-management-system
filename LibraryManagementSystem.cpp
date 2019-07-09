/*
@author : Li Hao, Shen Penghui
*/
#define _CRT_SECURE_NO_WARNINGS
#include "StuJsonOperate.h"
#include "BookJsonOperate.h"
#include "MainMenuDisplay.h"
#include<stdio.h>
#include<string.h>
#include <Windows.h>



void RabitDisplay();

void OrgDisplay();



int main(int argc, char* argv[])
{
	SetConsoleTitleA(TITLE);
	OrgDisplay();
	color(3);
	

	int actionSelect, i = 0, posY = 22;
	while (true)
	{
		i+=1;
		if (i!= 1)
		{
			color(3);
			system("cls");
			RabitDisplay();
			posY += 2;
		}
		printf_s("------------------------------------------------------------------------------------------------------------------------\n");
		Sleep(100);

		printf_s("                          *********************欢迎使用北京化工大学图书管理系统********************\n");
		printf_s("                          *                                                                       *\n");
		//此处目的：为菜单栏留出空间
		printf_s("\n\n\n\n");
		printf_s("                          *                                                                       *\n");
		printf_s("                          *************************************************************************\n");

		actionSelect = MAIN_MainDisplay(posY);
		//注册
		if (actionSelect == _SIGN_UP)
		{
			MAIN_SignUpDisplay();
		}
		//登录
		else if (actionSelect == _SIGN_IN)
		{
			int choice = MAIN_SignInDisplay();

		}
		//管理员登录
		else if (actionSelect == _ADMIN)
		{
			int choice = MAIN_AdminSignInDisplay();
			if (choice == 1)
			{
				MAIN_AdminAddBookDisplay();
			}
			else if (choice == 2)
			{

			}
			
		}

		else if (actionSelect == _QUIT) { return 0; }
		else
		{
			printf_s("                          * 注册请输入'1'，登陆请输入'2'，管理员请输入'3'\n");
			printf_s("                          * 请再次输入:");
			scanf("%d", &actionSelect);
		}
	}

	return 0;
}


void RabitDisplay()
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

void OrgDisplay()
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
}