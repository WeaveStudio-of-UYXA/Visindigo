#include "../VIStyleSheetManager.h"
#include "../VIFramework.h"

def_init VIStyleSheetManager11::VIStyleSheetManager11(QWidget* MasterWidget):VIObject(MasterWidget) {
	this->MasterWidget = MasterWidget;
	CurrentStyleSheetName = "";
	PaletteGroup = VIFrame->getPaletteGroup();
	connect(PaletteGroup, &VIPaletteGroup::paletteChanged, this, &VIStyleSheetManager11::onPaletteChanged);
	connect(PaletteGroup, &VIPaletteGroup::colorChanged, this, &VIStyleSheetManager11::onColorChanged);
}