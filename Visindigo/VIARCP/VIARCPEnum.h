#pragma once
#include "VIARCPPackageMeta.h"
class VIARCPEnum
{
	_Public enum Version : quint16 {
		V1_0 = 0x0001,
		Latest = V1_0
	};
	_Public enum Status : quint16 {
		Success = 0x0000,
		UnknownError = 0x0001,
		InternalError = 0x0002,
		ConnectionLost = 0x0003,
		UnknownFunction = 0x0101,
		ParameterTypeMismatch = 0x0102,
		ParmeterCountMismatch = 0x0103,
		ThrowException = 0x0104,
		ChunkParseFailed = 0x0201,
		MissingCALLChunk = 0x0202,
		MissingRETNChunk = 0x0203,
		IncorrectCALLorRETNChunk = 0x0204,
		HeadChunkLengthIsNotARCP = 0x0301,
		HeadChunkIsNotARCP = 0x0302,
		UnknownProtocalVersion = 0x0303,
		UnknownStatusCode = 0xFFFF
	};
	_Public static QString getStatusStr(Status code);
};