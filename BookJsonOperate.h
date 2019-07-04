#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>


/*
@File_ReadBooksInfoToJson() : 从data_book.json文件中读取并解析成json格式
@返回 ： 装载Json结构体的指针
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
	@fread(): 返回真实读取的项数，若大于count则意味着产生了错误
	*/
	if (fread(buff, 1023, 1, fp) >= 1023)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
	}
	//解析Json
	cJSON* stuJson = cJSON_Parse(buff);

	free(json_data);
	return stuJson;
}

/*
@File_AddBookInfoToJson() : 将学生信息加载进json结构体中并写入data_book.json文件
@返回 ： 成功后再次返回Json结构体的指针
*/
cJSON* File_AddBookInfoToJson(cJSON* stuJson, char bookNo[10],
	char bookname[50], char publisher[50], char date[20], int count)
{
	cJSON* memberDetail = cJSON_CreateObject();
	char* buffer;
	FILE* fp;

	//生成嵌套Json对象
	cJSON_AddStringToObject(memberDetail, "bookname", bookname);
	cJSON_AddStringToObject(memberDetail, "publisher", publisher);
	cJSON_AddStringToObject(memberDetail, "date", date);
	cJSON_AddNumberToObject(memberDetail, "count", count);
	cJSON_AddItemToObject(stuJson, bookNo, memberDetail);

	//将Json结构格式化到缓冲区
	buffer = cJSON_Print(stuJson);
	printf("data:\n%s\n", buffer = cJSON_Print(stuJson));
	//打开文件写入Json内容
	fp = fopen("data_book.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	fflush(fp);
	free(buffer);
	fclose(fp);
	
	return stuJson;
}

/*
@FILE_StuPasswdQuery() :从Json结构体中读取学生的密码并比较
@返回 ： 正确（true）/ 错误（false）
*/
bool FILE_StuPasswdCompare(cJSON* stuJson, char name[10], char passwd[10])
{
	char passwdQuery[10];
	if (stuJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "出现错误: %s\n", errorPtr);
		}
		return NULL;
	}
	cJSON* individualInfo = cJSON_GetObjectItem(stuJson, name);
	cJSON* item = cJSON_GetObjectItem(individualInfo, "passwd");
	memcpy(passwdQuery, item->valuestring, strlen(item->valuestring));

	//长度不一致 false
	if (strlen(item->valuestring) != strlen(passwd))
	{
		return false;
	}
	//字符不一致  错误
	for (int i = 0; i < strlen(passwd); i++)
	{
		if (passwd[i] != passwdQuery[i])
		{
			return false;
		}
	}
	return true;
}