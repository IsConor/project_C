#include <stdio.h>
#include "teacher.h"
#include "itcast_asn1_der.h"
#include <stdlib.h>
#include <string.h>

/*
typedef struct _Teacher {
	char name[64];
	int age;
	char* p;
	long plen;
}Teacher;
*/

int encodeTeacher(Teacher* p, char** outData, int* outlen)
{
	//编码name
	// ITCAST_INT DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF **pOriginBuf, unsigned char *strOrigin, int strOriginLen);
	//ITCAST_INT DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING * pPrintString, ITASN1_PRINTABLESTRING * *ppDerPrintString);
	ITCAST_ANYBUF* head = NULL;
	ITCAST_ANYBUF* temp = NULL;
	ITCAST_ANYBUF* next = NULL;
	//将 char * ----> ITCAST_ANYBUF指针
	DER_ITCAST_String_To_AnyBuf(&temp, p->name, strlen(p->name) + 1);//temp传出参数
	//编码字符串数据
	DER_ItAsn1_WritePrintableString(&temp, &head);
	//释放内存
	ITCAST_INT DER_ITCAST_FreeQueue(temp);

	//编码age
	//ITCAST_INT DER_ItAsn1_WriteInter(ITCAST_UINT32 integer, ITASN1_INTEGER **ppDerInteger);
	DER_ItAsn1_WriteInteger(p->age, head->next);
	next = head->next;
	//编码p
	EncodeChar(p->p, strlen(p->p) + 1, &next->next);//将char * 类型数据进行编码
	next = next->next;
	//编码plen
	DER_ItAsn1_ReadInteger(p->plen, &next);
	//序列化
	DER_ItAsn1_WriteSequence(head, &temp);
	//输出参数赋值
	*outData = temp->pData;
	*outlen = temp->dataLen;
	//释放内存
	return 0;
}

int decodeTeacher(char* inData, int inLen, Teacher** p)
{
	ITCAST_ANYBUF* head = NULL;
	ITCAST_ANYBUF* temp = NULL;
	ITCAST_ANYBUF* next = NULL;

	Teacher* pt = (Teacher *)malloc(sizeof(Teacher));
	if (pt == NULL)
	{
		return -1;
	}
	//将inData反序列化成链表
	//将char* 转换成 ITCAST_ANYBUF类型
	DER_ITCAST_String_To_AnyBuf(&temp, inData, inLen);
	DER_ItAsn1_ReadSequence(temp, &head);
	DER_ITCAST_FreeQueue(temp);
	next = head->next;
	//解码name
	DER_ItAsn1_ReadPrintableString(&next, &temp);
	memcpy(pt->name, temp->pData, temp->dataLen);
	DER_ITCAST_FreeQueue(temp);
	next = next->next;
	//解码age
	DER_ItAsn1_ReadInteger(next, &pt->age);
	next = next->next;
	//解码p
	int len = 0;
	DecodeChar(next, &pt->p, &len);
	next = next->next;
	//解码plen
	DER_ItAsn1_ReadInteger(next, &pt->plen);
	//给输出参数赋值
	*p = pt;
	//释放内存
	DER_ITCAST_FreeQueue(head);
	return 0;
}

//释放内存
void freeTeacher(Teacher** p)
{
	if ((*p) != NULL)
	{
		if ((*p) != NULL)
		{
			free((*p)->p);
		}
		free(*p);
	}
}