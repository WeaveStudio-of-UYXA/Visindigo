#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "SPOLInterpreter.h"
#include "SPSReader.h"

class SPDFScripts :public VIObject
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
	_Private SPDFWorkingEnv* Env;
	_Private QMutex* Mutex;
	_Private QWaitCondition* WaitCondition;
	_Private QList<SPDFAbstractControllerParser*> Parsers;
	_Private VIECMA_SPOL* ESSPOL;
	_Public def_init SPDFScripts(SPDFWorkingEnv* env, VISuper* parent = VI_NULLPTR):VIObject(parent){
		Env = env;
		ScriptsEngine = new VIECMAScripts();
		Mutex = ScriptsEngine->getThreadMutex();
		WaitCondition = ScriptsEngine->getThreadWaitCondition();
		connect(ScriptsEngine, &VIECMAScripts::finished, this, &SPDFScripts::onThreadFinished);
		connect(env->Terminal, &SPDFAbstractTerminal::controllerHandled, this, &SPDFScripts::awake);
		ESSPOL = new VIECMA_SPOL();
		ESSPOL->Scripts = this;
		ScriptsEngine->importVIObject(ESSPOL);
	}
	_Public void addParser(SPDFAbstractControllerParser* parser) {
		Parsers.append(parser);
	}
	_Public void exec(QString path, QString entry = "main") {
		emit starting();
		SPSReader::spawnAllStoryFile(path);
		qDebug() << "storyFilePrepared";
		emit storyFilePrepared();
		if (Interpreter != VI_NULLPTR) {
			Interpreter->deleteLater();
		}
		Interpreter = new SPOLInterpreter(Env, Mutex, WaitCondition);
		for (auto parser : Parsers) {
			Interpreter->addParser(parser);
		}
		Interpreter->moveToThread(ScriptsEngine->getThread());
		qDebug() << "interpreterPrepared";
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