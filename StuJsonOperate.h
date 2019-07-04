/*
@author : Li Hao, Fu Ning
@initalize date : 2019.7.2
*/

#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>
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
@File_ReadStueInfoToJson() :
*/
cJSON* File_ReadStueInfoToJson()
{
	FILE* fp;
	if ((fp = fopen("data.json", "r+")) == NULL)
	{
		printf("\033[47;31mCan't open file correctly!\033[0m");
		return NULL;
	}

	char buff[1024] = {};
	char* json_data = NULL;

	/*
	@fread(): 返回真实读取的项数，若大于count则意味着产生了错误
	*/
	if (fread(buff, 1023, 1, fp)>=1023)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
	}
	//解析Json
	cJSON* stuJson = cJSON_Parse(buff);

	free(json_data);
	return stuJson;
}

/*
@File_AddStuInfoToJson() : 
*/
cJSON* File_AddStuInfoToJson(cJSON* stuJson, char name[10], 
	char passwd[10], int classNumber, int stuNumber)
{
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
	printf("data:\n%s\n", buffer = cJSON_Print(stuJson));
	//打开文件写入Json内容
	fp = fopen("data.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	free(buffer);
	fclose(fp);

	return stuJson;
}

/*
@FILE_StuPasswdQuery() :
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