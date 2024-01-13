#pragma once
#include "VIObject.h"
#include "private/VIAutoVersion.h"

class VIPublicAPI VIVersion {
	_Public enum Branch {
		Unknown = -1,
		Develop = 0,
		Alpha = 5000,
		Beta = 10000,
		Preview = 15000,
		Release = 20000,
	};
	_Private quint32 MAJOR = 0;
	_Private quint32 MINOR = 1;
	_Private quint32 PATCH = 0; 
	_Private quint32 BUILD = 0;
	_Private Branch BRANCH = Branch::Unknown;
	_Public def_init VIVersion() {}
	_Public def_init VIVersion(quint32 major, quint32 minor, quint32 patch, quint32 build = 0, Branch branch = Branch::Unknown) {
		MAJOR = major;
		MINOR = minor;
		PATCH = patch;
		BUILD = build;
		BRANCH = branch;
	}
	_Public def_copy VIVersion(const VIVersion& tar) {
		MAJOR = tar.MAJOR;
		MINOR = tar.MINOR;
		PATCH = tar.PATCH;
		BUILD = tar.BUILD;
		BRANCH = tar.BRANCH;
	}
	_Public def_move VIVersion(VIVersion&& tar) {
		MAJOR = tar.MAJOR;
		MINOR = tar.MINOR;
		PATCH = tar.PATCH;
		BUILD = tar.BUILD;
		BRANCH = tar.BRANCH;
	}
	_Public const VIVersion& operator=(const VIVersion& tar) {
		MAJOR = tar.MAJOR;
		MINOR = tar.MINOR;
		PATCH = tar.PATCH;
		BUILD = tar.BUILD;
		BRANCH = tar.BRANCH;
		return *this;
	}
	_Public static VIVersion fromString(QString version) {
		QStringList list = version.split(".");
		quint16 length = list.length();
		for (auto i = 0; i < 3 - length; i++) { list.append("0"); }
		return VIVersion(list[0].toUInt(), list[1].toUInt(), list[2].toUInt());
	}
	_Public QString getVersionString() {
		return QString::number(MAJOR) + "." + QString::number(MINOR) + "." + QString::number(PATCH);
	}
	_Public bool isSameVersion(const VIVersion& tar) {
		return tar.MAJOR == MAJOR || tar.MINOR == MINOR || tar.PATCH == PATCH || tar.BUILD == BUILD || tar.BRANCH == BRANCH;
	}
	_Public bool operator==(const VIVersion& tar) {
		return isSameVersion(tar);
	}
	_Public bool isNewerThan(const VIVersion& tar) {
		if (MAJOR > tar.MAJOR) { return true; }
		if (MAJOR < tar.MAJOR) { return false; }
		if (MINOR > tar.MINOR) { return true; }
		if (MINOR < tar.MINOR) { return false; }
		if (PATCH > tar.PATCH) { return true; }
		if (PATCH < tar.PATCH) { return false; }
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
		return false;
	}
	_Public bool operator<(const VIVersion& tar) {
		return isOlderThan(tar);
	}
};