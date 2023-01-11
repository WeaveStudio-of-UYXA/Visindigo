#pragma once
#define VIJSHostWait VIJSGlobal::VIJSWait.wait(&VIJSGlobal::VIJSMutex)
#define VIJSHostWake VIJSGlobal::VIJSWait.wakeAll()

#define SSDEF(funcName,...) Q_SIGNALS: void S##funcName(__VA_ARGS__);public Q_SLOTS:void funcName(__VA_ARGS__)
#define JsVIGUI GUILabel
#define JsVIGUI_PARA QObject* parent, VIGUI2DWidget* gui
#define JsVI_INVOKE(VIGUI) public: VIGUI* GUILabel; Q_SIGNALS: void newGUILabel(VIGUI**);
#define JsVI_NewFrom(type) BIND(this, SIGNAL(newGUILabel(type**)), gui, SLOT(new##type(type**))); emit newGUILabel(&JsVIGUI);
#define JsVI_INIT __init__(parent, (VI2DGUILabel*)JsVIGUI);
#define JsVI_WAIT(para) if (para) { VIJSHostWait; }
#define JsVI_AniBIND(func, ...) BIND(this, SIGNAL(S##func(__VA_ARGS__)), JsVIGUI, SLOT(func##Ani(__VA_ARGS__)));
#define SSDEF_SA_VOID(funcName) SSDEF(funcName){ emit S##funcName();}
#define JsVI_BIND_SAME(funcName, Target, ...) BIND(this, SIGNAL(S##funcName(__VA_ARGS__)), Target, SLOT(funcName(__VA_ARGS__)));
#define JsVI_BIND_SAME_VOID(funcName, Target) JsVI_BIND_SAME(funcName, Target);
#define JsVI_CONNECT_SAME(funcName, Target, ...) connect(this, SIGNAL(S##funcName(__VA_ARGS__)), Target, SLOT(funcName(__VA_ARGS__)));
#define JsVI_CONNECT_SAME_VOID(funcName, Target) JsVI_CONNECT_SAME(funcName, Target);