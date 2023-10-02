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
	CurrentOrientation = ori;
	Side = side;
	switch (CurrentOrientation)
	{
	case Qt::Horizontal:
		CurrentLayout = new QHBoxLayout(this);
		if (side == Visindigo::DefaultEmphasis) {
			side = Visindigo::Bottom;
		}
		break;
	case Qt::Vertical:
		CurrentLayout = new QVBoxLayout(this);
		if (side == Visindigo::DefaultEmphasis) {
			side = Visindigo::Right;
		}
		break;
	}
	AnimationLabel = new VILabel(this);
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
void VIRatioWidgetContainer::addWidget(VIAbstractRatioWidget* widget) {
	if (WidgetList.contains(widget)) {
		return;
	}
	CurrentLayout->addWidget(widget);
	WidgetList.append(widget);
	connect(widget, &VIAbstractRatioWidget::selected, this, &VIRatioWidgetContainer::onSelected);
	if (CurrentLayout->count() == 1) {
		FirstWidget = widget;
	}
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
}
void VIRatioWidgetContainer::resizeEvent(QResizeEvent* event) {
	if (FirstWidget == nullptr) {
		return;
	}
	switch (CurrentOrientation)
	{
	case Qt::Horizontal:
		AnimationLabel->resize(FirstWidget->width() * 0.8, 10);
		break;
	case Qt::Vertical:
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