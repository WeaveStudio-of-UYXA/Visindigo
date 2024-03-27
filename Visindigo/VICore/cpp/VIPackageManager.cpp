#include "../VIPackageManager.h"
#include "../VIFileTools.h"
#include "../VIVersion.h"
#include "../VIPackage.h"
/*
VIPackageManager
*/

VI_Singleton_StaticInit(VIPackageManager);

def_init VIPackageManager::VIPackageManager(VISuper* parent) :VIObject(parent) {
	VI_Singleton_Init;
}

bool VIPackageManager::loadPackage(VIPackage* package) {
	if (package == nullptr) return false;
	if (Packages.keys().contains(package->getPackageMeta()->getUniqueName())) {
		return false;
	}
	Packages.insert(package->getPackageMeta()->getUniqueName(), package);
	package->onEnable();
	return true;
}

bool VIPackageManager::loadPluginPackages(QString rootPath) {
	QDir dir(rootPath);
	if (!dir.exists()) return false;
	QStringList metaJson = VIFileTools::filesFilter(rootPath, QStringList({ "*.json" }));
	QMap<VIPackageUniqueName, quint32> dependenceCount;
	QMap<VIPackageUniqueName, QString> entryPath;
	QMap<VIPackageUniqueName, VIVersion> packageVersion;
	for (auto i : metaJson) {
		VIDocument::VIJSON doc;
		if (!doc.loadSettings(i)) { continue; }
		QStringList index = doc.getKeysOf("Dependence");
		VIPackageUniqueName name = doc["UniqueName"].toString();
		VIVersion version = VIVersion::fromString(doc["Version"].toString());
		if (entryPath.contains(name)) {
			if (packageVersion[name] < version) {
				entryPath[name] = i.left(i.lastIndexOf("."))+".dll";
				packageVersion[name] = version;
			}
			else {
				continue;
			}
		}
		else {
			entryPath.insert(name, i.left(i.lastIndexOf(".")) + ".dll");
			packageVersion.insert(name, version);
		}
		for (auto j : index) {
			VIPackageUniqueName name = doc["Dependence." + j + ".UniqueName"].toString();
			if (dependenceCount.contains(name)) {
				dependenceCount[name]++;
			}
			else {
				dependenceCount.insert(name, 1);
			}
		}
	}
	for (auto i : dependenceCount.keys()) {
		if (!entryPath.keys().contains(i)) {
			consoleLog(VIConsole::inWarningStyle("Package " + i + " not found!"));
			//may auto download
		}
	}
	for (auto i : entryPath.keys()) {
		if (!dependenceCount.keys().contains(i)) {
			consoleLog(VIConsole::inWarningStyle("Package " + i + " not used!"));
		}
	}
	QVector<QPair<VIPackageUniqueName, quint32>> dependenceCountVector;
	for (auto i : dependenceCount.keys()) {
		dependenceCountVector.push_back(QPair<VIPackageUniqueName, quint32>(i, dependenceCount[i]));
	}
	qSort(dependenceCountVector.begin(), dependenceCountVector.end(), 
		[](QPair<VIPackageUniqueName, quint32> a, QPair<VIPackageUniqueName, quint32> b) {
			return a.second > b.second;
		});
	for (auto i : dependenceCountVector) {
		VIDllPackageContainer* container = new VIDllPackageContainer(entryPath[i.first]);
		container->load();
		DllPackages.insert(i.first, container);
	}

}

bool VIPackageManager::startAll() {
	for (auto i : Packages.keys()) {
		try {
			Packages[i]->start(Visindigo::T20);
		}
		catch (...) {
			return false;
		}
	}
	return true;
}

bool VIPackageManager::disableAll() {
	for (auto i : Packages.keys()) {
		Packages[i]->onDisable(); // may need exception handle
	}
	return true;
}

bool VIPackageManager::reloadAll() {
	for (auto i : Packages.keys()) {
		Packages[i]->onReload(); // S.F
	}
	return true;
}

bool VIPackageManager::reInitAll() {
	PASS; // need implyment
	return true;
}

bool VIPackageManager::disablePackage(VIPackageUniqueName packageName) {
	if (Packages.contains(packageName)) {
		Packages[packageName]->onDisable();
	}
	return true;
}



VIPackage* VIPackageManager::getPackage(VIPackageUniqueName name) {
	if (Packages.keys().contains(name)) {
		return Packages[name];
	}
	else {
		return nullptr;
	}
}

QList<VIPackageUniqueName> VIPackageManager::getPackageNames() {
	return Packages.keys();
}