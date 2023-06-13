#pragma once
#include "../../../Visindigo/VICore/VICore.h"
#include "SPOLInterpreter.h"
#include "SPSReader.h"
class VIECMA_SPOL :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public SPOLScripts* Scripts;
	_Public def_init VIECMA_SPOL() {
		setObjectName("SPOL");
	}
	_Slot void loadStory(QStringList spolLines);
};
class SPOLScripts :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void starting();
	_Signal void storyFilePrepared();
	_Signal void interpreterPrepared();
	_Signal void finished();
	friend class VIECMA_SPOL;
	_Protected VIECMAScripts* ScriptsEngine;
	_Protected SPOLInterpreter* Interpreter = VI_NULLPTR;
	_Private SPOLWorkingEnv* Env;
	_Private QMutex* Mutex;
	_Private QWaitCondition* WaitCondition;
	_Private QList<SPOLAbstractControllerParser*> Parsers;
	_Private VIECMA_SPOL* SPOL;
	_Public def_init SPOLScripts(SPOLWorkingEnv* env, VISuper* parent = VI_NULLPTR):VIObject(parent){
		Env = env;
		ScriptsEngine = new VIECMAScripts();
		Mutex = ScriptsEngine->getThreadMutex();
		WaitCondition = ScriptsEngine->getThreadWaitCondition();
		connect(ScriptsEngine, &VIECMAScripts::finished, this, &SPOLScripts::onThreadFinished);
		SPOL = new VIECMA_SPOL();
		SPOL->Scripts = this;
		ScriptsEngine->importVIObject(SPOL);
	}
	_Public void addParser(SPOLAbstractControllerParser* parser) {
		Parsers.append(parser);
	}
	_Public void exec(QString path, QString entry = "main") {
		emit starting();
		SPSReader::spawnAllStoryFile(path);
		emit storyFilePrepared();
		if (Interpreter != VI_NULLPTR) {
			Interpreter->deleteLater();
		}
		Interpreter = new SPOLInterpreter(Env, Mutex, WaitCondition);
		for (auto parser : Parsers) {
			Interpreter->addParser(parser);
		}
		Interpreter->moveToThread(ScriptsEngine->getThread());
		emit interpreterPrepared();
		ScriptsEngine->threadBoot(path, entry);
	}
	_Public void awake() {
		WaitCondition->wakeAll();
	}
	_Slot void onThreadFinished() {
		Interpreter->deleteLater();
		Interpreter = VI_NULLPTR;
		emit finished();
	}
};