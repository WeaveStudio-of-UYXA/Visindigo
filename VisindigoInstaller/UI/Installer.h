#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtGUI>
class VisindigoCentralWidget :public QWidget
{
	Q_OBJECT
public:
	QLabel* TitleLabel;
	QWidget* BG;
	QGridLayout* CurrentLayout;
	VisindigoCentralWidget(QWidget* parent = Q_NULLPTR) :QWidget(parent) {
		BG = new QWidget(this);
		BG->setObjectName("Background");
		CurrentLayout = new QGridLayout(this);
		
		TitleLabel = new QLabel(this);
		TitleLabel->setText("Visindigo Installer");
		TitleLabel->setStyleSheet("QLabel{font-size:40px;border-radius:0px;border-bottom:1px solid black}");
		this->setStyleSheet("QWidget{background-color:#FFFFFF;font-family:'Microsoft YaHei';border-radius:5px;} \
			QWidget#Background{border:1px solid black}");
		CurrentLayout->addWidget(TitleLabel, 0, 0, 1, 2);
		
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		BG->resize(size());
	}
};

class VisindigoMainWin :public QMainWindow
{
	Q_OBJECT
public:
	VisindigoCentralWidget* CentralWidget;
	QGridLayout* CurrentLayout;
public:
	VisindigoMainWin(QWidget* parent = Q_NULLPTR) :QMainWindow(parent) {
		this->setMinimumSize(1366, 768);
		this->resize(1366, 768);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);
		CentralWidget = new VisindigoCentralWidget(this);
		//CurrentLayout = new QGridLayout(this);
		//CurrentLayout->addWidget(CentralWidget);
		qDebug() << this->size();
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		CentralWidget->resize(this->size());
		qDebug() << CentralWidget->size();
	}
};