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
	//����name
	// ITCAST_INT DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF **pOriginBuf, unsigned char *strOrigin, int strOriginLen);
	//ITCAST_INT DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING * pPrintString, ITASN1_PRINTABLESTRING * *ppDerPrintString);
	ITCAST_ANYBUF* head = NULL;
	ITCAST_ANYBUF* temp = NULL;
	ITCAST_ANYBUF* next = NULL;
	//�� char * ----> ITCAST_ANYBUFָ��
	DER_ITCAST_String_To_AnyBuf(&temp, p->name, strlen(p->name) + 1);//temp��������
	//�����ַ�������
	DER_ItAsn1_WritePrintableString(&temp, &head);
	//�ͷ��ڴ�
	ITCAST_INT DER_ITCAST_FreeQueue(temp);

	//����age
	//ITCAST_INT DER_ItAsn1_WriteInter(ITCAST_UINT32 integer, ITASN1_INTEGER **ppDerInteger);
	DER_ItAsn1_WriteInteger(p->age, head->next);
	next = head->next;
	//����p
	EncodeChar(p->p, strlen(p->p) + 1, &next->next);//��char * �������ݽ��б���
	next = next->next;
	//����plen
	DER_ItAsn1_ReadInteger(p->plen, &next);
	//���л�
	DER_ItAsn1_WriteSequence(head, &temp);
	//���������ֵ
	*outData = temp->pData;
	*outlen = temp->dataLen;
	//�ͷ��ڴ�
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
	//��inData�����л�������
	//��char* ת���� ITCAST_ANYBUF����
	DER_ITCAST_String_To_AnyBuf(&temp, inData, inLen);
	DER_ItAsn1_ReadSequence(temp, &head);
	DER_ITCAST_FreeQueue(temp);
	next = head->next;
	//����name
	DER_ItAsn1_ReadPrintableString(&next, &temp);
	memcpy(pt->name, temp->pData, temp->dataLen);
	DER_ITCAST_FreeQueue(temp);
	next = next->next;
	//����age
	DER_ItAsn1_ReadInteger(next, &pt->age);
	next = next->next;
	//����p
	int len = 0;
	DecodeChar(next, &pt->p, &len);
	next = next->next;
	//����plen
	DER_ItAsn1_ReadInteger(next, &pt->plen);
	//�����������ֵ
	*p = pt;
	//�ͷ��ڴ�
	DER_ITCAST_FreeQueue(head);
	return 0;
}

//�ͷ��ڴ�
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