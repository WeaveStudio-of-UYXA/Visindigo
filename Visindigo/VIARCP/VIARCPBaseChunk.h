#pragma once
#include "VIARCPPackageMeta.h"
#include "VIARCPEnum.h"
#pragma pack(1)
#define ARCP_UINT32_8 (quint32)0x00000008
#define ARCP_UINT16_2 (quint16)0x0002
#define ARCP_CONST_ARCPRNRN (quint64)0x415243500D0A0D0A
#define ARCP_CONST_CALL (quint32)0x43414C4C
#define ARCP_CONST_RETN (quint32)0x5245544E
struct VIPublicAPI VIARCPDataChunk
{
	quint32 DataLength = 0;
	quint16 TypeNameLength = 0;
	QByteArray AllData;
};
struct VIPublicAPI VIARCPHeadChunk
{
	quint32 DataLength = ARCP_UINT32_8;
	quint16 VersionNameLength = ARCP_UINT16_2;
	quint64 TagData = ARCP_CONST_ARCPRNRN;
	quint16 Version = (quint16)VIARCPEnum::Version::Latest;
};
struct VIPublicAPI VIARCPCallChunk
{
	quint32 DataLength = ARCP_UINT32_8;
	quint16 FunctionNameLength;
	quint32 TagData = ARCP_CONST_CALL;
	quint32 ParaCount = 0;
	QByteArray FunctionName;
};
struct VIPublicAPI VIARCPRetnChunk
{
	quint32 DataLength = ARCP_UINT32_8;
	quint16 StatusCodeLength = ARCP_UINT16_2;
	quint32 TagData = ARCP_CONST_RETN;
	quint32 ParaCount = 0;
	quint16 StatusCode = (quint16)VIARCPEnum::Status::Success;
};
#pragma pack()