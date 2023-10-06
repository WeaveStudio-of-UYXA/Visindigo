#include "../VIRatioWidget.h"

def_init VIAbstractRatioWidget::VIAbstractRatioWidget(QWidget* parent) :VIWidget(parent) {
};
void VIAbstractRatioWidget::mouseReleaseEvent(QMouseEvent* event) {
	isSelected = true;
	applyVIDSS("selected");
	emit clicked();
	emit released();
	emit selected();
}
void VIAbstractRatioWidget::mousePressEvent(QMouseEvent* event) {
	applyVIDSS("pressed");
	emit pressed();
}
void VIAbstractRatioWidget::mouseDoubleClickEvent(QMouseEvent* event) {
	isSelected = true;
	applyVIDSS("selected");
	emit doubleClicked();
	emit released();
	emit selected();
}
void VIAbstractRatioWidget::leaveEvent(QEvent* event) {
	if (isSelected) {
		applyVIDSS("selected");
	}
	else {
		applyVIDSS("normal");
	}
	emit leaved();
}
void VIAbstractRatioWidget::enterEvent(QEvent* event) {
	if (isSelected) {
		applyVIDSS("selected");
	}
	else {
		applyVIDSS("hover");
	}
	emit entered();
}
void VIAbstractRatioWidget::unSelect() {
	isSelected = false;
	applyVIDSS("normal");
	emit unselected();
}
void VIAbstractRatioWidget::select() {
	isSelected = true;
	applyVIDSS("selected");
	emit selected();
}
void VIAbstractRatioWidget::click() {
	select();
	emit clicked();
}
void VIAbstractRatioWidget::doubleClick() {
	select();
	emit doubleClicked();
}

