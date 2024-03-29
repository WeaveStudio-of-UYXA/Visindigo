﻿#pragma once
#include "../VICore/VIObject.h"
#include "VIPalette.h"
#include <QtWidgets>

class VIPublicAPI VIDynamicStyleSheet :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public static QStringList hasDynamicSize(const QString& qss);
	_Public static QStringList hasDynamicColor(const QString& qss);
};

class VIPublicAPI VIDynamicStyleSheetContainer  //此类一定不要继承自VIObject
{
	_Private QString QSS;
	_Private QWidget* MasterWidget;
	VI_PrivateFlag(HasDynamicSize);
	VI_PrivateFlag(HasDynamicColor);
	QStringList DynamicSizeList;
	QStringList DynamicColorList;
	_Public def_init VIDynamicStyleSheetContainer();
	_Public def_init VIDynamicStyleSheetContainer(QWidget* masterWidget, const QString& qss);
	_Public def_copy VIDynamicStyleSheetContainer(const VIDynamicStyleSheetContainer& other);
	_Public VIDynamicStyleSheetContainer& operator=(const VIDynamicStyleSheetContainer& other);
	_Public def_move VIDynamicStyleSheetContainer(VIDynamicStyleSheetContainer&& other);
	_Public void applyVIDSS();
	_Private void applyDynamicSize(QString* vidss);
	_Private void applyDynamicColor(QString* vidss);
	_Public void setVIDSS(const QString& qss);
	_Public void setMasterWidget(QWidget* masterWidget);
};

using VIDynamicStyleSheetContainerHash = QHash<QString, VIDynamicStyleSheetContainer>;
using VIDynamicStyleSheetContainerWidgetHash = QHash<QWidget*, VIDynamicStyleSheetContainerHash>;
using VIDynamicStyleSheetNameHash = QHash<QWidget*, QString>;
class VIPublicAPI VIDynamicStyleSheetManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(VIDynamicStyleSheetManager);
	_Private VIDynamicStyleSheetContainerWidgetHash VIDSSContainerHash;
	_Private VIDynamicStyleSheetNameHash VIDSSNameHash;
	_Public def_init VIDynamicStyleSheetManager(VISuper* parent);
	_Public void addVIDSS(QWidget* masterWidget, const QString& name, const QString& qss);
	_Public void applyVIDSS(QWidget* masterWidget, const QString& name);
	_Public QString getCurrentVIDSSName(QWidget* masterWidget);
	_Slot void refreshVIDSS();
	_Public void refreshVIDSS(QWidget* masterWidget);
};