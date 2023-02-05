#pragma once
#include "macro/VIVersion_m.h"
//此文件定义VI版本号类和自由信息类

class VIVersion :public QObject {
	Q_OBJECT;
	_Protected VersionList Version;
	_Public def_init VIVersion(VersionList InitVersion = { 0,0,0 });
	_Public int getVersionLength();
	_Public VersionNum getVersionNum(int index);
	_Public bool operator>(VIVersion& ver);
	_Public bool operator<(VIVersion& ver);
	_Public bool operator==(VIVersion& ver);
	_Public operator QString(); 
};

class VICustomVersion :public VIVersion {
	Q_OBJECT;
	_Public ENUM StringPush{
		Front, Middle, Back,
	};
	_Public struct CustomInfo {
		QStringList Info;
		StringPush Push;
		int VersionIndex;
	};
	_Public QList<CustomInfo> InfoList;
	_Public def_init VICustomVersion(VersionList InitVersion, QList<CustomInfo> CustomInfo);
};
