#pragma once
#include "VIWidget.h"
#include "VIWidgetsTransQt.h"
#include "../VICore/VICore.h"

class private_VIRatioWidgetAnimation;
class VIRatioWidgetContainer;

class VIPublicAPI VIAbstractRatioWidget :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	friend class VIRatioWidgetContainer;
	_Signal void clicked();
	_Signal void pressed();
	_Signal void released();
	_Signal void entered();
	_Signal void leaved();
	_Signal void selected();
	_Signal void unselected();
	_Signal void doubleClicked();
	_Protected bool isSelected = false;
	_Public def_init VIAbstractRatioWidget(QWidget* parent = VI_NULL);
	_Public virtual void mouseReleaseEvent(QMouseEvent* event) override final;
	_Public virtual void mousePressEvent(QMouseEvent* event) override final;
	_Public virtual void mouseDoubleClickEvent(QMouseEvent* event) override final;
	_Public virtual void leaveEvent(QEvent* event) override final;
	_Public virtual void enterEvent(QEvent* event) override final;
	_Protected void unSelect();
	_Public void select();
	_Public void click();
	_Public void doubleClick();
};

class VIPublicAPI VIRatioWidgetContainer :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	friend class private_VIRatioWidgetAnimation;
	_Signal void selectWidgetChanged(VIAbstractRatioWidget* widget);
	_Private QLayout* CurrentLayout = VI_NULL;
	_Protected Qt::Orientation CurrentOrientation = Qt::Horizontal;
	_Protected VILabel* AnimationLabel = VI_NULL;
	VI_Flag(AllowDragToRerange); 
	VI_Property(int, WidgetPerPage);
	_Private private_VIRatioWidgetAnimation* AnimationBehavior = VI_NULL;
	_Private QList<VIAbstractRatioWidget*> WidgetList;
	_Private VIAbstractRatioWidget* FirstWidget = VI_NULL;
	_Private VIAbstractRatioWidget* LastSelectWidget = VI_NULL;
	_Private QWidget* Panel = VI_NULL;
	_Private QScrollArea* ScrollArea = VI_NULL;
	_Private QPoint mousePressPos;
	_Private bool mousePressed = false;
	_Private bool dragging = false;
	_Private int DraggingIndex = -1;
	_Private VIAbstractRatioWidget* DraggingWidget = VI_NULL;
	_Protected Visindigo::EmphasisSide Side = Visindigo::DefaultEmphasis;
	_Public def_init VIRatioWidgetContainer(Qt::Orientation ori, QWidget* parent = VI_NULL, Visindigo::EmphasisSide side = Visindigo::DefaultEmphasis);
	_Public void addWidget(VIAbstractRatioWidget* widget, int index = -1);
	_Public void insertWidget(int index, VIAbstractRatioWidget* widget);
	_Slot void onSelected();
	_Public void removeWidget(VIAbstractRatioWidget* widget);
	_Public void resizeEvent(QResizeEvent* event) override; 
	_Public void leaveEvent(QEvent* event) override;
	_Private bool eventFilter(QObject* watched, QEvent* event) override;
	_Private bool eventFilter_MouseButtonPress(QObject* watched, QEvent* event);
	_Private bool eventFilter_MouseButtonRelease(QEvent* event = VI_NULL);
	_Private bool eventFilter_MouseMove(QEvent* event);
	_Private void updateWidgetSize();
};

class VIPrivateAPI private_VIRatioWidgetAnimation :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Public VIRatioWidgetContainer* MasterWidget = VI_NULL;
	_Public VIAbstractRatioWidget* TargetWidget = VI_NULL;
	_Public VILabel* AnimationLabel = VI_NULL;
	_Private QPoint InitPos;
	_Private QPoint TargetPos;
	_Private double deltaMove;
	_Private double deltaSize;
	_Private double LastDurationPercent;
	_Private int effectiveDeltaMove;
	_Public def_init private_VIRatioWidgetAnimation(VIRatioWidgetContainer* master);
	_Public void setTarget(VIAbstractRatioWidget* tar);
	_Public virtual void onStart() override;
	_Public virtual void onTick() override;
	_Public virtual void onStop() override;
};