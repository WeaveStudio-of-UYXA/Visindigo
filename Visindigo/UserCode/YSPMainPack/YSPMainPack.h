#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "../../Visindigo/VI2DScene/VI2DSceneWidget.h"
#include "SPOL/SPSReader.h"
#include "SPOL/SPSEditor.h"

class RotationBehavior :public VIBasicBehavior {
	Q_OBJECT;
	VI_Property(VI2DSceneWidget*, Scene);
	_Public def_init RotationBehavior(QObject* parent = VI_NULLPTR) :VIBasicBehavior(parent) {};
	_Public virtual void onActive() HalfVirtual;
	_Public virtual void onTick() {
		Scene->TestProxy->setRotation(Scene->TestProxy->rotation() + 2);
		Scene->TestLabel->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
	};
	_Public virtual void onPassive() HalfVirtual;
};
class YSPPlayerWidget :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Public VI2DSceneWidget* Scene;
	_Public QGridLayout* CurrentLayout;
	_Public RotationBehavior* rotationBehavior;
	_Public def_init YSPPlayerWidget(QWidget* parent = VI_NULLPTR) :VIWidget(parent) {
		//把背景色调成黑的
		this->setStyleSheet("YSPPlayerWidget{background-color:black;}");
		this->setWindowTitle("YSPPlayerWidget");
		Scene = new VI2DSceneWidget(this);
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->setSpacing(0);
		CurrentLayout->setMargin(0);
		CurrentLayout->addWidget(Scene);
		rotationBehavior = new RotationBehavior(this);
		rotationBehavior->setScene(Scene);
		rotationBehavior->active(VIAbstractBehavior::QuantifyTickType::T128);
	};
};
class YSPMainPack :public VIPackage
{
	Q_OBJECT;
	QWidget* testWin;
	VIDebugBehavior* debugBehavior;
	YSPPlayerWidget* playerWidget;
	VIMultiButtonGroup* testGroup;
	SPSEditor* spsEditor;
	_Public def_init YSPMainPack(QObject* parent = VI_NULLPTR) :VIPackage(parent) {
		SPSReader::spawnStoryFile("./Dev/t10.js");
		PackageName = "YSPMainPack";
		debugBehavior = new VIDebugBehavior(this);
		playerWidget = new YSPPlayerWidget();
		//playerWidget->showFullScreen();
		consoleLog("new YSPCommand");
		VICommand_Reg(YSPCommand);
		VIFramework::execCommand("ecma");
		spsEditor = new SPSEditor();
		spsEditor->show();
		testGroup = new VIMultiButtonGroup(Qt::Vertical);
		testGroup->resize(200, 500);
		testGroup->spawnButton("TEST1", "", "test1");
		testGroup->spawnButton("TEST2", "", "test2");
		testGroup->spawnButton("TEST3", "", "test3");
		testGroup->spawnButton("TEST4", "", "test4");
		testGroup->setNormalStyleSheet("VIMultiButton{background-color:rgb(255,255,255);border:1px solid rgb(200,200,200);border-radius:3px;}");
		testGroup->setHoverStyleSheet("VIMultiButton{background-color:rgb(230,230,255);border:1px solid rgb(230,230,255);border-radius:3px;}");
		testGroup->setPressStyleSheet("VIMultiButton{background-color:rgb(200,200,200);border:1px solid rgb(200,200,200);border-radius:3px;}");
		testGroup->selectFirst();
		testGroup->show();
	};
	_Public virtual void onActive() {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is active!");
		VIFramework::execCommand("YSP ua1 ua2 -t n1 -s n2 -n \"n3ss ss\" | YSP uua1 uua2");
	};
	_Public virtual void onPassive() {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is passive!");
	};
	_Public virtual void onTick() {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is ticking!");
		//throw VIDimensionError("Test");
	};
	_Public virtual void onEvent(QEvent* e) {
		//QMessageBox::information(VI_NULLPTR, "YSPMainPack", "YSPMainPack is eventing!");
	};
	_Public VICommand_Handler(YSPCommand) {
		VICommand_Name("YSP") {
			debugPrint();
			setCommandOutput("rt");
			return true;
		}
	};
};
