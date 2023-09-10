
#include "itcast_asn1_der.h"

ITCAST_INT
DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF** pOriginBuf,
	unsigned char* strOrigin,
	int  strOriginLen)
{
	ITCAST_ANYBUF* pValueBuf;

	pValueBuf = malloc(sizeof(ITCAST_ANYBUF));
	if (pValueBuf == NULL)
	{
		ITDER_LOG(__FILE__, __LINE__, LogLevel[4], ITDER_MemoryErr, "malloc err");
		return ITDER_MemoryErr;
	}
	memset(pValueBuf, 0, sizeof(ITCAST_ANYBUF));

	if (strOriginLen <= 0)
	{
		pValueBuf->pData = NULL;
		strOriginLen = 0;
	}
	else
	{
		pValueBuf->pData = (unsigned char*)malloc(strOriginLen);
		if (pValueBuf->pData == NULL)
		{
			DER_ITCAST_Free(pValueBuf);
			ITDER_LOG(__FILE__, __LINE__, LogLevel[4], ITDER_LengthErr, "malloc err");
			return ITDER_MemoryErr;
		}
		memcpy(pValueBuf->pData, strOrigin, strOriginLen);
	}
	pValueBuf->dataLen = strOriginLen;
	pValueBuf->dataType = ITCAST_DER_ID_STRING_PRINTABLE;
	pValueBuf->next = NULL;
	pValueBuf->prev = NULL;
	pValueBuf->unusedBits = (strOriginLen % 8);
	pValueBuf->memoryType = 0;
	*pOriginBuf = pValueBuf;
	return ITDER_NoErr;
}



//DER编码PrintableString类型数据
ITCAST_INT
DER_ItAsn1_WritePrintableString(
	ITASN1_PRINTABLESTRING* pPrintString,
	ITASN1_PRINTABLESTRING** ppDerPrintString)
{
	int iResult;

	if (pPrintString->dataType == ITCAST_DER_STRING_BMP)
	{
		iResult = DER_ItAsn1_WriteBmpString(pPrintString, ppDerPrintString);
		if (iResult != ITDER_NoErr)
		{
			ITDER_LOG(__FILE__, __LINE__, LogLevel[4], iResult, "func DER_ItAsn1_WriteBmpString() err");
			return  iResult;
		}

	}
	else
	{
		iResult = DER_ItAsn1_WriteCharString(pPrintString, ppDerPrintString);
		if (iResult != ITDER_NoErr)
		{
			ITDER_LOG(__FILE__, __LINE__, LogLevel[4], iResult, "func DER_ItAsn1_WriteCharString() err");
			return  iResult;
		}
	}

	return 0;
}
