/*
@author : Li Hao, Fu Ning
@initalize date : 2019.7.2
*/

#pragma once

#include "cJSON.h"
#include<stdio.h>
#include <string>
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

	char buff[1024] = {};
	char* json_data = NULL;

	/*
	@fread(): ������ʵ��ȡ��������������count����ζ�Ų����˴���
	*/
	if (fread(buff, 1023, 1, fp)>=1023)
	{
		printf("\033[47;31mOpen file correctly!\n\033[0m");
		return NULL;
	}
	//����Json
	cJSON* stuJson = cJSON_Parse(buff);

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