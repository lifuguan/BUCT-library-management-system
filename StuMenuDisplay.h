#pragma once

#include "menuInteract.h"
#include "StuJsonOperate.h"


char* stuMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ����������鼮     ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������黹�鼮     ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������鿴������Ϣ ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺��˳� ***************************      *"
};


int stuNumber, classNumber;
char name[50], passwd[50], passwdText[50];



void MAIN_SignUpDisplay()
{
	system("cls");
	printf_s("                          *************************************************************************\n");
	printf_s("                          *                                                                       *\n");
	printf_s("                          * ��ӭע�ᱱ��������ѧͼ�����Ϣ����ϵͳ�����������ϵͳ��ʾע�������˺�*\n");
	printf_s("                          * ��������������:");
	scanf("%s", &name);
	printf_s("                          * ����������ѧ��:");
	scanf("%d", &stuNumber);
	while (2015000000 > stuNumber || stuNumber > 2019999999)
	{
		printf_s("                          * ���ٴ�ȷ������ѧ��:");
		scanf("%d", &stuNumber);;
	}
	printf_s("                          * ���������İ༶:");
	scanf("%d", &classNumber);
	printf_s("                          * ��������������:");
	scanf("%s", &passwd);
	printf_s("                          * ���ٴ�ȷ����������:");
	scanf("%s", &passwdText);
	while (strcmp(passwd, passwdText) != 0)
	{
		printf_s("                          * ���ٴ�ȷ����������:");
		scanf("%s", &passwdText);
	}
	//Json����
	stuJson = File_AddStuInfoToJson(File_ReadStuInfoToJson(), name, passwd, classNumber, stuNumber);
	//printf("                          ");
	color(2);
	printf_s("                                           <<<<<<<<<<<<<<<<ע��ɹ���>>>>>>>>>>>>>>>>>>            \n\n");
	color(3);
	printf_s("                          *************************************************************************\n\n");
	printf_s("-----------------------------------------------------------------------------------------------------------------------\n");
	system("pause");
}

int MAIN_SignInDisplay()
{
	system("cls");
	printf("                          \n");
	printf_s("                          *************************************************************************\n");
	printf_s("                          *                                                                       *\n");
	printf_s("                          * ��ӭ��½����������ѧͼ�����Ϣ����ϵͳ\n");
	printf_s("                          * ��������������:");
	scanf("%s", &name);
	for (int i = 0; i <= 2; i++)
	{
		printf_s("                          * ����'%d'�λ��ᣬ��������ȷ������*\n", 3 - i);
		printf_s("                          * ��������������:");
		scanf("%s", &passwd);
		//��δ��¼���״ζ�ȡ
		if (stuJson == NULL)
		{
			stuJson = File_ReadStuInfoToJson();
		}
		bool res = FILE_StuPasswdCompare(stuJson, name, passwd);

		if (res == true)
		{
			system("cls");
			//����ɫ
			color(2);
			printf_s("\n                                           <<<<<<<<<<<������ȷ,��½�ɹ�!>>>>>>>>>>>>>              \n\n");
			color(3);
			printf_s("                          *************************************************************************\n");
			printf_s("                          *                                                                       *\n");
			printf("\n\n\n\n");
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
				MAIN_MenuDisplay(hOut, stuMenu, NR(stuMenu), index, 5);
				ret = MAIN_GetUserInput(&index, NR(stuMenu));
				if (ret == ESC)
					break;
				if (ret == ENTER)
				{
					switch (index)
					{
					case 0:     return 1;  	//����µ��鼮
					case 1:     return 2;  	//ɾ�����е��鼮
					case 2:     return 3;
					case 3:		return 0;	//�˳�
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

