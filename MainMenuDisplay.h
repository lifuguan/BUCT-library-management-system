#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <time.h>
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
#define  TITLE  "ѧ����Ϣ����ϵͳ"
#define _QUIT 0
#define _SIGN_UP 1
#define _SIGN_IN 2
#define _ADMIN 3
#define _ADMIN_ACCOUNT "root"
#define _ADMIN_PASSWD "root"

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

int stuNumber, classNumber;
char name[50], passwd[50], passwdText[50];


//ȫ�ֱ���jsonѧ������,ͼ�����
cJSON* stuJson, * bookJson;

//��ʾ���˵�
char* mainMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺�ע�� ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺ŵ�¼ ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ���������Ա�˺ŵ�¼ *************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������˳�����  ******************************      *"
};

char* adminMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ���������µ��鼮 ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ɾ�������鼮 ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ���������Ա�˺��˳�  *************************     *"
};

char* stuMenu[] =
{
	(char*)"* ��ѡ������Ҫ���еĲ����������鼮     ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������黹�鼮     ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ������鿴������Ϣ ***************************      *",
	(char*)"* ��ѡ������Ҫ���еĲ�����ѧ���˺��˳� ***************************      *"
};

//����ṹ��
CONSOLE_CURSOR_INFO cci;
//����Ĭ�ϵ�����λ��  	
COORD pos = { 0,0 };
//��ʾ�˵� 
void MAIN_MenuDisplay(HANDLE hOut, char** menu, int size, int index, int posY);
//��ȡ�û����� 
int  MAIN_GetUserInput(int* index, int size);

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



int MAIN_MainDisplay(int posY)
{
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
		MAIN_MenuDisplay(hOut, mainMenu, NR(mainMenu), index, posY);
		ret = MAIN_GetUserInput(&index, NR(mainMenu));
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			switch (index)
			{
			case 0:     return 1;  	//ѧ���˺�ע��
			case 1:     return 2;  	//ѧ���˺ŵ�¼
			case 2:     return 3;  	//����Ա�˺ŵ�¼
			case 3:     return 0;		//�˳�
			}
		}
	}

}

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
	printf_s("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                          \n");
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
	printf("------------------------------------------------------------------------------------------------------------------------\n\n");
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



void MAIN_MenuDisplay(HANDLE hOut, char** menu, int size, int index, int posY)
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
			pos.X = 26;
			pos.Y = posY + i;
			//���ù������
			SetConsoleCursorPosition(hOut, pos);
			printf("%s", menu[i]);
		}
		//������ʾΪ��ɫ 
		else
		{

			SetConsoleTextAttribute(hOut, 3);
			pos.X = 26;
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