#pragma once
#include <QtCore>
#include <QtGUI>
#include <QtWidgets>

class ProgramPin :public QWidget
{
	Q_OBJECT
public:
	QPushButton* ManageButton;
	QPushButton* UpdateButton;
	QPushButton* DeleteButton;
	QLabel* LogoLabel;
	QLabel* NameLabel;
	QLabel* VersionLabel;
	QLabel* DescriptionLabel;
	QGridLayout* CurrentLayout;
public:
	ProgramPin(QWidget* parent) :QWidget(parent) {
		LogoLabel = new QLabel(this);
		NameLabel = new QLabel(this);
		VersionLabel = new QLabel(this);
		DescriptionLabel = new QLabel(this);
		CurrentLayout = new QGridLayout(this);
		ManageButton = new QPushButton(this);
		UpdateButton = new QPushButton(this);
		DeleteButton = new QPushButton(this);
	}
};
