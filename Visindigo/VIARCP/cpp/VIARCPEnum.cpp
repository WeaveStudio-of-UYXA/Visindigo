#include "../VIARCPEnum.h"

QString VIARCPEnum::getStatusStr(VIARCPEnum::Status code) {
	switch (code) {
		VI_ENUMSTR(VIARCPEnum::Status, Success);
		VI_ENUMSTR(VIARCPEnum::Status, UnknownError);
		VI_ENUMSTR(VIARCPEnum::Status, InternalError);
		VI_ENUMSTR(VIARCPEnum::Status, ConnectionLost);
		VI_ENUMSTR(VIARCPEnum::Status, UnknownFunction);
		VI_ENUMSTR(VIARCPEnum::Status, ParameterTypeMismatch);
		VI_ENUMSTR(VIARCPEnum::Status, ParmeterCountMismatch);
		VI_ENUMSTR(VIARCPEnum::Status, ThrowException);
		VI_ENUMSTR(VIARCPEnum::Status, ChunkParseFailed);
		VI_ENUMSTR(VIARCPEnum::Status, MissingCALLChunk);
		VI_ENUMSTR(VIARCPEnum::Status, MissingRETNChunk);
		VI_ENUMSTR(VIARCPEnum::Status, IncorrectCALLorRETNChunk);
		VI_ENUMSTR(VIARCPEnum::Status, HeadChunkLengthIsNotARCP);
		VI_ENUMSTR(VIARCPEnum::Status, HeadChunkIsNotARCP);
		VI_ENUMSTR(VIARCPEnum::Status, UnknownProtocalVersion);
		VI_ENUMSTR(VIARCPEnum::Status, UnknownStatusCode);
	default:
		return "Unknown Status Code";
	}
}