#pragma once

#include "menuInteract.h"
#include "StuJsonOperate.h"
#include "BookJsonOperate.h"

char* stuMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ����������鼮     ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������黹�鼮     ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������鿴������Ϣ ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺��˳� ***************************      *"
};


int stuNumber, classNumber;
char name[50], passwd[50], passwdText[50];



void MAIN_StuSignUpDisplay()
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

bool STU_SignInDisplay()
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
			return true;
		}
		else
		{
			color(4);
			printf_s("                                           <<<<<<<<<<�������,����������!>>>>>>>>>>>>              \n\n");
			color(3);
		}
	}
	return false;
}

int STU_MainMenuDisplay()
{
	//����ɫ
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("\n\n\n\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
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
		MAIN_MenuDisplay(hOut, stuMenu, NR(stuMenu), index, 5, 26);
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

int STU_QueryAllBookDisplay()
{
	system("cls");
	printf("                          *************************************************************************\n");
	printf("      ����                   ������                     �鼮���                ʣ������           ʱ��\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
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
		MAIN_MenuDisplay(hOut, stuQueryMenu, bookCnt, index, 4, 5);
		ret = MAIN_GetUserInput(&index, bookCnt);
		if (ret == ESC)
			return 0;
		if (ret == ENTER)
		{
			return index + 1;
		}
	}
}

void STU_BookSelectedEvent(int selected)
{
	system("cls");
	printf("\n\n                                                    �Ƿ�ѡ����Ĵ���\n");
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("\n\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
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
		MAIN_MenuDisplay(hOut, selectedMenu, 2, index, 5, 26);
		ret = MAIN_GetUserInput(&index, 2);
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			if (index == 0)
			{
				FILE_ModifyBookInfoToJson(bookJson, bookName[selected - 1], -1);
				break;
			}
			else
			{
				break;
			}
		}
	}
}



int STU_ReturnBookDisplay(int bookCnt)
{
	system("cls");
	printf("           ************************************ѡ��Ҫ�黹���鼮*************************************\n");
	printf("      ����                   ������                     �鼮���                ʣ������           ʱ��\n");
	printf("---------------------------------------------------------------------------------------------------------------\n");
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
	while (true)
	{
		MAIN_MenuDisplay(hOut, stuReturnMenu, bookCnt, index, 4, 5);
		ret = MAIN_GetUserInput(&index, bookCnt);
		if (ret == ESC)
			return 0;
		if (ret == ENTER)
		{
			return index + 1;
		}
	}
}

void STU_BookReturnEvent(int selected, char name[50])
{
	system("cls");
	printf("\n\n                                                    �Ƿ�ѡ��黹����\n");
	printf("                          *************************************************************************\n");
	printf("                          *                                                                       *\n");
	printf("\n\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
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
		MAIN_MenuDisplay(hOut, selectedMenu, 2, index, 5, 26);
		ret = MAIN_GetUserInput(&index, 2);
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			if (index == 0)
			{
				stuReturnMenu[selected - 1] = NULL;
				
				break;
			}
			else
			{
				break;
			}
		}
	}
}


void MAIN_StuPersonalInfoDisplay(cJSON* stuJson, char name[50])
{
	system("cls");
	cJSON* stu = cJSON_GetObjectItem(stuJson, name);
	
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
	printf("                          * ѧ������   :                                                          *\n"); // 38
	printf("                          * ѧ��ѧ��   :                                                          *\n");
	printf("                          * ѧ���༶   :                                                          *\n");
	printf("                          * �ѽ���Ŀ   :                                                          *\n");
	printf("                          *                                                                       *\n");
	printf("                          *************************************************************************\n");
	color(15);
	pos.X = 41;   pos.Y = 4;

	//������뻺����
	int c;  while ((c = getchar()) != '\n' && c != EOF);
	//���ù������
	SetConsoleCursorPosition(hOut, pos); printf("%s", name);
	pos.X = 41;   pos.Y = 5;
	//���ù������
	SetConsoleCursorPosition(hOut, pos); printf("%d", stu->child->valueint);
	pos.X = 41;   pos.Y = 6;
	//���ù������
	SetConsoleCursorPosition(hOut, pos); printf("%d", stu->child->next->valueint);
	pos.X = 41;   pos.Y = 7;
	//���ù������
	SetConsoleCursorPosition(hOut, pos); printf("%d\n\n\n", stu->child->next->next->next->valueint);
	pos.X = 41;   pos.Y = 10;
	color(2);
	system("pause");
	color(3);
}
