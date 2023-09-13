#pragma once
#include "VIARCPPackageMeta.h"
#include "VIARCPBaseChunk.h"
#include "VIARCPEnum.h"
class VIPublicAPI VIARCPTypeManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_STATIC_CLASS(VIARCPTypeManager);
	_Public enum class TypeName {
		Unknown,
		Any,
		None,
		UInt32, Int32, UInt64, Int64, Bool,
		Float, Double,
		String,
		Json,
		Binary,
		__UserStart__ = 1000,
		__UserEnd__ = 10000,
	};
	_Private static QMap<QString, TypeName> TypeNameMapReverse;
	_Private static QMap<TypeName, QString> UserRegTypeNameMap;
	_Private static QMap<QString, TypeName> UserRegTypeNameMapReverse;
	_Public static QString getTypeNameString(TypeName t);
	_Public static TypeName registerNewTypeName(QString typeName);
	_Public static TypeName getTypeNameFromString(QString type);
	_Public static VIARCPEnum::Status checkData(const VIARCPDataChunk& chunk, TypeName type);
	_Public static VIARCPDataChunk createChunkWithDataInType(const QByteArray& data, TypeName type);
	_Public static VIARCPDataChunk fromUInt32(quint32 value);
	_Public static VIARCPEnum::Status toUInt32(quint32* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromInt32(qint32 value);
	_Public static VIARCPEnum::Status toInt32(quint32* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromUInt64(quint64 value);
	_Public static VIARCPEnum::Status toUInt64(quint64* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromInt64(qint64 value);
	_Public static VIARCPEnum::Status toInt64(qint64* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromFloat(float value);
	_Public static VIARCPEnum::Status toFloat(float* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromDouble(double value);
	_Public static VIARCPEnum::Status toDouble(double* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromBool(bool value);
	_Public static VIARCPEnum::Status toBool(bool* rtn, const VIARCPDataChunk& chunk);
	_Public static VIARCPDataChunk fromString(const QString& value);
	_Public static VIARCPEnum::Status toString(QString* rtn, const VIARCPDataChunk& chunk);
};