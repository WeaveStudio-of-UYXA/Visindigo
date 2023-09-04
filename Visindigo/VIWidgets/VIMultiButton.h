//此文件中的杂按钮源于CommonEdit
#pragma once
#include "../VICore/VICore.h"
#include "VIPalette.h"
#include "VIWidget.h"

class VIPublicAPI VIMultiButtonGroup;
class VIPublicAPI VIMultiButton :public VIWidget
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
			IconLabel->setGeometry(Spacing, (width() - height() + Spacing * 2) / 2, height() - Spacing * 2, height() - Spacing * 2);
		}
		else {
			IconLabel->setGeometry(Spacing, Spacing, height() - Spacing * 2, height() - Spacing * 2);
			if (EnableSubText) {
				TextLabel->setGeometry(height(), Spacing, width() - height() - Spacing * 2, (height() - Spacing * 2) * 3 / 5);
				SubTextLabel->setGeometry(height(), (height() - Spacing * 2) * 3 / 5 + Spacing, width() - height() - Spacing * 2, (height() - Spacing * 2) * 2 / 5);
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
		if (EnableSubText) { SubTextLabel->hide(); }
		TextLabel->hide();
	}
	_Private void onExpand() {
		if (!Shrinked) return;
		Shrinked = false;
		if (EnableSubText) { SubTextLabel->show(); }
		TextLabel->show();
	}
	_Public void setNormalStyleSheet(QString ss) {
		setVIDStyleSheet("normal", ss);
	}
	_Public void setHoverStyleSheet(QString ss) {
		setVIDStyleSheet("hover", ss);
	}
	_Public void setPressStyleSheet(QString ss) {
		setVIDStyleSheet("pressed", ss);
	}
	_Public void select() {
		Selected = true;
		applyVIDSS("pressed");
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
		if (!Selected) { applyVIDSS("hover"); }
	}
	_Public void leaveEvent(QEvent* event) {
		if (!Selected) { applyVIDSS("normal"); }
	}
	_Public void mousePressEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
			applyVIDSS("pressed");
			emit pressed();
		}
	}
	_Public void mouseReleaseEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
			applyVIDSS("pressed");
			Selected = true;
			emit clicked();
			emit selected(ButtonGroupIndex);
		}
	}
	_Protected void unSelect() {
		Selected = false;
		applyVIDSS("normal");
	}
};