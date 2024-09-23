#pragma once
#include "VIObject.h"
#include "VIJsonDocument.h"
#include "VILogger.h"

class VIPackagePrivate;
class VIMiCoreAPI VIPackage :public VIObject
{
    Q_OBJECT;
    VI_OBJECT;

    friend class VIPackageManager;
    friend class VIPackagePrivate;

    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName);
	Q_PROPERTY(QString name READ name WRITE setName);
    _Public def_init VIPackage(QString uniqueName, QObject* parent = nullptr);
    _Public QString uniqueName() const;
    _Protected void setUniqueName(const QString& value);
	_Public QString name() const;
	_Protected void setName(const QString& value);
    _Public bool packageContainsClass(const QString& className) const;
    _Public void recordClass(const QMetaObject* metaObject);
	_Public QString internalPath() const;
	_Public QString externalPath() const;
	_Public QString absolutePath() const;
    _Protected virtual void onEnable() PureVirtual;
    _Protected virtual void onDisable() PureVirtual;
	_Public VIJsonDocument* config() const;
	_Public VILogger* logger() const;
    _Private VIPackagePrivate* d;
};

typedef VIPackage* (*VisindigoDllMainPtr)(void);