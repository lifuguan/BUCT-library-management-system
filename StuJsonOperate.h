/*
@author : Li Hao
@initalize date : 2019.7.2
*/

#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>
void ProcessTest()
{
	char  data[] = "{\"love\":[\"LOL\",\"Go shopping 哈哈哈\"]}";
	cJSON* json = cJSON_Parse(data);
	char* json_data = NULL;
	printf("data:%s\n", json_data = cJSON_Print(json));
	free(json_data);
	cJSON_Delete(json);
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
	cJSON* json = cJSON_Parse(buff);

	free(json_data);
	return json;
}

/*
@File_AddStuInfoToJson() : 
*/
cJSON* File_AddStuInfoToJson(cJSON* json, char name[10], 
	char passwd[10], int classNumber, int stuNumber)
{
	cJSON* memberDetail = cJSON_CreateObject();
	char* buffer;
	FILE* fp;

	//生成嵌套json对象
	cJSON_AddNumberToObject(memberDetail, "stuNumber", stuNumber);
	cJSON_AddNumberToObject(memberDetail, "classNumber", classNumber);
	cJSON_AddStringToObject(memberDetail, "passwd", passwd);
	cJSON_AddNumberToObject(memberDetail, "bookNum", 0);
	cJSON_AddArrayToObject(memberDetail, passwd);
	cJSON_AddItemToObject(json, name, memberDetail);

	//将json结构格式化到缓冲区
	buffer = cJSON_Print(json);
	printf("data:\n%s\n", buffer = cJSON_Print(json));
	//打开文件写入json内容
	fp = fopen("data.json", "w");
	fwrite(buffer, strlen(buffer), 1, fp);
	free(buffer);
	fclose(fp);

	return json;
}