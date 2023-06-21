#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "../../Visindigo/VIWidgets/VIWidgets.h"

namespace YSPSceneGUIObject 
{
	class SpeedButton :public VIPushButton
	{
		Q_OBJECT;
		VI_WIDGET;
		_Signal void speedChanged(int value);
		_Public QList<double> MagnificationValue = { 0.5,1.0,1.5,2.0,4.0,8.0,16.0};
		_Public QStringList MagnificationText = { "0.5x","1.0x","1.5x","2.0x","4.0x","8.0x","16.0x" };
		_Public enum class Magnification {
			_0_5x = 0, _1_0x = 1, _1_5x = 2, _2_0x = 3, _4_0x = 4, _8_0x = 5, _16_0x = 6
		};
		VI_PrivateProperty(unsigned long long, MagnificationIndex);
		_Public def_init SpeedButton(QWidget* parent = VI_NULLPTR):VIPushButton(parent){
			MagnificationIndex = 1;
			setText(MagnificationText[MagnificationIndex]);
		}
		_Public void changeMagnification(Magnification m) {
			MagnificationIndex = (unsigned long long)m;
			setText(MagnificationText[MagnificationIndex]);
			VIFramework::getBehaviorHostInstance()->setMagnification(MagnificationValue[MagnificationIndex]);
			emit speedChanged(MagnificationValue[MagnificationIndex]);
		}
		_Public void magnificationNext() {
			MagnificationIndex++;
			if (MagnificationIndex >= MagnificationValue.size()) {
				MagnificationIndex = 0;
			}
			setText(MagnificationText[MagnificationIndex]);
			VIFramework::getBehaviorHostInstance()->setMagnification(MagnificationValue[MagnificationIndex]);
			emit speedChanged(MagnificationValue[MagnificationIndex]);
		}
		_Public void magnificationPrevious() {
			if (MagnificationIndex == 0) {
				MagnificationIndex = MagnificationValue.size() - 1;
			}
			else {
				MagnificationIndex--;
			}
			setText(MagnificationText[MagnificationIndex]);
			VIFramework::getBehaviorHostInstance()->setMagnification(MagnificationValue[MagnificationIndex]);
			emit speedChanged(MagnificationValue[MagnificationIndex]);
		}
		_Public void wheelEvent(QWheelEvent* event) {
			if (event->delta() > 0) {
				magnificationNext();
			}
			else {
				magnificationPrevious();
			}
		}
		_Public void mousePressEvent(QMouseEvent* event) {
			if (event->button() == Qt::LeftButton) {
				magnificationNext();
			}
			else if (event->button() == Qt::RightButton) {
				magnificationPrevious();
			}
		}
	};
	class AutoButton :public VIPushButton
	{
		Q_OBJECT;
		VI_WIDGET;
		_Signal void autoChanged(bool a);
		_Private bool Auto = true;
		_Public def_init AutoButton(QWidget* parent = VI_NULLPTR) :VIPushButton(parent) {
			renewVTR();
		}
		_Public virtual void VTR()override {
			if (Auto) {
				setText(VITR("YSP_Player_AutoButton_Auto"));
			}
			else {
				setText(VITR("YSP_Player_AutoButton_Manu"));
			}
		}
		_Public void setAuto(bool a) {
			this->Auto = a;
			VTR();
			emit autoChanged(this->Auto);
		}
	};
	class NextButton :public VIPushButton
	{
		Q_OBJECT;
		VI_WIDGET;
		_Public def_init NextButton(QWidget* parent = VI_NULLPTR) :VIPushButton(parent) {
			renewVTR();
		}
		_Public virtual void VTR()override {
			this->setText(VITR("YSP_Player_NextButton_Text"));
		}
	};
	class GUIStateButton :public VIPushButton
	{
		Q_OBJECT;
		VI_WIDGET;
		_Public def_init GUIStateButton(QWidget* parent = VI_NULLPTR) :VIPushButton(parent) {
			
		}
	};
}

class YSPSceneGUI :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public YSPSceneGUIObject::NextButton* NextButton;
	_Public YSPSceneGUIObject::SpeedButton* SpeedButton;
	_Public YSPSceneGUIObject::GUIStateButton* GUIStateButton;
	_Public YSPSceneGUIObject::AutoButton* AutoButton;
	_Public def_init YSPSceneGUI(QWidget* parent = VI_NULLPTR) :VIWidget(parent) { 
		
	}
};