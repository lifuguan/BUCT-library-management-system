/*
@author : Li Hao, Shen Penghui
*/
#define _CRT_SECURE_NO_WARNINGS

#include "MainMenuDisplay.h"
#include "StuMenuDisplay.h"
#include "adminMenuDisplay.h"
#include "BookJsonOperate.h"


void RabitDisplay();

void OrgDisplay();

DWORD WINAPI ThreadReadJson(void* data);

int main(int argc, char* argv[])
{
	HANDLE thread = CreateThread(NULL, 0, ThreadReadJson, NULL, 0, NULL);
	stuJson = File_ReadStuInfoToJson();
	bookJson = File_ReadBooksInfoFromJson();

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
		printf_s("-----------------------------------------------------------------------------------------------------------------------\n");
		Sleep(100);

		printf_s("                          *********************欢迎使用北京化工大学图书管理系统********************\n");
		printf_s("                          *                                                                       *\n");
		//此处目的：为菜单栏留出空间
		printf_s("\n\n\n\n");
		printf_s("                          *                                                                       *\n");
		printf_s("                          *************************************************************************\n");

		actionSelect = MAIN_MainDisplay(posY);
		//学生注册
		if (actionSelect == _SIGN_UP)
		{
			MAIN_StuSignUpDisplay();
		}
		//学生登录
		else if (actionSelect == _SIGN_IN)
		{
			bool status = false; status = STU_SignInDisplay();
			if (status)
			{
				system("cls");
				color(2);
				printf_s("\n                                           <<<<<<<<<<<密码正确,登陆成功!>>>>>>>>>>>>>              \n\n");
				color(3);
			}
			while (status)
			{
				int choice = STU_MainMenuDisplay();
			
				if (choice == 1)
				{
					FILE_QueryAllBookInfo();
					int res = STU_QueryAllBookDisplay();
					STU_BookSelectedEvent(res);
					system("cls");
					color(2);
					printf_s("\n                                           <<<<<<<<<<<借阅成功，继续操作!>>>>>>>>>>>>>              \n\n");
					color(3);

				}
				else if (choice == 2)
				{

				}
				else if (choice == 3)
				{

				}
				else { break; }
			}
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
	printf_s("-----------------------------------------------------------------------------------------------------------------------\n");
	color(4);
	printf_s("-----------------------------------------------------------------------------------------------------------------------\n");
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
	printf_s("\n-----------------------------------------------------------------------------------------------------------------------\n");
	Sleep(100);
}


DWORD WINAPI ThreadReadJson(void* data)
{
	stuJson = File_ReadStuInfoToJson();
	bookJson = File_ReadBooksInfoFromJson();
	return 0;
}