def_init VIRatioWidgetContainer::VIRatioWidgetContainer(Qt::Orientation ori, QWidget* parent, Visindigo::EmphasisSide side) :VIWidget(parent) {
	Panel = new QWidget(this);
	ScrollArea = new QScrollArea(this);
	ScrollArea->setWidget(Panel);
	CurrentOrientation = ori;
	Side = side;
	WidgetPerPage = 7;
	AllowDragToRerange = false;
	switch (CurrentOrientation)
	{
	case Qt::Horizontal:
		CurrentLayout = new QHBoxLayout(Panel);
		ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		if (side == Visindigo::DefaultEmphasis) {
			side = Visindigo::Bottom;
		}
		break;
	case Qt::Vertical:
		CurrentLayout = new QVBoxLayout(Panel);
		ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		if (side == Visindigo::DefaultEmphasis) {
			side = Visindigo::Right;
		}
		break;
	}
	AnimationLabel = new VILabel(Panel);
	AnimationLabel->setVIDStyleSheet("default",
		"VILabel{\
			border:0px solid black; \
			border-radius:5px;\
			background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Foreground) + "_CLR;\
		}"
	);
	AnimationLabel->applyVIDSS("default");
	AnimationLabel->hide();
	AnimationBehavior = new private_VIRatioWidgetAnimation(this);
	switch (Side) {
	case Visindigo::Left:
		CurrentLayout->setContentsMargins(22, 11, 11, 11);
		break;
	case Visindigo::Top:
		CurrentLayout->setContentsMargins(11, 22, 11, 11);
		break;
	case Visindigo::Right:
		CurrentLayout->setContentsMargins(11, 11, 22, 11);
		break;
	case Visindigo::Bottom:
		CurrentLayout->setContentsMargins(11, 11, 11, 22);
		break;
	}
	switch (Side) {
	case Visindigo::Left:
		AnimationLabel->move(6, AnimationLabel->y());
		break;
	case Visindigo::Top:
		AnimationLabel->move(AnimationLabel->x(), 6);
		break;
	case Visindigo::Right:
		AnimationLabel->move(width() - 16, AnimationLabel->y());
		break;
	case Visindigo::Bottom:
		AnimationLabel->move(AnimationLabel->x(), height() - 16);
		break;
	}
};
void VIRatioWidgetContainer::addWidget(VIAbstractRatioWidget* widget, int index) {
	if (WidgetList.contains(widget)) {
		return;
	}
	if (index != -1) {
		index = index < 0 ? 0 : index;
		index = index > WidgetList.count() ? WidgetList.count() : index;
		WidgetList.insert(index, widget);
		switch (CurrentOrientation) {
		case Qt::Horizontal: {
			QHBoxLayout* layout = static_cast<QHBoxLayout*>(CurrentLayout);
			layout->insertWidget(index, widget);
			break; }
		case Qt::Vertical: {
			QVBoxLayout* layout2 = static_cast<QVBoxLayout*>(CurrentLayout);
			layout2->insertWidget(index, widget);
			break; }
		}
	}
	else {
		CurrentLayout->addWidget(widget);
		WidgetList.append(widget);
	}
	widget->installEventFilter(this);
	widget->setParent(Panel);
	connect(widget, &VIAbstractRatioWidget::selected, this, &VIRatioWidgetContainer::onSelected);
	if (CurrentLayout->count() == 1) {
		FirstWidget = widget;
	}
	updateWidgetSize();
}
void VIRatioWidgetContainer::insertWidget(int index, VIAbstractRatioWidget* widget) {
	addWidget(widget, index);
}
void VIRatioWidgetContainer::onSelected() {
	AnimationLabel->show();
	VIAbstractRatioWidget* widget = static_cast<VIAbstractRatioWidget*>(sender());
	if (LastSelectWidget == widget) {
		return;
	}
	LastSelectWidget = widget;
	for (int i = 0; i < WidgetList.count(); i++) {
		if (WidgetList.at(i) != widget) {
			WidgetList.at(i)->unSelect();
		}
	}
	emit selectWidgetChanged(widget);
	AnimationBehavior->setDuration(400);
	AnimationBehavior->setTarget(widget);
	AnimationBehavior->start();
}
void VIRatioWidgetContainer::removeWidget(VIAbstractRatioWidget* widget) {
	CurrentLayout->removeWidget(widget);
	WidgetList.removeOne(widget);
	widget->removeEventFilter(this);
	widget->setParent(this);
	if (WidgetList.count() == 0) {
		FirstWidget = VI_NULL;
	}
	updateWidgetSize();
}
void VIRatioWidgetContainer::resizeEvent(QResizeEvent* event) {
	ScrollArea->resize(width(), height());
	if (FirstWidget == nullptr) {
		return;
	}
	switch (CurrentOrientation)
	{
	case Qt::Horizontal:
		Panel->resize(Panel->width(), height());
		AnimationLabel->resize(FirstWidget->width() * 0.8, 10);
		break;
	case Qt::Vertical:
		Panel->resize(width(), Panel->height());
		AnimationLabel->resize(10, FirstWidget->height() * 0.8);
		break;
	}
	switch (Side) {
	case Visindigo::Left:
		AnimationLabel->move(6, AnimationLabel->y());
		break;
	case Visindigo::Top:
		AnimationLabel->move(AnimationLabel->x(), 6);
		break;
	case Visindigo::Right:
		AnimationLabel->move(width() - 16, AnimationLabel->y());
		break;
	case Visindigo::Bottom:
		AnimationLabel->move(AnimationLabel->x(), height() - 16);
		break;
	}
	updateWidgetSize();
}
void VIRatioWidgetContainer::leaveEvent(QEvent* event) {
	consoleLog("leaveEvent");
	eventFilter_MouseButtonRelease();
}
bool VIRatioWidgetContainer::eventFilter(QObject* watched, QEvent* event) {
	switch (event->type()) {
	case QEvent::MouseButtonPress:
		eventFilter_MouseButtonPress(watched, event);
		break;
	case QEvent::MouseButtonRelease:
		eventFilter_MouseButtonRelease(event);
		break;
	case QEvent::MouseMove: 
		eventFilter_MouseMove(event);
		break;
	}
	return false;
}

