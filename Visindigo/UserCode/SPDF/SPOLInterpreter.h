#pragma once
#include "../../Visindigo/VICore/VICore.h"

#include "SPDFParser.h"

class SPDFScripts;
class VIECMA_SPOL :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public SPDFScripts* Scripts;
	_Public def_init VIECMA_SPOL() {
		setObjectName("SPOL");
	}
	_Slot void loadStory(QJSValue spolLinesRaw);
};

typedef QMap<QString, QString> SPOLContext;
typedef QMap<QString, SPDFAbstractControllerParser*> SPDFParserMap;


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
	_Signal void onControllers(SPDFParserObjectList* list);
	_Private static SPOLInterpreter* Instance;
	_Private SPDFParserMap Parsers;
	_Private QList<QString> SPOLDocument;
	_Private SPOLContext SPOLDocumentContext;
	_Private bool SceneFinished;
	_Private QMutex* ThreadMutex;
	_Private QWaitCondition* ThreadWaitCondition;
	_Private SPDFWorkingEnv* WorkingEnv;
	_Public def_init SPOLInterpreter(SPDFWorkingEnv* workingEnv, QMutex* mutex, QWaitCondition* waitCondition) {
		WorkingEnv = workingEnv;
		ThreadMutex = mutex;
		ThreadWaitCondition = waitCondition;
		connect(this, &SPOLInterpreter::onControllers, WorkingEnv->Terminal, &SPDFAbstractTerminal::onControllers);
	}
	_Public void addParser(SPDFAbstractControllerParser* parser) {
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
		if (spol != "") { SPOLDocument = spol.split("\n"); }
		SceneFinished = false;
		for(auto line = SPOLDocument.begin(); line != SPOLDocument.end(); line++) {
			if (SceneFinished) {
				break;
			}
			QStringList ControllersName= Parsers.keys();
			qDebug()<<ControllersName;
			for (auto controllerName = ControllersName.begin(); controllerName != ControllersName.end(); controllerName++) {
				if ((*line).startsWith(*controllerName)) {
					qDebug()<<*controllerName;
					SPDFAbstractControllerParser* par = Parsers[*controllerName];
					par->Parameters.clear();
					bool success = par->parseLine(*line);
					//可能有线程安全问题，因为抽象控制器解析器是在VIECMAScript的线程中运行的
					//但是这里的onControllers目标应该是在主线程中运行的
					//主要目前从逻辑上来说，Parameters在解析之后VIECMAScript中应该没人会动它
					//然后紧接着就是主线程拿去用，用完之后就会被清空，所以暂时不管了
					if (!success) { continue; }//以后可以整个内部异常机制
					emit onControllers(&(par->Parameters));
					for (auto i = par->Parameters.begin(); i != par->Parameters.end(); i++) {
						if (!(*i).NoWait) { wait(); }
						break;
					}
					break;
				}
			}
			qDebug()<<*line;
		}
		SceneFinished = true;
		emit sceneFinished();
	}
};