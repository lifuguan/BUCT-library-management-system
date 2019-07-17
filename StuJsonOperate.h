/*
@author : Li Hao, Fu Ning
@initalize date : 2019.7.2
*/

#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>

char stuBuff[8096] = {};

char* stuReturnMenu[10], str[10][150];

/*
@JsonParseTest() : Json �������Ժ�����ûɶ���ã�û���ã�
@���� �� ��
*/
void JsonParseTest()
{
	char  data[] = "{\"love\":[\"LOL\",\"Go shopping ������\"]}";
	cJSON* stuJson = cJSON_Parse(data);
	char* json_data = NULL;
	printf("data:%s\n", json_data = cJSON_Print(stuJson));
	free(json_data);
	cJSON_Delete(stuJson);
}

/*
@File_ReadStuInfoToJson() : ��data.json�ļ��ж�ȡ��������json��ʽ
@���� �� װ��Json�ṹ���ָ��
*/
cJSON* File_ReadStuInfoToJson()
{
	FILE* fp;
	if ((fp = fopen("data.json", "r+")) == NULL)
	{
		printf("\033[47;31mCan't open file correctly!\033[0m");
		return NULL;
	}

	
	char* json_data = NULL;

	/*
	@fread(): ������ʵ��ȡ��������������count����ζ�Ų����˴���
	*/
	if (fread(stuBuff, 8096, 1, fp)>=8096)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
		return NULL;
	}
	//����Json
	cJSON* stuJson = cJSON_Parse(stuBuff);

	free(json_data);
	return stuJson;
}

/*
@File_AddStuInfoToJson() : ��ѧ����Ϣ���ؽ�json�ṹ���в�д��data.json�ļ�
@���� �� �ɹ����ٴη���Json�ṹ���ָ��
*/
cJSON* File_AddStuInfoToJson(cJSON* stuJson, char name[10], 
	char passwd[10], int classNumber, int stuNumber)
{
	//����ѧ����Ա����
	cJSON* memberDetail = cJSON_CreateObject();

	char* buffer;
	FILE* fp;

	//����Ƕ��Json����
	cJSON_AddNumberToObject(memberDetail, "stuNumber", stuNumber);
	cJSON_AddNumberToObject(memberDetail, "classNumber", classNumber);
	cJSON_AddStringToObject(memberDetail, "passwd", passwd);
	cJSON_AddNumberToObject(memberDetail, "bookNum", 0);
	cJSON_AddArrayToObject(memberDetail, "bookLists");
	cJSON_AddItemToObject(stuJson, name, memberDetail);

	//��Json�ṹ��ʽ����������
	buffer = cJSON_Print(stuJson);
	//���ļ�
	fp = fopen("data.json", "w");
	//д��Json����
	fwrite(buffer, strlen(buffer), 1, fp);
	//ˢ�»���������ʱд��
	fflush(fp);
	//�ͷ��ڴ�
	free(buffer);
	//�ر��ļ�
	fclose(fp);

	return stuJson;
}

/*
@FILE_StuPasswdQuery() :��Json�ṹ���ж�ȡѧ�������벢�Ƚ�
@���� �� ��ȷ��true��/ ����false��
*/
bool FILE_StuPasswdCompare(cJSON* stuJson, char name[50], char passwd[50])
{
	char passwdQuery[50];
	if (stuJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "���ִ���: %s\n", errorPtr);
		}
		return NULL;
	}
	//��ȡѧ��������Ϣ
	cJSON* individualInfo = cJSON_GetObjectItem(stuJson, name);
	//��ȡ����
	cJSON* item = cJSON_GetObjectItem(individualInfo, "passwd");
	//���������ڴ�
	memcpy(passwdQuery, item->valuestring, strlen(item->valuestring));

	//���Ȳ�һ�� false
	if (strlen(item->valuestring) != strlen(passwd))
	{
		return false;
	}
	//�ַ���һ��  ����
	for (int i = 0; i < strlen(passwd); i++)
	{
		if (passwd[i] != passwdQuery[i])
		{
			return false;
		}
	}
	return true;
}

void STU_transfor(int t, char a[150], char b[20])
{
	int m = 0, k;
	for (k = t; b[m] != '\0'; k++)
	{
		a[k] = b[m];
		m = m + 1;
	}
}

int FILE_StuBookReturnQuery(cJSON* stuJson, char name[50])
{
	if (stuJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "���ִ���: %s\n", errorPtr);
		}
		return NULL;
	}
	//��ȡѧ��������Ϣ
	cJSON* individualInfo = cJSON_GetObjectItem(stuJson, name);
	//��ȡArray
	cJSON* books = cJSON_GetObjectItem(individualInfo, "bookLists");
	int bookSize = cJSON_GetArraySize(books);
	char publisher[10][20], date[10][20], str3[10][20], str4[10][20];  int bookNo[10], count[10];
	for (int iCnt = 0; iCnt < bookSize; iCnt++)
	{
		cJSON* pBook = cJSON_GetArrayItem(books, iCnt);
		if (pBook == NULL)
		{
			continue;
		}
		memset(str[iCnt], ' ', 150 * sizeof(char));
		cJSON* book = cJSON_GetObjectItem(bookJson, pBook->valuestring);
		bookNo[iCnt] = book->child->valueint;
		strcpy(publisher[iCnt], book->child->next->valuestring);
		strcpy(date[iCnt], book->child->next->next->valuestring);
		count[iCnt] = 1;
		sprintf(str3[iCnt], "%d", bookNo[iCnt]);
		sprintf(str4[iCnt], "%d", count[iCnt]);
		int i = strlen(date[iCnt]);
		STU_transfor(0, str[iCnt], pBook->valuestring);
		STU_transfor(23, str[iCnt], publisher[iCnt]);
		STU_transfor(51, str[iCnt], str3[iCnt]);
		STU_transfor(75, str[iCnt], str4[iCnt]);
		STU_transfor(94, str[iCnt], date[iCnt]);
		str[iCnt][94 + i] = '\0';

		stuReturnMenu[iCnt] = str[iCnt];
	}

	return bookSize;
}




