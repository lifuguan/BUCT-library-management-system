#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>


/*
@File_ReadBooksInfoToJson() : ��data_book.json�ļ��ж�ȡ��������json��ʽ
@���� �� װ��Json�ṹ���ָ��
*/
cJSON* File_ReadBooksInfoToJson()
{
	FILE* fp;
	if ((fp = fopen("data_book.json", "r+")) == NULL)
	{
		printf("\033[47;31mCan't open file correctly!\033[0m");
		return NULL;
	}

	char buff[1024] = {};
	char* json_data = NULL;

	/*
	@fread(): ������ʵ��ȡ��������������count����ζ�Ų����˴���
	*/
	if (fread(buff, 1023, 1, fp) >= 1023)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
	}
	//����Json
	cJSON* stuJson = cJSON_Parse(buff);

	free(json_data);
	return stuJson;
}

/*
@File_AddBookInfoToJson() : ��ͼ����Ϣ���ؽ�json�ṹ���в�д��data_book.json�ļ�
@���� �� �ɹ����ٴη���Json�ṹ���ָ��
*/
cJSON* File_AddBookInfoToJson(cJSON* stuJson, char bookNo[10],
	char bookname[50], char publisher[50], char date[20], int count)
{
	cJSON* memberDetail = cJSON_CreateObject();
	char* buffer;
	FILE* fp;

	//����Ƕ��Json����
	cJSON_AddStringToObject(memberDetail, "bookNo", bookNo);
	cJSON_AddStringToObject(memberDetail, "publisher", publisher);
	cJSON_AddStringToObject(memberDetail, "date", date);
	cJSON_AddNumberToObject(memberDetail, "count", count);
	cJSON_AddItemToObject(stuJson, bookname, memberDetail);

	//��Json�ṹ��ʽ����������
	buffer = cJSON_Print(stuJson);
	//���ļ�д��Json����
	fp = fopen("data_book.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	fflush(fp);
	free(buffer);
	fclose(fp);
	
	return stuJson;
}

/*
@FILE_StuPasswdQuery() :��Json�ṹ���ж�ȡѧ�������벢�Ƚ�
@���� �� ��ȷ��true��/ ����false��
*/
bool FILE_StuPasswdCompare(cJSON* stuJson, char name[10], char passwd[10])
{
	char passwdQuery[10];
	if (stuJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "���ִ���: %s\n", errorPtr);
		}
		return NULL;
	}
	cJSON* individualInfo = cJSON_GetObjectItem(stuJson, name);
	cJSON* item = cJSON_GetObjectItem(individualInfo, "passwd");
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


void FILE_StuBrorrowOperate(cJSON* bookJson, cJSON* stuJson, char bookname[50])
{
	char* buffer_book, * buffer_stu;
	FILE* fp_book, * fp_stu;


	//��Json�ṹ��ʽ����������
	buffer_stu = cJSON_Print(stuJson);
	buffer_book = cJSON_Print(stuJson);
	//���ļ�д��Json����
	fp_stu = fopen("data.json", "w");
	fp_book = fopen("data_book.json", "w");

	fwrite(buffer_stu, strlen(buffer_stu), 1, fp_stu);
	fwrite(buffer_book, strlen(buffer_book), 1, fp_book);

	fflush(fp_stu);
	fflush(fp_book);

	free(buffer_stu);
	free(buffer_book);

	fclose(fp_stu);
	fclose(fp_book);
}
void FILE_AdminAddBookInfoToJson(cJSON* bookJson, char bookname[50])
{

}