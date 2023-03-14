#pragma once
#include <QtCore>
#include "../../VICore/macro/VIMarco.h"

//此文档提供简化的旧版SPOL解释器源码
//此解释器不能扩展，不支持任何逻辑，小分支和大分支解释器已经被移除，标题控制器亦被移除，但仍保留版本控制器。
//此解释器不再提供跨线程交互，故应当由VIJS主机线程或新版SPOL解释器线程调用
//新版解释器又死半道上了（这已经是第五次了）
class SPOL9X :public QObject {
	Q_OBJECT;
	_Signal void controller_Cover(bool coverStatus);
	_Signal void controller_Speak_Chara(QStringList charaPicPath);
	_Signal void controller_Speak_FadeAnimation(float duration, bool isFadeIn);
	_Signal void controller_Speak_TextAnimation(float msPerText, float msWait, QString text, bool isContinue);
	_Signal void controller_Backdrop_FadeAnimation(float duration, QString backdropPath);
	_Signal void controller_Free_TextAnimation(float msPerText, float msWait, QString text, bool isContinue, float xPercent, float yPercent, float widthPercent, float heightPercent, QChar AlignLMR);
	_Signal void controller_BackgroundMusic(QString musicPath, int volume, float FadeInDuration, float FadeOutDuration, bool isLoop);
	_Signal void controller_BackgroundSound(QString soundPath, int volume, float FadeInDuration, float FadeOutDuration);
};