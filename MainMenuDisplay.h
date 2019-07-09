#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
#define  TITLE  "学生信息管理系统"
#define _QUIT 0
#define _SIGN_UP 1
#define _SIGN_IN 2
#define _ADMIN 3
#define _ADMIN_ACCOUNT "root"
#define _ADMIN_PASSWD "root"

//定义枚举Keyboard的键值数据 
enum
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};

int stuNumber, classNumber;
char name[50], passwd[50], passwdText[50];


//全局保存json学生对象,图书对象
cJSON* stuJson, * bookJson;

//显示主菜单
char* mainMenu[] =
{
	(char*)"* 请选择您将要进行的操作：学生账号注册 ***************************      *",
	(char*)"* 请选择您将要进行的操作：学生账号登录 ***************************      *",
	(char*)"* 请选择您将要进行的操作：管理员账号登录 *************************      *",
	(char*)"* 请选择您将要进行的操作：退出程序  ******************************      *"
};

char* adminMenu[] =
{
	(char*)"* 请选择您将要进行的操作：添加新的书籍 ***************************      *",
	(char*)"* 请选择您将要进行的操作：删除已有书籍 ***************************      *",
	(char*)"* 请选择您将要进行的操作：管理员账号退出  *************************     *"
};

//定义结构体
CONSOLE_CURSOR_INFO cci;
//定义默认的坐标位置  	
COORD pos = { 0,0 };
//显示菜单 
void MAIN_MenuDisplay(HANDLE hOut, char** menu, int size, int index, int posY);
//获取用户输入 
int  MAIN_GetUserInput(int* index, int size);

void color(short x)	//自定义函根据参数改变颜色 
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	}
	else//默认的颜色白色
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}



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
	printf_s("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                          \n");
}

void MAIN_SignInDisplay()
{
	system("cls");
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
					case 0:     return 1;  	//学生账号注册
					case 1:     return 2;  	//学生账号登录
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



void MAIN_MenuDisplay(HANDLE hOut, char** menu, int size, int index, int posY)
{
	int i;
	for (i = 0; i < size; i++)
	{
		//如果i==index表示在当前选项的位置，默认初始化显示是第一项，显示为红色，
		//当按下上下按键选择的时候，光标会移动，也就看到了列表选择的现象 
		if (i == index)
		{
			//反色 
			SetConsoleTextAttribute(hOut, 4 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			pos.X = 26;
			pos.Y = posY + i;
			//设置光标坐标
			SetConsoleCursorPosition(hOut, pos);
			printf("%s", menu[i]);
		}
		//否则显示为白色 
		else
		{

			SetConsoleTextAttribute(hOut, 3);
			pos.X = 26;
			pos.Y = posY + i;
			//设置光标坐标
			SetConsoleCursorPosition(hOut, pos);    //设置光标坐标
			printf("%s", menu[i]);
		}
	}
	//刷新标准输出缓冲区 
	fflush(stdout);
}

//获取用户输入的接口 
int  MAIN_GetUserInput(int* index, int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//上 
		//如果选择上，那么光标向上移动 
	case UP: if (*index > 0)* index -= 1;  break;
		//下 
		//如果选择下，那么光标向下移动 
	case DOWN:if (*index < size - 1)* index += 1;  break;
		//左 
	case LEFT:
	case 97:return 0;
		//右 
	case RIGHT:return 0;
		//回车 
	case ENTER: return ENTER;
		//ESC
	case ESC: return ESC;
	}
	return 0;
}