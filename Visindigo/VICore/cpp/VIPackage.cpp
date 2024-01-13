#include "../VIPackage.h"
#include "../VICoreFramework.h"

def_init VIPackageMeta::VIPackageMeta() {
	this->setPackageName("UnnamedVIPackage");
	this->TranslationPackageHost = new VITranslationSubHost(this);
	this->PackageConfig = new VIDocument::VIJSON(this);
}
bool VIPackageMeta::initFromMetaJson() {
	QString metaJsonPath = getPackageInternalPath() + "/resource/packageMeta.json";
	if (!QFile::exists(metaJsonPath)) {
		VIConsole::printLine(VIConsole::inErrorStyle(getLogPrefix() + "Package meta file not found."));
		return false;
	}
	VIDocument::VIJSON metaJson = VIDocument::VIJSON(this);
	if (!metaJson.loadSettings(metaJsonPath)) {
		VIConsole::printLine(VIConsole::inErrorStyle(getLogPrefix() + "Package meta file load failed."));
		return false;
	}
	QString packageName = metaJson["Name"].toString();
	if (packageName!=getPackageName()) {
		VIConsole::printLine(VIConsole::inErrorStyle(getLogPrefix() + "Package name not match."));
		return false;
	}
	QString packageUniqueName = metaJson["UniqueName"].toString();
	if (packageUniqueName.isEmpty()) { return false; }
	else { setUniqueName(packageUniqueName); }
	VIVersion packageVersion = VIVersion::fromString(metaJson["Version"].toString());
	setPackageVersion(VIVersion::fromString(metaJson["Version"].toString()));
	setAuthor(metaJson["Author"].toStringList());
	setDescription(metaJson["Description"].toString());
	setLicense(metaJson["License"].toString());
	setURL(metaJson["URL"].toString());
	QStringList dependencyKeys = metaJson.getKeysOf("Dependence");
	for (auto i : dependencyKeys) {
		VIPackageUniqueName depName = metaJson["Dependence."+i+".UniqueName"].toString();
		if (depName.isEmpty()) { continue; }
		VIVersion depVersion = VIVersion::fromString(metaJson["Dependence." + i + ".Version"].toString());
		VIPackageDependency dep(depName, depVersion);
		PackageDependencies.insert(depName, dep);
	}
	return true;
}
QString VIPackageMeta::getPackageRootPath() {
	if (PackageRootPath == "") {
		return VIPathInfo::getProgramPath() + "/ProgramData/" + PackageName;
	}
	else {
		return PackageRootPath + "/"+ PackageName;
	}
}
QString VIPackageMeta::TR(const QString& key) {
	return TranslationPackageHost->getTranslation(key);
}
void VIPackageMeta::addTranslationFileName(Visindigo::Language langType, const QString& key, bool inRC) {
	TranslationPackageHost->addTranslationFileName(langType, key, inRC);
}
void VIPackageMeta::setDefaultLanguage(Visindigo::Language langType) {
	TranslationPackageHost->setDefaultLanguage(langType);
}
void VIPackageMeta::initTranslation() {
	TranslationPackageHost->onInit();
}
void VIPackageMeta::addTranslatableObject(VITranslatableObject* obj) {
	TranslationPackageHost->addTranslatableObject(obj);
}
void VIPackageMeta::setPackageName(const QString& name) {
	PackageName = name;
	setObjectName(name);
}
QVariant VIPackageMeta::getConfig(const QString& key) {
	return PackageConfig->getValueOf(key);
}
void VIPackageMeta::setConfig(const QString& key, const QVariant& value) {
	PackageConfig->setValueOf(key, value);
}
void VIPackageMeta::saveConfig() {
	PackageConfig->saveSettings();
}
void VIPackageMeta::initConfig() {
	PackageConfig->loadDefault(getPackageInternalPath() + "/resource/config.json");
	PackageConfig->loadSettings(getPackageRootPath() + "/config.json", true);
	PackageConfig->setObjectName(PackageName);
}
def_del VIPackageMeta::~VIPackageMeta() {
	delete TranslationPackageHost;
	PackageConfig->saveSettings();
	delete PackageConfig;
}
/*
VIPackage
*/
def_init VIPackage::VIPackage() {
	PackageMeta = VI_NULL;
}
VIPackageMeta* VIPackage::getPackageMeta() {
	return PackageMeta;
}
void VIPackage::setPackageMeta(VIPackageMeta* info) {
	if (info != VI_NULL) {
		if (PackageMeta != VI_NULL) {
			return;
		}
		PackageMeta = info;
		setObjectName(info->getPackageName());
		VIConsole::printLine(VIConsole::inSuccessStyle(getLogPrefix() + "Package Meta loaded."));
	}
}
def_del VIPackage::~VIPackage() {
	if (PackageMeta != VI_NULL) {
		delete PackageMeta;
	}
}

def_init VIDllPackageContainer::VIDllPackageContainer(const QString& dllpath) {
	DllPath = dllpath;
	Dll = new QLibrary(dllpath);
}
Visindigo::LoadState VIDllPackageContainer::load() {
	if (!Dll->load()) {
		return Visindigo::LoadState::LoadFailed;
	}
	__VisindigoDllMain main = (__VisindigoDllMain)Dll->resolve(VisindigoDllEntryPointName);
	if (main == VI_NULL) {
		return Visindigo::LoadState::EntryFailed;
	}
	QString packageRoot = DllPath.section("/", 0, -2);
	Package = main();
	if (Package == VI_NULL) {
		return Visindigo::LoadState::InitFailed;
	}
	try {
		Package->PackageMeta->PackageRootPath = packageRoot;
		VICoreFramework::getCoreInstance()->loadPackage(Package);
	}
	catch (...) {
		return Visindigo::LoadState::InitFailed;
	}
	return Visindigo::LoadState::Succeed;
}
def_del VIDllPackageContainer::~VIDllPackageContainer() {
	if (Package != VI_NULL) {
		delete Package;
	}
	if (Dll != VI_NULL) {
		Dll->unload();
		delete Dll;
	}
}