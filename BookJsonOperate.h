#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>
#define LENGTH 4096

char bookBuff[LENGTH] = {};

char* stuQueryMenu[100], bookName[100][20];
int bookCnt;

/*
@File_ReadBooksInfoFromJson() : 从data_books.json文件中读取并解析成json格式
@返回 ： 装载Json结构体的指针
*/
cJSON* File_ReadBooksInfoFromJson()
{
	FILE* fp;
	if ((fp = fopen("data_books.json", "r+")) == NULL)
	{
		printf("Can't open file correctly!");
		return NULL;
	}
	
	char* json_data = NULL;

	/*
	@fread(): 返回真实读取的项数，若大于count则意味着产生了错误
	*/
	if (fread(bookBuff, LENGTH, 1, fp) >= LENGTH)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
	}
	//解析Json
	cJSON* stuJson = cJSON_Parse(bookBuff);

	free(json_data);
	return stuJson;
}

/*
@File_AddBookInfoToJson() : 将图书信息加载进json结构体中并写入data_books.json文件
@返回 ： 成功后再次返回Json结构体的指针
*/
cJSON* File_AddBookInfoToJson(cJSON* stuJson, int bookNo,
	char bookname[50], char publisher[50], char date[20], int count)
{
	cJSON* memberDetail = cJSON_CreateObject();
	char* buffer;
	FILE* fp;

	//生成嵌套Json对象
	cJSON_AddNumberToObject(memberDetail, "bookNo", bookNo);
	cJSON_AddStringToObject(memberDetail, "publisher", publisher);
	cJSON_AddStringToObject(memberDetail, "date", date);
	cJSON_AddNumberToObject(memberDetail, "count", count);
	cJSON_AddItemToObject(stuJson, bookname, memberDetail);

	//将Json结构格式化到缓冲区
	buffer = cJSON_Print(stuJson);
	//打开文件写入Json内容
	fp = fopen("data_books.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	fflush(fp);
	free(buffer);
	fclose(fp);
	
	return stuJson;
}

/*
@FILE_ModifyBookInfoToJson() : 从Json结构体中修改图书信息(数目)
@param 2 : 书本姓名
@param 3 : 增加/减少数量
*/
void FILE_ModifyBookInfoToJson(cJSON* bookJson, char bookName[50], int count)
{
	if (bookJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "出现错误: %s\n", errorPtr);
		}

	}
	cJSON* bookInfo = cJSON_GetObjectItem(bookJson, bookName);
	
	//获取count节点信息
	cJSON* item = cJSON_GetObjectItem(bookInfo, "count");
	int orgCount = item->valueint;
	//修改count节点
	cJSON_ReplaceItemInObject(bookInfo, "count", cJSON_CreateNumber(count+orgCount));
	//将Json结构格式化到缓冲区
	char * buffer =  cJSON_Print(bookJson);
	//打开文件写入Json内容
	FILE* fp = fopen("data_books.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	fflush(fp);
	free(buffer);
	fclose(fp);
}

/*
@FILE_ModifyStuInfoToJson() : 修改学生图书信息
*/
void FILE_ModifyStuInfoToJson( cJSON* stuJson, char bookname[50])
{
	char* buffer_book, * buffer_stu;
	FILE* fp_book, * fp_stu;


	//将Json结构格式化到缓冲区
	buffer_stu = cJSON_Print(stuJson);
	buffer_book = cJSON_Print(stuJson);
	//打开文件写入Json内容
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

void transfor(int t, char a[200], char b[20]);

void FILE_QueryAllBookInfo()
{
	char publisher[100][20], date[100][20];  int bookNo[100], count[100];
	cJSON* booksJson = bookJson->child;

	bookCnt = 0;


	char str4[100][20] = {};
	char str5[100][20] = {};
	char a[100][200];

	int i;
	

	while (booksJson != NULL)
	{
		memset(a[bookCnt], ' ', 150 * sizeof(char));
		strcpy(bookName[bookCnt], booksJson->string);
		bookNo[bookCnt] = booksJson->child->valueint;
		strcpy(publisher[bookCnt], booksJson->child->next->valuestring);
		strcpy(date[bookCnt], booksJson->child->next->next->valuestring);
		count[bookCnt] = booksJson->child->next->next->next->valueint;


		sprintf(str4[bookCnt], "%d", bookNo[bookCnt]);
		sprintf(str5[bookCnt], "%d", count[bookCnt]);
		i = strlen(date[bookCnt]);
		transfor(0, a[bookCnt], bookName[bookCnt]);
		transfor(23, a[bookCnt], publisher[bookCnt]);
		transfor(51, a[bookCnt], str4[bookCnt]);
		transfor(75, a[bookCnt], str5[bookCnt]);
		transfor(94, a[bookCnt], date[bookCnt]);
		a[bookCnt][94 + i] = '\0';


		//char* type(char bookname[], char publisher[], int bookNo, int count, char date[]);
		stuQueryMenu[bookCnt] = a[bookCnt];  
		//printf(stuQueryMenu[bookCnt]);
		booksJson = booksJson->next;
		bookCnt++;
	}
}

void transfor(int t, char a[200], char b[20])
{
	int m = 0, k;
	for (k = t; b[m] != '\0'; k++)
	{
		a[k] = b[m];
		m = m + 1;
	}
}
