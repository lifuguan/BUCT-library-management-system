#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
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

void MAIN_SignInDisplay()
{
	system("cls");
	printf("                          \n");
	printf_s("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                          \n");
	printf_s("                          *************************************************************************\n");
	printf_s("                          *                                                                       *\n");
	printf_s("                          * ��ӭ��½����������ѧͼ�����Ϣ����ϵͳ\n");
	printf_s("                          * ��������������:");
	scanf("%s", &name);

	while (true)
	{
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
			color(2);
			printf_s("                                           <<<<<<<<<<<������ȷ,��½�ɹ�!>>>>>>>>>>>>>              \n\n");
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
					case 0:     return 1;  	//ѧ���˺�ע��
					case 1:     return 2;  	//ѧ���˺ŵ�¼
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