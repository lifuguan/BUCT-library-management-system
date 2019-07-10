#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>
#define LENGTH 4096
char buff[LENGTH] = {};

/*
@File_ReadBooksInfoFromJson() : ��data_books.json�ļ��ж�ȡ��������json��ʽ
@���� �� װ��Json�ṹ���ָ��
*/
cJSON* File_ReadBooksInfoFromJson()
{
	FILE* fp;
	if ((fp = fopen("data_books.json", "r+")) == NULL)
	{
		printf("\033[47;31mCan't open file correctly!\033[0m");
		return NULL;
	}
	
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
@File_AddBookInfoToJson() : ��ͼ����Ϣ���ؽ�json�ṹ���в�д��data_books.json�ļ�
@���� �� �ɹ����ٴη���Json�ṹ���ָ��
*/
cJSON* File_AddBookInfoToJson(cJSON* stuJson, int bookNo,
	char bookname[50], char publisher[50], char date[20], int count)
{
	cJSON* memberDetail = cJSON_CreateObject();
	char* buffer;
	FILE* fp;

	//����Ƕ��Json����
	cJSON_AddNumberToObject(memberDetail, "bookNo", bookNo);
	cJSON_AddStringToObject(memberDetail, "publisher", publisher);
	cJSON_AddStringToObject(memberDetail, "date", date);
	cJSON_AddNumberToObject(memberDetail, "count", count);
	cJSON_AddItemToObject(stuJson, bookname, memberDetail);

	//��Json�ṹ��ʽ����������
	buffer = cJSON_Print(stuJson);
	//���ļ�д��Json����
	fp = fopen("data_books.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	fflush(fp);
	free(buffer);
	fclose(fp);
	
	return stuJson;
}

/*
@FILE_ModifyBookInfoToJson() : ��Json�ṹ�����޸�ͼ����Ϣ(��Ŀ)
@param 2 : �鱾����
@param 3 : ����/��������
*/
void FILE_ModifyBookInfoToJson(cJSON* bookJson, char bookName[50], int count)
{
	if (bookJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "���ִ���: %s\n", errorPtr);
		}

	}
	cJSON* bookInfo = cJSON_GetObjectItem(bookJson, bookName);
	
	//��ȡcount�ڵ���Ϣ
	cJSON* item = cJSON_GetObjectItem(bookInfo, "count");
	int orgCount = item->valueint;
	//�޸�count�ڵ�
	cJSON_ReplaceItemInObject(bookInfo, "count", cJSON_CreateNumber(count+orgCount));
	//��Json�ṹ��ʽ����������
	char * buffer =  cJSON_Print(bookJson);
	//���ļ�д��Json����
	FILE* fp = fopen("data_books.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	fflush(fp);
	free(buffer);
	fclose(fp);
}

/*
@FILE_ModifyStuInfoToJson() : �޸�ѧ��ͼ����Ϣ
*/
void FILE_ModifyStuInfoToJson( cJSON* stuJson, char bookname[50])
{
	char* buffer_book, * buffer_stu;
	FILE* fp_book, * fp_stu;


	//��Json�ṹ��ʽ����������
	buffer_stu = cJSON_Print(stuJson);
	buffer_book = cJSON_Print(stuJson);
	//���ļ�д��Json����
	fp_stu = fopen("data.json", "w");
	fp_book = fopen("data_books.json", "w");

	fwrite(buffer_stu, strlen(buffer_stu), 1, fp_stu);
	fwrite(buffer_book, strlen(buffer_book), 1, fp_book);

	fflush(fp_stu);
	fflush(fp_book);

	free(buffer_stu);
	free(buffer_book);

	fclose(fp_stu);
	fclose(fp_book);
}

void FILE_QueryAllBookInfo(cJSON* booksJson)
{
	//int i = cJSON_get
}