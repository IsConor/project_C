#pragma once
#ifndef _TEACHER_H_
#define _TEACHER_H_


typedef struct _Teacher {
	char name[64];
	int age;
	char* p;
	long plen;
}Teacher;


//����ṹ��
//p:���������������Ľṹ��
//outData:����������������֮����ַ���
//outlen���������������֮����ַ�������
int encodeTeacher(Teacher* p, char** outData, int* outlen);

//����ṹ��
//inData:�������
//inLen: inData�ĳ���
//p���������֮�������
int decodeTeacher(char* inData, int inLen, Teacher** p);

//�ͷ��ڴ溯��
void freeTeacher(Teacher** p);






#endif