#include "../VIDynamicStyleSheet.h"
#include "../VIPalette.h"

VI_Singleton_StaticInit(VIDynamicStyleSheetManager);

QStringList VIDynamicStyleSheet::hasDynamicSize(const QString& ss) {
	int index_auto = 0;
	int index_pr = 0;
	QStringList rtn;
	while (true) {
		index_auto = ss.indexOf("APR_", index_auto);
		index_pr = ss.indexOf("_PR", index_pr);
		if (index_auto == -1 || index_pr == -1) {
			break;
		}
		QString colorName = ss.mid(index_auto + 4, index_pr - index_auto - 4);
		rtn << colorName;
		index_auto = index_pr;
		index_pr += 3;
	}
	return rtn;
}

QStringList VIDynamicStyleSheet::hasDynamicColor(const QString& ss) {
	int index_auto = 0;
	int index_clr = 0;
	QStringList rtn;
	while (true) {
		index_auto = ss.indexOf("ACLR_", index_auto);
		index_clr = ss.indexOf("_CLR", index_clr);
		if (index_auto == -1 || index_clr == -1) {
			break;
		}
		QString colorName = ss.mid(index_auto + 5, index_clr - index_auto - 5);
		rtn << colorName;
		index_auto = index_clr;
		index_clr += 4;
	}
	return rtn;
}
/*
VIDynamicStyleSheetContainer
*/
def_init VIDynamicStyleSheetContainer::VIDynamicStyleSheetContainer() {
	this->MasterWidget = VI_NULL;
	this->QSS = "";
	DynamicSizeList = QStringList();
	HasDynamicSize = false;
	DynamicColorList = QStringList();
	HasDynamicColor = false;
}
def_init VIDynamicStyleSheetContainer::VIDynamicStyleSheetContainer(QWidget* masterWidget, const QString& qss) {
	this->MasterWidget = masterWidget;
	setVIDSS(qss);
}

def_copy VIDynamicStyleSheetContainer::VIDynamicStyleSheetContainer(const VIDynamicStyleSheetContainer& other) {
	this->MasterWidget = other.MasterWidget;
	this->QSS = other.QSS;
	this->DynamicSizeList = other.DynamicSizeList;
	this->HasDynamicSize = other.HasDynamicSize;
	this->DynamicColorList = other.DynamicColorList;
	this->HasDynamicColor = other.HasDynamicColor;
}

VIDynamicStyleSheetContainer& VIDynamicStyleSheetContainer::operator=(const VIDynamicStyleSheetContainer& other) {
	this->MasterWidget = other.MasterWidget;
	this->QSS = other.QSS;
	this->DynamicSizeList = other.DynamicSizeList;
	this->HasDynamicSize = other.HasDynamicSize;
	this->DynamicColorList = other.DynamicColorList;
	this->HasDynamicColor = other.HasDynamicColor;
	return *this;
}

def_move VIDynamicStyleSheetContainer::VIDynamicStyleSheetContainer(VIDynamicStyleSheetContainer&& other) {
	this->MasterWidget = other.MasterWidget;
	this->QSS = other.QSS;
	this->DynamicSizeList = other.DynamicSizeList;
	this->HasDynamicSize = other.HasDynamicSize;
	this->DynamicColorList = other.DynamicColorList;
	this->HasDynamicColor = other.HasDynamicColor;
}

void VIDynamicStyleSheetContainer::applyVIDSS() {
	QString vidss = QSS;
	if (HasDynamicSize) {
		applyDynamicSize(&vidss);
	}
	if (HasDynamicColor) {
		applyDynamicColor(&vidss);
	}
	MasterWidget->setStyleSheet(vidss);
}

void VIDynamicStyleSheetContainer::applyDynamicSize(QString* ss) {
	for (auto& name : DynamicSizeList) {
		float value = QString(name).toFloat() / 100;
		value *= MasterWidget->height();
		QString px = QString::number((int)value) + "px";
		ss->replace("APR_" + name + "_PR", px);
	}
}

void VIDynamicStyleSheetContainer::applyDynamicColor(QString* ss) {
	for (auto& name : DynamicColorList) {
		QString color = VIColorTools::toRGBAString(VIPaletteGroup::getInstance()->getColor(name));
		ss->replace("ACLR_" + name + "_CLR", color);
	}
}

void VIDynamicStyleSheetContainer::setVIDSS(const QString& qss) {
	this->QSS = qss;
	DynamicSizeList = VIDynamicStyleSheet::hasDynamicSize(QSS);
	HasDynamicSize = !DynamicSizeList.isEmpty();
	DynamicColorList = VIDynamicStyleSheet::hasDynamicColor(QSS);
	HasDynamicColor = !DynamicColorList.isEmpty();
}

void VIDynamicStyleSheetContainer::setMasterWidget(QWidget* masterWidget) {
	this->MasterWidget = masterWidget;
}
/*
VIDynamicStyleSheetManager
*/
// Notice: VIDynamicStyleSheetManager 还未连接到VIPaletteGroup
def_init VIDynamicStyleSheetManager::VIDynamicStyleSheetManager(VISuper* parent) :VIObject(parent) {
	VI_Singleton_Init;
}

void VIDynamicStyleSheetManager::addVIDSS(QWidget* masterWidget, const QString& name, const QString& qss) {
	if (masterWidget == VI_NULL) { return; }
	VIDynamicStyleSheetContainer container(masterWidget, qss);
	if (!VIDSSContainerHash.contains(masterWidget)) {
		VIDSSContainerHash.insert(masterWidget, VIDynamicStyleSheetContainerHash());
		VIDSSContainerHash[masterWidget].insert(name, container);
	}
	else {
		if (VIDSSContainerHash[masterWidget].contains(name)) {
			VIDSSContainerHash[masterWidget][name] = container;
			if (VIDSSNameHash.contains(masterWidget)) {
				if (VIDSSNameHash[masterWidget] == name) {
					container.applyVIDSS();
				}
			}
		}
		else {
			VIDSSContainerHash[masterWidget].insert(name, container);
		}
	}
}

void VIDynamicStyleSheetManager::applyVIDSS(QWidget* masterWidget, const QString& name) {
	if (VIDSSContainerHash.contains(masterWidget) && VIDSSContainerHash[masterWidget].contains(name)) {
		VIDSSNameHash[masterWidget] = name;
		VIDSSContainerHash[masterWidget][name].applyVIDSS();
	}
}

QString VIDynamicStyleSheetManager::getCurrentVIDSSName(QWidget* masterWidget) {
	if (VIDSSNameHash.contains(masterWidget)) {
		return VIDSSNameHash[masterWidget];
	}
	else {
		return "";
	}
}

void VIDynamicStyleSheetManager::refreshVIDSS() {
	for (auto& masterWidget : VIDSSContainerHash.keys()) {
		if (VIDSSNameHash.contains(masterWidget)) {
			VIDSSContainerHash[masterWidget][VIDSSNameHash[masterWidget]].applyVIDSS();
		}
	}
}

void VIDynamicStyleSheetManager::refreshVIDSS(QWidget* masterWidget) {
	if (VIDSSNameHash.contains(masterWidget)) {
		VIDSSContainerHash[masterWidget][VIDSSNameHash[masterWidget]].applyVIDSS();
	}
}