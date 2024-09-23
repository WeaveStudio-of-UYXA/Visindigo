#pragma once
#include "VIAbstractObject.h"
#include <QtCore>

class VIMiCoreAPI VIQCoreApplication :public QCoreApplication, public VIAbstractObject
{
	Q_OBJECT;
	VI_OBJECT;

	_Public def_init VIQCoreApplication(int& argc, char** argv);
	_Public def_copy VIQCoreApplication(const VIQCoreApplication& other) = delete;
	_Public def_move VIQCoreApplication(VIQCoreApplication&& other) = delete;
	_Protected virtual bool notify(QObject* receiver, QEvent* e) override;
};
