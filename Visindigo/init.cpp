#include "init.h"

void doQRegisterMetaType() {
	qRegisterMetaType<VIMath::VI2DMatrix>("VIMath::VI2DMatrix");
	qRegisterMetaType<VIMath::VIVector2>("VIMath::VIVector2");
	qRegisterMetaType<VIMath::VIMatrix>("VIMath::VIMatrix");
	qRegisterMetaType<QList<QList<int>>>("QList<QList<int>>");
	//qRegisterMetaType<VITextLabel>("VITextLabel");
}