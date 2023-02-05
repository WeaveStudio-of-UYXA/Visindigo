#include "VIVersion.h"
 
def_init VIVersion::VIVersion(QList<int> InitVersion) {
	Version = InitVersion;
}
int VIVersion::getVersionLength() {
	return Version.length();
}
VersionNum VIVersion::getVersionNum(int index) {
	return Version[index];
}
bool VIVersion::operator>(VIVersion& ver) {
	int Length = this->getVersionLength();
	if (ver.getVersionLength() != Length) { return false; }
	else {
		for (int i = 0; i < Length; i++) {
			if (Version[i] > ver.Version[i]) {
				return true;
			}
			if (Version[i] < ver.Version[i]) {
				return false;
			}
		}
		return false;
	}
}
bool VIVersion::operator<(VIVersion& ver) {
	int Length = this->getVersionLength();
	if (ver.getVersionLength() != Length) { return false; }
	else {
		for (int i = 0; i < Length; i ++) {
			if (Version[i] > ver.Version[i]) {
				return false;
			}
			if (Version[i] < ver.Version[i]) {
				return true;
			}
		}
		return false;
	}
}
bool VIVersion::operator==(VIVersion& ver) {
	int Length = this->getVersionLength();
	if (ver.getVersionLength() != Length) { return false; }
	else {
		for (int i = 0; i < Length; i++) {
			if (Version[i] != ver.Version[i]) {
				return false;
			}
		}
		return true;
	}
}
VIVersion::operator QString() {
	QString result = "";
	for (auto i = Version.begin(); i != Version.end(); i++) {
		result.append(QString::number(*i));
		if (i != Version.end() - 1) {
			result.append(".");
		}
	}
	return result;
}