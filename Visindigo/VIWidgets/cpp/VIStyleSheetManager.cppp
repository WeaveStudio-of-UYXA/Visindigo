#include "../VIStyleSheetManager.h"
#include "../VIFramework.h"

def_init VIStyleSheetManager::VIStyleSheetManager(QWidget* MasterWidget):VIObject(MasterWidget) {
	this->MasterWidget = MasterWidget;
	CurrentStyleSheetName = "";
	PaletteGroup = VIFrame->getPaletteGroup();
	connect(PaletteGroup, &VIPaletteGroup::paletteChanged, this, &VIStyleSheetManager::onPaletteChanged);
	connect(PaletteGroup, &VIPaletteGroup::colorChanged, this, &VIStyleSheetManager::onColorChanged);
}