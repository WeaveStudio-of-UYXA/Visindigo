#pragma once
#include "VIARCPTypeManager.h"

#define VIARCPDataChunkBuilder(Type, Object) VIARCPStructConverter::fromStruct(#Type, Object)
class VIPublicAPI VIARCPStructConverter {
	VI_STATIC_CLASS(VIARCPStructConverter);
	_Public template<typename T>static VIARCPDataChunk fromStruct(const QString& name, const T& data) {
		VIARCPDataChunk chunk;
		chunk.AllData = name + QByteArray::fromRawData((const char*)(&T), sizeof(T));
		chunk.TypeNameLength = name.size();
		chunk.DataLength = sizeof(T);
		return chunk;
	}
};

#pragma pack(1)
struct EG{
	quint32 a, b, c, d;
};
void f() {
	EG eg;
	VIARCPDataChunkBuilder(EG, eg);
}