#pragma once

#define CE_USE_QT

#ifdef CE_USE_QT
#include <QtCore>
#endif

//The macros in this file are used to enhance the Qt development experience. 
//If there is no Qt environment, they will not be activated
#ifdef QT_VERSION_MAJOR
	#if (QT_VERSION_MAJOR==5)
		#ifndef CE_QT_5
		#define CE_QT_5
	#endif
#elif (QT_VERSION_MAJOR==6)
	#ifndef CE_QT_6
		#define CE_QT_6
		#endif
	#endif
#endif

#ifdef QT_VERSION_MAJOR
	#define CE_QT_KEYWORDS
		#define Slots public Q_SLOTS:
#endif

#ifdef QT_VERSION_MAJOR
	#define connectPushButton(QPushButton_Object,Target_Object,Slot) connect(QPushButton_Object,SIGNAL(clicked()),Target_Object,SLOT(Slot))
	#define connectAction(QAction_Object,Target_Object,Slot) connect(QAction_Object,SIGNAL(triggered()),Target_Object,SLOT(Slot))
#endif

#ifndef Q_NULLPTR
	#define Q_NULLPTR nullptr
#endif