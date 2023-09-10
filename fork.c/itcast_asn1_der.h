#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"

#pragma once
#ifndef _ITCAST_ASN1_DER_H_
#define _ITCAST_ASN1_DER_H_

#ifdef _cplusplus
extern "C"
#endif

#define ITCASTDER_NoErr 0


//别名
typedef int					ITCAST_INT;
typedef unsigned char       ITCAST_UINT8;
typedef unsigned short      ITCAST_UINT16;
typedef unsigned long		ITCAST_UINT32;
typedef signed long         ITCAST_SINT32;

//错误
#define TRUE 1
#define FALSE 0

#define     ITDER_NoErr                 0
#define     ITDER_MemoryErr             200
#define     ITDER_LengthErr             201
#define     ITDER_LengthNotEqualErr     202
#define     ITDER_DataRangeErr          203
#define     ITDER_InvalidTagErr         204


enum {
    ITCAST_DER_ID_RESERVED,
    ITCAST_DER_ID_BOOLEAN,
    ITCAST_DER_ID_INTEGER,
    ITCAST_DER_ID_BITSTRING,
    ITCAST_DER_ID_OCTETSTRING,
    ITCAST_DER_ID_NULL,
    ITCAST_DER_ID_OBJECT_IDENTIFIER,
    ITCAST_DER_ID_OBJECT_DESCRIPTOR,
    ITCAST_DER_ID_EXTERNAL,
    ITCAST_DER_ID_REAL,
    ITCAST_DER_ID_ENUMERATED,
    ITCAST_DER_ID_EMBEDDED_PDV,
    ITCAST_DER_ID_STRING_UTF8,
    ITCAST_DER_ID_13,
    ITCAST_DER_ID_14,
    ITCAST_DER_ID_15,
    ITCAST_DER_ID_SEQUENCE,
    ITCAST_DER_ID_SET,
    ITCAST_DER_ID_STRING_NUMERIC,
    ITCAST_DER_ID_STRING_PRINTABLE,
    ITCAST_DER_ID_STRING_T61,
    ITCAST_DER_ID_STRING_VIDEOTEX,
    ITCAST_DER_ID_STRING_IA5,
    ITCAST_DER_ID_TIME_UTC,
    ITCAST_DER_ID_TIME_GENERALIZED,
    ITCAST_DER_ID_STRING_GRAPHIC,
    ITCAST_DER_ID_STRING_ISO646,
    ITCAST_DER_ID_STRING_GENERAL,
    ITCAST_DER_ID_STRING_UNIVERSAL,
    ITCAST_DER_ID_29,
    ITCAST_DER_ID_STRING_BMP
};

#define ITCAST_DER_CONSTRUCTED      0X20
#define ITCAST_DER_PRIMITIVE        0X00

#define ITCAST_DER_UNIVERSAL        0X00
#define ITCAST_DER_PRIMITIVE        0X00




//结构体
typedef struct ITCAST_ANYBUF_ {

    unsigned char* pData;
    ITCAST_UINT32     dataLen;

    ITCAST_UINT32     unusedBits;  /* for bit string */
    ITCAST_UINT32     memoryType;
    ITCAST_UINT32     dataType;
    struct ITCAST_ANYBUF_* next;    /* for sequence and set */
    struct ITCAST_ANYBUF_* prev;

}ITCAST_ANYBUF;

//别名
typedef ITCAST_UINT8     ITASN1_BOOLEAN;
typedef ITCAST_ANYBUF    ITASN1_INTEGER;
typedef ITCAST_ANYBUF    ITASN1_OCTETSTRING;
typedef ITCAST_ANYBUF    ITASN1_BITSTRING;
typedef ITCAST_ANYBUF    ITASN1_PRINTABLESTRING;
/*begin of bmpstring*/
typedef ITCAST_ANYBUF	 ITASN1_BMPSTRING;
/*end of bmpstring*/
typedef ITCAST_ANYBUF    ITASN1_ENUMERATED;
typedef ITCAST_ANYBUF    ITASN1_IA5STRING;
typedef ITCAST_ANYBUF    ITASN1_SEQUENCE;
typedef ITCAST_ANYBUF    ITASN1_SET;


//函数
ITCAST_INT
DER_ItAsn1_WriteInteger(ITCAST_UINT32 integer, ITASN1_INTEGER** ppDerInteger);

ITCAST_INT
DER_ItAsn1_ReadInteger(ITASN1_INTEGER* pDerInteger, ITCAST_UINT32* pInteger);

ITCAST_INT
DER_ItAsn1_WriteBitString(ITASN1_BITSTRING* pBitString, ITASN1_BITSTRING** ppDerBitString);

ITCAST_INT
DER_ItAsn1_ReadBitString(ITASN1_BITSTRING* pDerBitString, ITASN1_BITSTRING** ppBitString);


ITCAST_INT
DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING* pPrintString,
    ITASN1_PRINTABLESTRING** ppDerPrintString);

ITCAST_INT
DER_ItAsn1_ReadPrintableString(ITASN1_PRINTABLESTRING* pDerPrintString,
    ITASN1_PRINTABLESTRING** ppPrintString);

ITCAST_INT
DER_ItAsn1_WriteSequence(ITASN1_SEQUENCE* pSequence, ITCAST_ANYBUF** ppDerSequence);

ITCAST_INT
DER_ItAsn1_ReadSequence(ITCAST_ANYBUF* pDerSequence, ITASN1_SEQUENCE** ppSequence);

ITCAST_INT
DER_ItAsn1_WriteNull(ITCAST_ANYBUF** ppDerNull);

ITCAST_INT
DER_ItAsn1_ReadNull(ITCAST_ANYBUF* ppDerNull, ITCAST_UINT8* pInt);

ITCAST_INT
DER_ITCAST_FreeQueue(ITCAST_ANYBUF* pAnyBuf);

ITCAST_INT
DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF** pOriginBuf, unsigned char* strOrigin, int strOriginLen);

int WriteNullSequence(ITCAST_ANYBUF** pOutData);

int EncodeChar(char* pData, int dataLen, ITCAST_ANYBUF** outBuf);

int EncodeUnsignedChar(unsigned char* pData, int dataLen, ITCAST_ANYBUF** outBuf);

int DecodeChar(ITCAST_ANYBUF* inBuf, char** Data, int* pDataLen);

#ifdef _cplusplus
}
#endif

#endif