#pragma once
#include "../../Visindigo/VICore/VIPackage.h"
#include "../../Visindigo/VI2DView/VI2DView.h"

class TestScenePack :public VIPackage
{
	Q_OBJECT;
	_Private int JustACount = 1000;
	_Private bool JustAFlag = false;
	_Public VI2DView* w;
	_Public def_init TestScenePack(QObject* parent = nullptr) {
		w = new VI2DView();
		w->show();
	};
	_Public void onFrame() {
		if (!JustAFlag) {
			if (JustACount < 0) {
				w->t->setTextAni("Hello World----------", 300, 1000);
				JustAFlag = true;
			}
			else {
				JustACount--;
			}
		}
	}
};