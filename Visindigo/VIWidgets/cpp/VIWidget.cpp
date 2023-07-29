#include "../VIWidget.h"
#include "../VIDynamicStyleSheet.h"

void VIAbstractWidget::setVIDStyleSheet(const QString& name, const QString& styleSheet) {
	if (styleSheet.isEmpty()) {
		return;
	}
	VIDynamicStyleSheetManager::getInstance()->addVIDSS(Self, name, styleSheet);
}

void VIAbstractWidget::applyVIDSS(const QString& name) {
	VIDynamicStyleSheetManager::getInstance()->applyVIDSS(Self, name);
}

QString VIAbstractWidget::getCurrentVIDSSName() {
	return VIDynamicStyleSheetManager::getInstance()->getCurrentVIDSSName(Self);
}

void VIAbstractWidget::refreshVIDStyleSheet() {
	VIDynamicStyleSheetManager::getInstance()->refreshVIDSS(Self);
}