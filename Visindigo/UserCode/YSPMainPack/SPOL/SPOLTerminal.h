#pragma once
#include "../../../Visindigo/VICore/VICore.h"
namespace SPOL {
	enum class ControllerType {
		Speaking,
		AnyText,
		Background,
		Sound,
		State,
		Animation
	};
	typedef QList<SPOL::ControllerType> ControllerTypeList;
	class Controller {
		_Public bool NoWait = false;
	};
	typedef QList<SPOL::Controller*> ControllerList;
	class Speaking :public Controller {
	public:
		QString Who;
		QString What;
		VIMilliSecond Speed;
		VIMilliSecond Wait;
	};
	class AnyText :public Controller {
	public:
		QString What;
		VIMilliSecond Speed;
		VIMilliSecond Wait;
		int X, Y;
		Qt::Alignment Align;
	};
	class Background :public Controller {
	public:
		QString What;
		VIMilliSecond Speed;
	};
	class Sound :public Controller {
	public:
		QString What;
		VIMilliSecond Speed;
		bool asBGM;
		float Volume;
	};
	class State :public Controller {
	public:
		QString Who;
		QString What;
		VIMilliSecond Speed;
	};
	class Animation :public Controller {
	public:
		QString Who;
		QString What;
		VIMilliSecond Speed;
	};
}

/*
* Abstract Terminal
* 如果用户要从SPOL获得控制数据，必须·继承此类并实现其虚函数
*/
class SPOLAbstractTerminal
{
	VI_ProtectedFlag(ControlHandled);
	_Public def_init SPOLAbstractTerminal(){ControlHandled = false;}
	_Public void spolHandled(){ControlHandled = true;}
	_Public virtual void onControllers(SPOL::ControllerTypeList type, SPOL::ControllerList controllers) PureVirtual;
};