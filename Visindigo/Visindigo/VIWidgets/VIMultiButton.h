//此文件中的杂按钮源于CommonEdit
#pragma once
#include "../VICore/VICore.h"
#include "VIWidget.h"

class VIMultiButtonGroup;
class VIMultiButton :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	friend class VIMultiButtonGroup;
	_Signal void pressed();
	_Signal void clicked();
	_Signal void selected(int index);
	_Private QLabel* IconLabel;
	_Private QLabel* TextLabel;
	_Private QLabel* SubTextLabel;
	VI_PrivateFlag(EnableSubText);
	VI_PrivateFlag(Shrinked);
	VI_Property(int, ShrinkWidth);
	VI_Property(int, Spacing);
	VI_ProtectedFlag(InButtonGroup);
	VI_ProtectedFlag(Selected);
	VI_ProtectedProperty(int, ButtonGroupIndex);
	_Public def_init VIMultiButton(QWidget* parent = VI_NULLPTR, QString text = "", bool enableSubText = true) :VIWidget(parent) {
		TextLabel = new QLabel(text, this);
		TextLabel->setObjectName("TextLabel");
		SubTextLabel = VI_NULLPTR;
		if (enableSubText) { SubTextLabel = new QLabel("", this); SubTextLabel->setObjectName("SubTextLabel"); }
		EnableSubText = enableSubText;
		IconLabel = new QLabel(this);
		IconLabel->setObjectName("IconLabel");
		ShrinkWidth = width() / 3;
		Shrinked = false;
		Spacing = 5;
		ButtonGroupIndex = -1;
		InButtonGroup = false;
		Selected = false;
	}
	_Public void resizeEvent(QResizeEvent* event) {
		if (width() < ShrinkWidth) {
			onShrink();
		}
		else {
			onExpand();
		}
		if (Shrinked) {
			IconLabel->setGeometry(Spacing, (width()-height()+Spacing*2)/2, height() - Spacing*2, height() - Spacing*2);
		}
		else {
			IconLabel->setGeometry(Spacing, Spacing, height() - Spacing*2, height() - Spacing*2);
			if (EnableSubText) { 
				TextLabel->setGeometry(height(), Spacing, width() - height() - Spacing * 2, (height() - Spacing * 2) * 3 / 5);
				SubTextLabel->setGeometry(height(), (height()-Spacing*2) * 3 / 5 + Spacing, width() - height() - Spacing*2, (height()-Spacing*2) * 2 / 5); 
			}
			else {
				TextLabel->setGeometry(height(), Spacing, width() - height() - Spacing * 2, height() - Spacing * 2);
			}
		}
	}
	_Public void show() {
		VIWidget::show();
	}
	_Private void onShrink() {
		if (Shrinked) return;
		Shrinked = true;
		if (EnableSubText) { SubTextLabel->hide();}
		TextLabel->hide();
	}
	_Private void onExpand() {
		if (!Shrinked) return;
		Shrinked = false;
		if (EnableSubText) { SubTextLabel->show();}
		TextLabel->show();
	}
	_Public void setNormalStyleSheet(QString ss) {
		StyleSheetManager->addStyleSheet("Normal", ss);
	}
	_Public void setHoverStyleSheet(QString ss) {
		StyleSheetManager->addStyleSheet("Hover", ss);
	}
	_Public void setPressStyleSheet(QString ss) {
		StyleSheetManager->addStyleSheet("Press", ss);
	}
	_Public void select() {
		Selected = true;
		StyleSheetManager->applyStyleSheet("Press");
	}
	_Public void setIcon(QString icon) {
		IconLabel->setPixmap(QPixmap(icon));
	}
	_Public void setText(QString text) {
		this->setObjectName(text);
		TextLabel->setText(text);
	}
	_Public void setSubText(QString text) {
		SubTextLabel->setText(text);
	}
	_Public void enterEvent(QEvent* event) {
		if (!Selected) { StyleSheetManager->applyStyleSheet("Hover"); }
	}
	_Public void leaveEvent(QEvent* event) {
		if (!Selected) { StyleSheetManager->applyStyleSheet("Normal"); }
	}
	_Public void mousePressEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
			StyleSheetManager->applyStyleSheet("Press");
			emit pressed();
		}
	}
	_Public void mouseReleaseEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
			StyleSheetManager->applyStyleSheet("Press");
			Selected = true;
			emit clicked();
			emit selected(ButtonGroupIndex);
		}
	}
	_Protected void unSelect() {
		Selected = false;
		StyleSheetManager->applyStyleSheet("Normal");
	}
};
class private_VIMultiButtonAnimationBehavior :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QWidget* Target;
	_Private int targetX, targetY;
	_Private int rawH, rawW;
	_Private int rawX, rawY;
	_Private float maxExpandPercent = 0.5;
	_Private bool PositiveDirection;
	_Public Qt::Orientation Direction;
	_Public def_init private_VIMultiButtonAnimationBehavior(QWidget* parent = VI_NULLPTR) :VIAnimationBehavior(parent) {
		Target = parent;
	}
	_Public void setMoveTo(int X, int Y, Qt::Orientation orientation) {
		targetX = X;
		targetY = Y;
		Direction = orientation;
	}
	_Public void setMaxExpandPercent(float p) {
		maxExpandPercent = p;
	}
	_Public void onActive() override {
		rawH = Target->height();
		rawW = Target->width();
		rawX = Target->x();
		rawY = Target->y();
		if (Direction == Qt::Orientation::Horizontal) {
			PositiveDirection = targetX > rawX;
		}
		else {
			PositiveDirection = targetY > rawY;
		}
	}
	_Public void onTick() override {
		Target->move((float)rawX+(float)(targetX-rawX)*VIMath::sin_0_1(Duration->getPercent()), 
			(float)rawY+(float)(targetY-rawY)*VIMath::sin_0_1(Duration->getPercent()));
		Target->resize(rawW, rawH + rawH * maxExpandPercent * VIMath::sin_0_1_0(Duration->getPercent()));
	}
	_Public void onPassive() override {
		Target->setGeometry(targetX, targetY, rawW, rawH);
	}
};
class private_VIMultiButtonAnimationLabel :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Public private_VIMultiButtonAnimationBehavior* Behavior;
	_Public def_init private_VIMultiButtonAnimationLabel(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		this->setObjectName("VIMultiButtonAnimationLabel");
		Behavior = new private_VIMultiButtonAnimationBehavior(this);
		this->StyleSheetManager->addStyleSheet("default",
			"private_VIMultiButtonAnimationLabel{background-color:CLR__SystemThemeColor__CLR;border:0px solid white;border-radius:2px;}");
		this->StyleSheetManager->applyStyleSheet("default");
	
	}
	_Public void setStyleSheetPalette(VIStyleSheetPalette* palette) override{
		consoleLog("Palette setted");
		VIWidget::setStyleSheetPalette(palette);
		connect(StyleSheetManager->Palette, &VIStyleSheetPalette::PaletteChanged, this->StyleSheetManager, &VIStyleSheetManager::refreshStyleSheet);
		this->StyleSheetManager->applyStyleSheet("default");
	}
};
class VIMultiButtonGroup :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void selected(int index);
	_Private QList<VIMultiButton*> Buttons;
	_Private QLayout* Layout;
	VI_PrivateProperty(int, SelectedIndex);
	VI_Property(Qt::Orientation, Direction);
	_Private int Spacing = 5;
	_Private int AnimationLabelWidth = 4;
	_Private private_VIMultiButtonAnimationLabel* AnimationLabel;
	_Public def_init VIMultiButtonGroup(Qt::Orientation orientation, QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		Direction = orientation;
		if (Direction == Qt::Orientation::Horizontal) {
			Layout = new QHBoxLayout(this);
		}
		else {
			Layout = new QVBoxLayout(this);
		}
		AnimationLabel = new private_VIMultiButtonAnimationLabel(this);
		SelectedIndex = -1;
	}
	_Public void addButton(VIMultiButton* button) {
		Buttons.append(button);
		button->InButtonGroup = true;
		button->ButtonGroupIndex = Buttons.size() - 1;
		connect(button, &VIMultiButton::selected, this, &VIMultiButtonGroup::onSelected);
		Layout->addWidget(button);
		AnimationLabel->raise();
	}
	_Public void removeButton(int index) {
		Buttons.removeAt(index);
		Layout->removeWidget(Buttons[index]);
		for (int i = index; i < Buttons.size(); i++) {
			Buttons[i]->ButtonGroupIndex--;
		}
	}
	_Public void removeButton(VIMultiButton* button) {
		removeButton(button->ButtonGroupIndex);
	}
	_Public void setShrinkWidth(int width) {
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->ShrinkWidth = width;
		}
	}
	_Public void setSpacing(int spacing) {
		Spacing = spacing;
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->Spacing = spacing;
		}
		resizeEvent(VI_NULLPTR);
	}
	_Public int selectFirst() {
		if (Buttons.size() == 0) { return -1; }
		Buttons[0]->select();
		SelectedIndex = 0;
		AnimationLabel->move(Buttons[SelectedIndex]->x()+(Spacing - AnimationLabelWidth) / 2, Buttons[SelectedIndex]->y() + Spacing);
		AnimationLabel->resize(AnimationLabelWidth, Buttons[SelectedIndex]->height() - Spacing * 2);
		return 0;
	}
	_Public void setNormalStyleSheet(const QString &styleSheet) {
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->setNormalStyleSheet(styleSheet);
			Buttons[i]->setStyleSheet(styleSheet);
		}
	}
	_Public void setPressStyleSheet(const QString &styleSheet) {
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->setPressStyleSheet(styleSheet);
		}
	}
	_Public void setHoverStyleSheet(const QString &styleSheet) {
		for (int i = 0; i < Buttons.size(); i++) {
			Buttons[i]->setHoverStyleSheet(styleSheet);
		}
	}
	_Public void resizeEvent(QResizeEvent* event) {
		if (SelectedIndex == -1) { return; }
		AnimationLabel->move(Buttons[SelectedIndex]->x() + (Spacing - AnimationLabelWidth) / 2, Buttons[SelectedIndex]->y() + Spacing);
		AnimationLabel->resize(AnimationLabelWidth, Buttons[SelectedIndex]->height() - Spacing * 2);
		qDebug()<<AnimationLabel->width()<<AnimationLabel->height();
	}
	_Public VIMultiButton* spawnButton(QString text, QString icon = "", QString subText = "") {
		VIMultiButton* button = new VIMultiButton(this, text, subText!="");
		if (icon != "") { button->setIcon(icon); }
		if (subText != "") { button->setSubText(subText); }
		addButton(button);
		AnimationLabel->raise();
		return button;
	}
	private slots: void onSelected(int index) {
		SelectedIndex = index;
		for (int i = 0; i < Buttons.size(); i++) {
			if (i != index) {
				Buttons[i]->unSelect();
			}
		}
		AnimationLabel->Behavior->setDuration(300);
		AnimationLabel->Behavior->setMoveTo(AnimationLabel->x(), Buttons[index]->y()+ Spacing, Direction);
		AnimationLabel->Behavior->active();
		emit selected(index);
	}
};