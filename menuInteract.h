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


//����ṹ��
CONSOLE_CURSOR_INFO cci;
//����Ĭ�ϵ�����λ��  	
COORD pos = { 0,0 };

char* selectedMenu[] = { (char*)"*      ��                                                               *", (char*)"*      ��                                                               *" };

//����ö��Keyboard�ļ�ֵ���� 
enum
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};


void color(short x)	//�Զ��庯���ݲ����ı���ɫ 
{
	if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//ֻ��һ���������ı�������ɫ 
	}
	else//Ĭ�ϵ���ɫ��ɫ
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}




void MAIN_MenuDisplay(HANDLE hOut, char** menu, int size, int index, int posY, int posX)
{
	int i;
	for (i = 0; i < size; i++)
	{
		//���i==index��ʾ�ڵ�ǰѡ���λ�ã�Ĭ�ϳ�ʼ����ʾ�ǵ�һ���ʾΪ��ɫ��
		//���������°���ѡ���ʱ�򣬹����ƶ���Ҳ�Ϳ������б�ѡ������� 
		if (i == index)
		{
			//��ɫ 
			SetConsoleTextAttribute(hOut, 4 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			pos.X = posX;
			pos.Y = posY + i;
			//���ù������
			SetConsoleCursorPosition(hOut, pos);
			printf("%s", menu[i]);
		}
		//������ʾΪ��ɫ 
		else
		{

			SetConsoleTextAttribute(hOut, 3);
			pos.X = posX;
			pos.Y = posY + i;
			//���ù������
			SetConsoleCursorPosition(hOut, pos);    //���ù������
			printf("%s", menu[i]);
		}
	}
	//ˢ�±�׼��������� 
	fflush(stdout);
}

//��ȡ�û�����Ľӿ� 
int  MAIN_GetUserInput(int* index, int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//�� 
		//���ѡ���ϣ���ô��������ƶ� 
	case UP: if (*index > 0)* index -= 1;  break;
		//�� 
		//���ѡ���£���ô��������ƶ� 
	case DOWN:if (*index < size - 1)* index += 1;  break;
		//�� 
	case LEFT:
	case 97:return 0;
		//�� 
	case RIGHT:return 0;
		//�س� 
	case ENTER: return ENTER;
		//ESC
	case ESC: return ESC;
	}
	return 0;
}