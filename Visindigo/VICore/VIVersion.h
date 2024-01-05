#pragma once
#include "VIObject.h"
#include "private/VIAutoVersion.h"

class VIPublicAPI VIVersion :public VIObject {
	Q_OBJECT;
	VI_OBJECT;
	_Public enum Branch {
		Unknown = -1,
		Develop = 0,
		Alpha = 5000,
		Beta = 10000,
		Preview = 15000,
		Release = 20000,
	};
	_Private quint32 MAJOR;
	_Private quint32 MINOR;
	_Private quint32 PATCH;
	_Private quint32 BUILD;
	_Private Branch BRANCH;
	_Public static Branch inDevelop(quint16 branch) { return (Branch)(Develop + branch); }
	_Public static Branch inAlpha(quint16 branch) { return (Branch)(Alpha + branch); }
	_Public static Branch inBeta(quint16 branch) { return (Branch)(Beta + branch); }
	_Public static Branch inPreview(quint16 branch) { return (Branch)(Preview + branch); }
	_Public static Branch inRelease(quint16 branch) { return (Branch)(Release + branch); }
	_Public static Branch inWhichBranch(quint32 version) {
		if (version >= Release) { return Release; }
		if (version >= Preview) { return Preview; }
		if (version >= Beta) { return Beta; }
		if (version >= Alpha) { return Alpha; }
		if (version >= Develop) { return Develop; }
		return Unknown;
	}
	_Public def_init VIVersion(quint32 major, quint32 minor, quint32 patch, quint32 build = 0, Branch branch = Branch::Unknown) {
		MAJOR = major;
		MINOR = minor;
		PATCH = patch;
		BUILD = build;
		BRANCH = branch;
	}
	_Public QString getFullVersionString() {
		Branch branch = inWhichBranch(BRANCH);
		QString branchStr = "";
		switch (branch) {
		case Develop:
			branchStr = "Develop" + QString::number(BRANCH - Develop);
			break;
		case Alpha:
			branchStr = "Alpha" + QString::number(BRANCH - Alpha);
			break;
		case Beta:
			branchStr = "Beta" + QString::number(BRANCH - Beta);
			break;
		case Preview:
			branchStr = "Preview" + QString::number(BRANCH - Preview);
			break;
		case Release:
			branchStr = "Release" + QString::number(BRANCH - Release);
			break;
		}
		return QString::number(MAJOR) + "." + QString::number(MINOR) + "." + QString::number(PATCH) + "_" + branchStr + "(" + QString::number(BUILD) + ")";
	}
	_Public bool isSameVersion(const VIVersion& tar) {
		return tar.MAJOR == MAJOR || tar.MINOR == MINOR || tar.PATCH == PATCH || tar.BUILD == BUILD || tar.BRANCH == BRANCH;
	}
	_Public bool operator=(const VIVersion& tar) {
		return isSameVersion(tar);
	}
	_Public bool isNewerThan(const VIVersion& tar) {
		if (MAJOR > tar.MAJOR) { return true; }
		if (MAJOR < tar.MAJOR) { return false; }
		if (MINOR > tar.MINOR) { return true; }
		if (MINOR < tar.MINOR) { return false; }
		if (PATCH > tar.PATCH) { return true; }
		if (PATCH < tar.PATCH) { return false; }
		if (BUILD > tar.BUILD) { return true; }
		if (BUILD < tar.BUILD) { return false; }
		if (BRANCH > tar.BRANCH) { return true; }
		if (BRANCH < tar.BRANCH) { return false; }
		return false;
	}
	_Public bool operator>(const VIVersion& tar) {
		return isNewerThan(tar);
	} 
	_Public bool isOlderThan(const VIVersion& tar) {
		if (MAJOR < tar.MAJOR) { return true; }
		if (MAJOR > tar.MAJOR) { return false; }
		if (MINOR < tar.MINOR) { return true; }
		if (MINOR > tar.MINOR) { return false; }
		if (PATCH < tar.PATCH) { return true; }
		if (PATCH > tar.PATCH) { return false; }
		if (BUILD < tar.BUILD) { return true; }
		if (BUILD > tar.BUILD) { return false; }
		if (BRANCH < tar.BRANCH) { return true; }
		if (BRANCH > tar.BRANCH) { return false; }
		return false;
	}
	_Public bool operator<(const VIVersion& tar) {
		return isOlderThan(tar);
	}

	//The functions below are just from old version of VIVersion class
	_Public static const QString getVisindigoVersion() { return QString::number(VI_VERSION_MAJOR) + "." + QString::number(VI_VERSION_MINOR) + "." + QString::number(VI_VERSION_PATCH) + "." + QString::number(VI_VERSION_BUILD); }
	_Public static const QString getVisindigoNickname() { return QString(VI_VERSION_NICKNAME); }
	_Public static const QString getVisindigoCompileTime() { return QString(VI_VERSION_BUILD_DATE) + " " + QString(VI_VERSION_BUILD_TIME); }
	_Public static const QString getVisindigoQtVersion() { return QString::number(QT_VERSION_MAJOR) + "." + QString::number(QT_VERSION_MINOR); }
};