bool VIRatioWidgetContainer::eventFilter_MouseButtonPress(QObject* watched, QEvent* event) {
	VIAbstractRatioWidget* tar = dynamic_cast<VIAbstractRatioWidget*>(watched);
	if (tar == nullptr) {
		return false;
	}
	mousePressed = true;
	DraggingWidget = tar;
	mousePressPos = Panel->mapFromGlobal(QCursor::pos());
	return false;
}
bool VIRatioWidgetContainer::eventFilter_MouseButtonRelease(QEvent* event) {
	mousePressed = false;
	if (dragging) {
		QPoint pos = Panel->mapFromGlobal(QCursor::pos());
		VIAbstractRatioWidget* hoverOnRatio = VI_NULL;
		switch (CurrentOrientation) {
		case Qt::Horizontal:
			hoverOnRatio = WidgetList.first();
			for (int i = 1; i < WidgetList.length(); i++) {
				if (WidgetList[i]->x() > pos.x()) {
					hoverOnRatio = WidgetList[i - 1];
					break;
				}
			}
			if (WidgetList.last()->x() < pos.x()) {
				hoverOnRatio = WidgetList.last();
			}
			break;
		case Qt::Vertical:
			hoverOnRatio = WidgetList.first();
			for (int i = 1; i < WidgetList.length(); i++) {
				if (WidgetList[i]->y() > pos.y()) {
					hoverOnRatio = WidgetList[i - 1];
					break;
				}
			}
			if (WidgetList.last()->y() < pos.y()) {
				hoverOnRatio = WidgetList.last();
			}
			break;
		}
		if (hoverOnRatio != VI_NULL && WidgetList.contains(hoverOnRatio)) {
			consoleLog("Rerange");
			switch (CurrentOrientation) {
			case Qt::Horizontal: {
				int half = hoverOnRatio->x() + hoverOnRatio->width() / 2;
				bool bottom = Panel->mapFromGlobal(QCursor::pos()).x() > half;
				int index = WidgetList.indexOf(hoverOnRatio) + bottom;
				index = index < 0 ? 0 : index;
				index = index > WidgetList.count() ? WidgetList.count() : index;
				WidgetList.insert(index, DraggingWidget);
				QHBoxLayout* layout = static_cast<QHBoxLayout*>(CurrentLayout);
				layout->insertWidget(index, DraggingWidget);
				break; }
			case Qt::Vertical: {
				int half = hoverOnRatio->y() + hoverOnRatio->height() / 2;
				bool bottom = Panel->mapFromGlobal(QCursor::pos()).y() > half;
				int index = WidgetList.indexOf(hoverOnRatio) + bottom;
				index = index < 0 ? 0 : index;
				index = index > WidgetList.count() ? WidgetList.count() : index;
				WidgetList.insert(index, DraggingWidget);
				QVBoxLayout* layout2 = static_cast<QVBoxLayout*>(CurrentLayout);
				layout2->insertWidget(index, DraggingWidget);
				break; }
			}
			dragging = false;
		}
		else {
			switch (CurrentOrientation) {
			case Qt::Horizontal: {
				QHBoxLayout* layout = static_cast<QHBoxLayout*>(CurrentLayout);
				layout->insertWidget(DraggingIndex, DraggingWidget);
				WidgetList.insert(DraggingIndex, DraggingWidget);
				break; }
			case Qt::Vertical: {
				QVBoxLayout* layout2 = static_cast<QVBoxLayout*>(CurrentLayout);
				layout2->insertWidget(DraggingIndex, DraggingWidget);
				WidgetList.insert(DraggingIndex, DraggingWidget);
				break; }
			}
			dragging = false;
		}
		DraggingWidget = VI_NULL;
	}
	return false;
}
bool VIRatioWidgetContainer::eventFilter_MouseMove(QEvent* event) {
	QMouseEvent* e = static_cast<QMouseEvent*>(event);
	if (mousePressed && DraggingWidget != VI_NULL) {
		if (AllowDragToRerange) {
			DraggingIndex = WidgetList.indexOf(DraggingWidget);
			QPoint currentPos = Panel->mapFromGlobal(QCursor::pos());
			switch (CurrentOrientation) {
			case Qt::Horizontal:
				if (abs(currentPos.x() - mousePressPos.x()) < FirstWidget->width() / 3) {
					break;
				}
				CurrentLayout->removeWidget(DraggingWidget);
				WidgetList.removeOne(DraggingWidget);
				DraggingWidget->move(currentPos.x()-DraggingWidget->width()/2, DraggingWidget->y());
				DraggingWidget->raise();
				dragging = true;
				break;
			case Qt::Vertical:
				if (abs(currentPos.y() - mousePressPos.y()) < FirstWidget->height() / 3) {
					break;
				}
				CurrentLayout->removeWidget(DraggingWidget);
				WidgetList.removeOne(DraggingWidget);
				DraggingWidget->move(DraggingWidget->x(), currentPos.y()-DraggingWidget->height()/2);
				DraggingWidget->raise();
				dragging = true;
				break;
			}
		}
	}
	return false;
}
void VIRatioWidgetContainer::updateWidgetSize() {
	switch (CurrentOrientation)
	{
	case Qt::Horizontal:
		{
			int width = (this->width() / WidgetPerPage + 22 ) * WidgetList.count();
			Panel->resize(width, Panel->height());
		}
		break;
	case Qt::Vertical:
		{
			int height = (this->height() / WidgetPerPage +22) * WidgetList.count();
			Panel->resize(Panel->width(), height);
		}
		break;
	}
}
def_init private_VIRatioWidgetAnimation::private_VIRatioWidgetAnimation(VIRatioWidgetContainer* master) {
	MasterWidget = master;
	AnimationLabel = master->AnimationLabel;
};
void private_VIRatioWidgetAnimation::setTarget(VIAbstractRatioWidget* tar) {
	TargetWidget = tar;
	InitPos = AnimationLabel->pos();
	switch (MasterWidget->CurrentOrientation) {
	case Qt::Horizontal:
		deltaMove = tar->x() - AnimationLabel->x();
		TargetPos = QPoint(tar->x() + AnimationLabel->width() * 0.1, AnimationLabel->y());
		deltaSize = AnimationLabel->width() * 0.5;
		break;
	case Qt::Vertical:
		deltaMove = tar->y() - AnimationLabel->y();
		TargetPos = QPoint(AnimationLabel->x(), tar->y() + AnimationLabel->height() * 0.1);
		deltaSize = AnimationLabel->height() * 0.5;
		break;
	}
}
void private_VIRatioWidgetAnimation::onStart() {
	LastDurationPercent = 0;
	effectiveDeltaMove = 0;
}
void private_VIRatioWidgetAnimation::onTick() {
	float cd = 0;
	cd = VICommonMapping::sin_0_1_0(Duration->getPercent()) - LastDurationPercent;
	LastDurationPercent = VICommonMapping::sin_0_1_0(Duration->getPercent());
	int ds = deltaSize * cd;
	effectiveDeltaMove += ds;
	switch (MasterWidget->CurrentOrientation) {
	case Qt::Horizontal:
		AnimationLabel->move(InitPos.x() + deltaMove * VICommonMapping::sin2_0_1(Duration->getPercent()), AnimationLabel->y());
		AnimationLabel->resize(AnimationLabel->width() + ds, AnimationLabel->height());
		break;
	case Qt::Vertical:
		AnimationLabel->move(AnimationLabel->x(), InitPos.y() + deltaMove * VICommonMapping::sin2_0_1(Duration->getPercent()));
		AnimationLabel->resize(AnimationLabel->width(), AnimationLabel->height() + ds);
		break;
	}
}
void private_VIRatioWidgetAnimation::onStop() {
	AnimationLabel->move(TargetPos);
	switch (MasterWidget->CurrentOrientation)
	{
	case Qt::Horizontal:
		AnimationLabel->resize(AnimationLabel->width() - effectiveDeltaMove, AnimationLabel->height());
		break;
	case Qt::Vertical:
		AnimationLabel->resize(AnimationLabel->width(), AnimationLabel->height() - effectiveDeltaMove);
		break;
	}
}