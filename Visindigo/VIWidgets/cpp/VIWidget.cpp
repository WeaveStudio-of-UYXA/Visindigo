#include "../VIWidget.h"
#include "../VIDynamicStyleSheet.h"

void VIAbstractWidget::setTRHost(VITranslationSubHost* host) {
	VITranslatableObject::setTRHost(host);
	for (auto c = Self->children().begin(); c != Self->children().end(); ++c) {
		if (auto w = dynamic_cast<VIWidget*>(*c)) {
			host->addTranslatableObject(w);
		}
	}
}
void VIAbstractWidget::inheritParentTRHost() {
	if (auto p = dynamic_cast<VIWidget*>(Self->parent())) {
		if (p->getTRHost() != VI_NULL) {
			p->getTRHost()->addTranslatableObject(this);
		}
	}
}
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