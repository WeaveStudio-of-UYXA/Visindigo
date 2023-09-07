#include "../VIARCPTypeManager.h"

#define VI_ENUMSTRMAP(Enum, Name) {#Name, Enum::Name}
QMap<QString, VIARCPTypeManager::TypeName> VIARCPTypeManager::TypeNameMapReverse = {
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Unknown),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Any),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, None),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, UInt32),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Int32),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, UInt64),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Int64),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Bool),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Float),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, Double),
	VI_ENUMSTRMAP(VIARCPTypeManager::TypeName, String),
};

QMap<VIARCPTypeManager::TypeName, QString> VIARCPTypeManager::UserRegTypeNameMap = {};
QMap<QString, VIARCPTypeManager::TypeName> VIARCPTypeManager::UserRegTypeNameMapReverse = {};

QString VIARCPTypeManager::getTypeNameString(VIARCPTypeManager::TypeName t) {
	switch (t) {
		VI_ENUMSTR(TypeName, Unknown);
		VI_ENUMSTR(TypeName, Any);
		VI_ENUMSTR(TypeName, None);
		VI_ENUMSTR(TypeName, UInt32);
		VI_ENUMSTR(TypeName, Int32);
		VI_ENUMSTR(TypeName, UInt64);
		VI_ENUMSTR(TypeName, Int64);
		VI_ENUMSTR(TypeName, Bool);
		VI_ENUMSTR(TypeName, Float);
		VI_ENUMSTR(TypeName, Double);
		VI_ENUMSTR(TypeName, String);
	default:
		if (UserRegTypeNameMap.contains(t)) {
			return UserRegTypeNameMap[t];
		}
	}
	return "Unknown";
}
VIARCPTypeManager::TypeName VIARCPTypeManager::registerNewTypeName(QString typeName) {
	if (UserRegTypeNameMapReverse.contains(typeName)) {
		return UserRegTypeNameMapReverse[typeName];
	}
	TypeName t = (TypeName)(UserRegTypeNameMap.size() + (int)TypeName::__UserStart__ + 1);
	UserRegTypeNameMap[t] = typeName;
	UserRegTypeNameMapReverse[typeName] = t;
	return t;
}
VIARCPTypeManager::TypeName VIARCPTypeManager::getTypeNameFromString(QString type) {
	if (TypeNameMapReverse.contains(type)) {
		return TypeNameMapReverse[type];
	}
	if (UserRegTypeNameMapReverse.contains(type)) {
		return UserRegTypeNameMapReverse[type];
	}
	return TypeName::Unknown;
}
VIARCPEnum::Status VIARCPTypeManager::checkData(const VIARCPDataChunk& chunk, TypeName type) {
	if (chunk.TypeNameLength == getTypeNameString(type).toUtf8().size()) {
		QByteArray tName = chunk.AllData.right(chunk.TypeNameLength);
		if (tName != getTypeNameString(type).toUtf8()) {
			return VIARCPEnum::Status::ParameterTypeMismatch;
		}
		if (chunk.DataLength + chunk.TypeNameLength > chunk.AllData.size()) {
			return VIARCPEnum::Status::ChunkParseFailed;
		}
		return VIARCPEnum::Status::Success;
	}
	return VIARCPEnum::Status::ParameterTypeMismatch;
}
VIARCPDataChunk VIARCPTypeManager::createChunkWithDataInType(const QByteArray& data, TypeName type) {
	QByteArray typeName = getTypeNameString(type).toUtf8();
	VIARCPDataChunk chunk;
	chunk.DataLength = data.size();
	chunk.TypeNameLength = typeName.size();
	chunk.AllData = data + typeName;
	return chunk;
}
VIARCPDataChunk VIARCPTypeManager::fromUInt32(quint32 value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(quint32)), TypeName::UInt32);
}
VIARCPEnum::Status VIARCPTypeManager::toUInt32(quint32* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::UInt32);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(quint32*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromInt32(qint32 value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(qint32)), TypeName::Int32);
}
VIARCPEnum::Status VIARCPTypeManager::toInt32(quint32* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::Int32);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(qint32*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromUInt64(quint64 value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(quint64)), TypeName::UInt64);
}
VIARCPEnum::Status VIARCPTypeManager::toUInt64(quint64* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::UInt64);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(quint64*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromInt64(qint64 value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(qint64)), TypeName::Int64);
}
VIARCPEnum::Status VIARCPTypeManager::toInt64(qint64* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::Int64);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(qint64*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromFloat(float value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(float)), TypeName::Float);
}
VIARCPEnum::Status VIARCPTypeManager::toFloat(float* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::Float);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(float*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromDouble(double value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(double)), TypeName::Double);
}
VIARCPEnum::Status VIARCPTypeManager::toDouble(double* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::Double);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(double*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromBool(bool value) {
	return createChunkWithDataInType(QByteArray((char*)&value, sizeof(bool)), TypeName::Bool);
}
VIARCPEnum::Status VIARCPTypeManager::toBool(bool* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::Bool);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = *(bool*)chunk.AllData.data();
		break;
	default:
		*rtn = 0;
		break;
	}
	return status;
}
VIARCPDataChunk VIARCPTypeManager::fromString(const QString& value) {
	QByteArray data = value.toUtf8();
	return createChunkWithDataInType(data, TypeName::String);
}
VIARCPEnum::Status VIARCPTypeManager::toString(QString* rtn, const VIARCPDataChunk& chunk) {
	auto status = checkData(chunk, TypeName::String);
	switch (status) {
	case VIARCPEnum::Status::Success:
		*rtn = QString::fromUtf8(chunk.AllData.data(), chunk.DataLength);
		break;
	default:
		*rtn = "";
		break;
	}
	return status;
}
