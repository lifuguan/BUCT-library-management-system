// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include "DataQuery.h"

int main()
{
	//ProcessTest();
	cJSON* json = File_ReadStueInfoToJson();
	File_AddStuInfoToJson(json);
	return 0;
}

