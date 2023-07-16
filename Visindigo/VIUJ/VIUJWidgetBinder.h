#pragma once
#include "../VIWidgets/VIWidgets.h"

class VIPublicAPI VIUJWidgetBinder :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Protected QWidget* self;
	VI_ProtectedProperty(QString, TargetInstanceName);
	_Public def_init VIUJWidgetBinder(VISuper* parent = VI_NULLPTR):VIObject(parent) {
		self = VI_NULLPTR;
		TargetInstanceName = "";
	}
	//This function will be called after all binders have been save the master widget.
	//If users want to connect the signal & slot , they should do it in this function.
	_Public virtual void onBindFinish() PureVirtual; 
	_Public void setMaster(QWidget* master) {
		self = master;
		self->installEventFilter(this);
	}
	_Public virtual bool resizeEvent(QResizeEvent* event) { return false; }
	_Public virtual bool mousePressEvent(QMouseEvent* event) { return false; }
	_Public virtual bool mouseReleaseEvent(QMouseEvent* event) { return false; }
	_Public virtual bool mouseDoubleClickEvent(QMouseEvent* event) { return false; }
	_Public virtual bool mouseMoveEvent(QMouseEvent* event) { return false; }
	_Public virtual bool wheelEvent(QWheelEvent* event) { return false; }
	_Public virtual bool keyPressEvent(QKeyEvent* event) { return false; }
	_Public virtual bool keyReleaseEvent(QKeyEvent* event) { return false; }
	_Public virtual bool focusInEvent(QFocusEvent* event) { return false; }
	_Public virtual bool focusOutEvent(QFocusEvent* event) { return false; }
	_Public virtual bool enterEvent(QEvent* event) { return false; }
	_Public virtual bool leaveEvent(QEvent* event) { return false; }
	_Public virtual bool paintEvent(QPaintEvent* event) { return false; }
	_Public virtual bool moveEvent(QMoveEvent* event) { return false; }
	_Public virtual bool closeEvent(QCloseEvent* event) { return false; }
	_Public virtual bool showEvent(QShowEvent* event) { return false; }
	_Public virtual bool hideEvent(QHideEvent* event) { return false; }
	_Private bool eventFilter(QObject* watched, QEvent* event) {
		if (watched == self) {
			QEvent::Type type = event->type();
			switch (type) {
			case QEvent::Resize:
				return resizeEvent((QResizeEvent*)event);
			case QEvent::MouseButtonPress:
				return mousePressEvent((QMouseEvent*)event);
			case QEvent::MouseButtonRelease:
				return mouseReleaseEvent((QMouseEvent*)event);
			case QEvent::MouseButtonDblClick:
				return mouseDoubleClickEvent((QMouseEvent*)event);
			case QEvent::MouseMove:
				return mouseMoveEvent((QMouseEvent*)event);
			case QEvent::Wheel:
				return wheelEvent((QWheelEvent*)event);
			case QEvent::KeyPress:
				return keyPressEvent((QKeyEvent*)event);
			case QEvent::KeyRelease:
				return keyReleaseEvent((QKeyEvent*)event);
			case QEvent::FocusIn:
				return focusInEvent((QFocusEvent*)event);
			case QEvent::FocusOut:
				return focusOutEvent((QFocusEvent*)event);
			case QEvent::Enter:
				return enterEvent(event);
			case QEvent::Leave:
				return leaveEvent(event);
			case QEvent::Paint:
				return paintEvent((QPaintEvent*)event);
			case QEvent::Move:
				return moveEvent((QMoveEvent*)event);
			case QEvent::Close:
				return closeEvent((QCloseEvent*)event);
			case QEvent::Show:
				return showEvent((QShowEvent*)event);
			case QEvent::Hide:
				return hideEvent((QHideEvent*)event);
			default:
				return false;
			}
		}
		return false;
	}
};