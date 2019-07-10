#pragma once

#include "menuInteract.h"
#include "BookJsonOperate.h"


#define _ADMIN_ACCOUNT "root"
#define _ADMIN_PASSWD "root"

char* adminMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ���������µ��鼮 ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ɾ�������鼮 ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ���������Ա�˺��˳�  *************************     *"
};



int MAIN_AdminSignInDisplay()
{
	system("cls");
	int i;

	for (i = 0; i <= 2; i++)
	{
		printf_s("                          * ����'%d'�λ��ᣬ��������ȷ������*\n", 3 - i);
		printf_s("                          * ��������������:");
		char passwd[10];
		scanf("%s", &passwd);

		if (strcmp(passwd, _ADMIN_PASSWD) == 0)
		{
			system("cls");
			//����ɫ
			color(2);
			printf_s("\n                                           <<<<<<<<<<<������ȷ,��½�ɹ�!>>>>>>>>>>>>>              \n\n");
			color(3);
			printf_s("                          *************************************************************************\n");
			printf_s("                          *                                                                       *\n");
			printf("\n\n\n");
			printf_s("                          *                                                                       *\n");
			printf_s("                          *************************************************************************\n");


			int ret;
			int index = 0;
			HANDLE hOut;
			//��ȡ��ǰ�ľ��---����Ϊ��׼������ 
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			//��ȡ�����Ϣ
			GetConsoleCursorInfo(hOut, &cci);
			//���ù���С   
			cci.dwSize = 1;
			//���ù�겻�ɼ� FALSE   
			cci.bVisible = 0;
			//����(Ӧ��)�����Ϣ
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
					case 0:     return 1;  	//����µ��鼮
					case 1:     return 2;  	//ɾ�����е��鼮
					case 2:		return 0;	//�˳�
					}
				}
			}
		}
		else
		{
			color(4);
			printf_s("                                           <<<<<<<<<<�������,����������!>>>>>>>>>>>>              \n\n");
			color(3);
		}
	}
}

void MAIN_AdminAddBookDisplay()
{
	char bookname[50], publisher[50], date[20]; int bookNo, count;
	system("cls");
	HANDLE hOut;
	//��ȡ��ǰ�ľ��---����Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	cci.bVisible = 1;
	//����(Ӧ��)�����Ϣ
	SetConsoleCursorInfo(hOut, &cci);
	color(3);
	printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("                          * ���������� :                                                          *\n"); // 38
	printf("                          * �������� :                                                          *\n");
	printf("                          * ����������� :                                                        *\n");
	printf("                          * ��������¼��Ŀ :                                                      *\n");
	printf("                          * ���ɴ���ʱ�� :                                                        *\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
	color(15);
	pos.X = 41;   pos.Y = 4;

	//������뻺����
	int c;  while ((c = getchar()) != '\n' && c != EOF);
	//���ù������
	SetConsoleCursorPosition(hOut, pos); gets_s(bookname, 50);
	pos.X = 41;   pos.Y = 5;
	//���ù������
	SetConsoleCursorPosition(hOut, pos); scanf("%d", &bookNo);
	pos.X = 43;   pos.Y = 6;
	//���ù������
	SetConsoleCursorPosition(hOut, pos); scanf("%s", &publisher);
	pos.X = 45;   pos.Y = 7;
	//���ù������
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

	//���ù������
	SetConsoleCursorPosition(hOut, pos); printf(date);

	color(2);
	printf_s("\n\n\n                                            <<<<<<<<<<�鼮���سɹ���>>>>>>>>>>>>              \n\n");
	system("pause");
	color(3);
}
