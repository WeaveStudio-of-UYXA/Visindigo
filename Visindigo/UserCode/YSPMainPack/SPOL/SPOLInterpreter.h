#pragma once
#include "../../../Visindigo/VICore/VICore.h"
#include "SPOLParser.h"

typedef QMap<QString, QString> SPOLContext;
typedef QMap<QString, SPOLAbstractControllerParser*> SPOLParserMap;


/*
SPOL解释器
SPOL解释器需要知道场景中有哪些角色，请注意这里的角色是抽象控件，并非具体的演员
SPOL解释器在VIECMAScript的线程中运行，请勿进行危险操作
*/

class SPOLInterpreter :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Signal void sceneFinished();
	_Signal void onControllers(SPOL::ControllerTypeList types, SPOL::ControllerList ctrs);
	_Private static SPOLInterpreter* Instance;
	_Private SPOLParserMap Parsers;
	_Private QList<QString> SPOLDocument;
	_Private SPOLContext SPOLDocumentContext;
	_Private bool SceneFinished;
	_Private QMutex* ThreadMutex;
	_Private QWaitCondition* ThreadWaitCondition;
	_Private SPOLWorkingEnv* WorkingEnv;
	_Public def_init SPOLInterpreter(SPOLWorkingEnv* workingEnv, QMutex* mutex, QWaitCondition* waitCondition) {
		WorkingEnv = workingEnv;
		ThreadMutex = mutex;
		ThreadWaitCondition = waitCondition;
		connect(this, &SPOLInterpreter::onControllers, WorkingEnv->Terminal, &SPOLAbstractTerminal::onControllers);
	}
	_Public void addParser(SPOLAbstractControllerParser* parser) {
		if (!Parsers.contains(parser->getControllerName())) {
			parser->Context = &SPOLDocumentContext;
			Parsers.insert(parser->getControllerName(), parser);
		}
		else {
			return;
		}
	}
	_Private void wait() {
		ThreadWaitCondition->wait(ThreadMutex);
	}
	_Public void executeSPOL(const QStringList& spol) {

		SPOLDocument = spol;
		executeSPOL();
	}
	_Public void executeSPOL(const QString& spol = "") {
		SPOLDocument = spol.split("\n");
		SceneFinished = false;
		for(auto line = SPOLDocument.begin(); line != SPOLDocument.end(); line++) {
			if (SceneFinished) {
				break;
			}
			QStringList ControllersName= Parsers.keys();
			for (auto controllerName = ControllersName.begin(); controllerName != ControllersName.end(); controllerName++) {
				if ((*line).startsWith(*controllerName)) {
					SPOLAbstractControllerParser* par = Parsers[*controllerName];
					par->parseLine(*line);
					par->Types.clear();
					for (auto i = par->Parameters.begin(); i != par->Parameters.end(); i++) {
						delete (*i);
					}
					par->Parameters.clear();
					emit onControllers(par->Types, par->Parameters);
					for (auto i = par->Parameters.begin(); i != par->Parameters.end(); i++) {
						if (!(*i)->NoWait) { wait(); }
						break;
					}
					break;
				}
			}
		}
		SceneFinished = true;
		emit sceneFinished();
	}
};