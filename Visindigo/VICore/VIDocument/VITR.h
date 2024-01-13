#pragma once
#include "../VIObject.h"
#include "../VIConsole.h"

using QStringHashMap = QHash<QString, QString> ;

class VITranslationSubHost;
namespace  VIDocument {
	class VIPublicAPI VITR :public VIObject {
		Q_OBJECT;
		VI_OBJECT;
		friend class VITranslationSubHost;
		_Private QStringHashMap Translations;
		VI_Property(QString, FilePath);
		VI_PrivateFlag(Loaded);
		_Private def_init VITR();
		_Public bool load();
		_Private void parseLine(const QString& line);
		_Private QString translate(const QString& key);
	};
}