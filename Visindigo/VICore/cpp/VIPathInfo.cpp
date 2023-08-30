#include "../VIPathInfo.h"

qint64 VIPathInfo::getSizeOf(QString path) {
	QDir dir(path);
	qint64 size = 0;
	for (QFileInfo fileInfo : dir.entryInfoList(QDir::Files)) {
		size += fileInfo.size();
	}
	for (QString subDir : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
		size += getSizeOf(path + QDir::separator() + subDir);
	}
	return size;
}

QString VIPathInfo::getCountingUnitStr(Visindigo::CountingUnit c) {
	switch (c)
	{
		VI_ENUMSTR(Visindigo, K);
		VI_ENUMSTR(Visindigo, M);
		VI_ENUMSTR(Visindigo, G);
		VI_ENUMSTR(Visindigo, T);
		VI_ENUMSTR(Visindigo, P);
		VI_ENUMSTR(Visindigo, E);
		VI_ENUMSTR(Visindigo, Z);
		VI_ENUMSTR(Visindigo, Y);
	default:
		return "";
	}
}

QString VIPathInfo::getReadableSize(double rawSize, Visindigo::BinarySizeUnit u, Visindigo::CountingUnit c , Visindigo::BinarySizeFormat f) {
	if (rawSize >= (int)f) {
		return getReadableSize(rawSize / (int)f, u, (Visindigo::CountingUnit)(c + 1), f);
	}
	else {
		QString suffix = QString::number(rawSize, 'f', 2);
		suffix += getCountingUnitStr(c);
		if (f == Visindigo::IEC) {
			suffix += "i";
		}
		if (u == Visindigo::Byte) {
			suffix += "B";
		}
		else {
			suffix += "b";
		}
		return suffix;
	}
}