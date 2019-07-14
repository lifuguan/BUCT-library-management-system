#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <time.h>
#include "cJSON.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))


//定义结构体
CONSOLE_CURSOR_INFO cci;
//定义默认的坐标位置  	
COORD pos = { 0,0 };

char* selectedMenu[] = { (char*)"*      是                                                               *", (char*)"*      否                                                               *" };

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




void MAIN_MenuDisplay(HANDLE hOut, char** menu, int size, int index, int posY, int posX)
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
			pos.X = posX;
			pos.Y = posY + i;
			//设置光标坐标
			SetConsoleCursorPosition(hOut, pos);
			printf("%s", menu[i]);
		}
		//否则显示为白色 
		else
		{

			SetConsoleTextAttribute(hOut, 3);
			pos.X = posX;
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