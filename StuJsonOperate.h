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
@JsonParseTest() : Json 解析测试函数，没啥卵用（没调用）
@返回 ： 无
*/
void JsonParseTest()
{
	char  data[] = "{\"love\":[\"LOL\",\"Go shopping 哈哈哈\"]}";
	cJSON* stuJson = cJSON_Parse(data);
	char* json_data = NULL;
	printf("data:%s\n", json_data = cJSON_Print(stuJson));
	free(json_data);
	cJSON_Delete(stuJson);
}

/*
@File_ReadStuInfoToJson() : 从data.json文件中读取并解析成json格式
@返回 ： 装载Json结构体的指针
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
	@fread(): 返回真实读取的项数，若大于count则意味着产生了错误
	*/
	if (fread(stuBuff, 8096, 1, fp)>=8096)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
		return NULL;
	}
	//解析Json
	cJSON* stuJson = cJSON_Parse(stuBuff);

	free(json_data);
	return stuJson;
}

/*
@File_AddStuInfoToJson() : 将学生信息加载进json结构体中并写入data.json文件
@返回 ： 成功后再次返回Json结构体的指针
*/
cJSON* File_AddStuInfoToJson(cJSON* stuJson, char name[10], 
	char passwd[10], int classNumber, int stuNumber)
{
	//创建学生成员对象
	cJSON* memberDetail = cJSON_CreateObject();

	char* buffer;
	FILE* fp;

	//生成嵌套Json对象
	cJSON_AddNumberToObject(memberDetail, "stuNumber", stuNumber);
	cJSON_AddNumberToObject(memberDetail, "classNumber", classNumber);
	cJSON_AddStringToObject(memberDetail, "passwd", passwd);
	cJSON_AddNumberToObject(memberDetail, "bookNum", 0);
	cJSON_AddArrayToObject(memberDetail, "bookLists");
	cJSON_AddItemToObject(stuJson, name, memberDetail);

	//将Json结构格式化到缓冲区
	buffer = cJSON_Print(stuJson);
	//打开文件
	fp = fopen("data.json", "w");
	//写入Json内容
	fwrite(buffer, strlen(buffer), 1, fp);
	//刷新缓存区，及时写入
	fflush(fp);
	//释放内存
	free(buffer);
	//关闭文件
	fclose(fp);

	return stuJson;
}

/*
@FILE_StuPasswdQuery() :从Json结构体中读取学生的密码并比较
@返回 ： 正确（true）/ 错误（false）
*/
bool FILE_StuPasswdCompare(cJSON* stuJson, char name[50], char passwd[50])
{
	char passwdQuery[50];
	if (stuJson == NULL)
	{
		const char* errorPtr = cJSON_GetErrorPtr();
		if (errorPtr != NULL)
		{
			fprintf(stderr, "出现错误: %s\n", errorPtr);
		}
		return NULL;
	}
	//读取学生个人信息
	cJSON* individualInfo = cJSON_GetObjectItem(stuJson, name);
	//读取密码
	cJSON* item = cJSON_GetObjectItem(individualInfo, "passwd");
	//分配数组内存
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
			fprintf(stderr, "出现错误: %s\n", errorPtr);
		}
		return NULL;
	}
	//读取学生个人信息
	cJSON* individualInfo = cJSON_GetObjectItem(stuJson, name);
	//读取Array
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




