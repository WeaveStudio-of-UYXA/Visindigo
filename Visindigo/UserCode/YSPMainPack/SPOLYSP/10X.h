#pragma once
#include "../../SPDF/SPDFParser.h"
#include "10X_Define.h"

namespace YSP_10X {
	class SpeakingController :public SPDFAbstractControllerParser {
		Q_OBJECT;
		VI_OBJECT;
		_Public def_init SpeakingController() {
			setControllerName(">>>");
			setFunctionLike(false);
		}
		_Public bool onParseLine(const QString& line) override {
			QStringList Speakers = line.split(">>>");
			for (auto speaker = Speakers.begin(); speaker != Speakers.end(); speaker++) {
				QStringList SpeakerInfo = speaker->split(":");
				if (SpeakerInfo.length() < 1 || SpeakerInfo.length() > 3) {
					consoleLog("讲述控制器：主参数个数少于1个或多于三个");
					return false;
				}
				QStringList SpeakerDisplayInfo = SpeakerInfo[0].split("/");
				if (SpeakerDisplayInfo.length() > 5) {
					consoleLog("讲述控制器：显示参数多于五个");
					return false;
				}
				QString DisplayName = SpeakerDisplayInfo[0];
				QString SpeakerText = "";
				if (SpeakerInfo.length() == 2) {
					SpeakerText = SpeakerInfo[1];
				}
				else {
					DisplayName = SpeakerInfo[1];
					SpeakerText = SpeakerInfo[2];
				}
				int length = SpeakerDisplayInfo.length();
				for (int i = 0; i < 6 - length; i++) { SpeakerDisplayInfo.append(""); }
				QString FileNameSuffix = (SpeakerDisplayInfo[1] != "" ? SpeakerDisplayInfo[1] : "");
				QString FilterSuffix = (SpeakerDisplayInfo[2] != "" ? SpeakerDisplayInfo[2] : "");
				QString FadeInSecond = (SpeakerDisplayInfo[3] != "" ? SpeakerDisplayInfo[3] : "0");
				QString FadeOutSecond = (SpeakerDisplayInfo[4] != "" ? SpeakerDisplayInfo[4] : "0");
				QString FileName = SpeakerDisplayInfo[0];
				if (FileNameSuffix != "") { FileName += "_" + FileNameSuffix; }
				if (FilterSuffix != "") { FileName += "_" + FilterSuffix; }
				if (FileName == "") { FileName = "__None__"; }
				else { FileName += ".png"; }
				int index = SpeakerText.lastIndexOf("(");
				QStringList SpeedSubController = { "0.04","1.75" };
				if (index != -1 && SpeakerText.endsWith(")")) {
					QString SpeedSubControllerText = SpeakerText.mid(index + 1, SpeakerText.length() - index - 2);
					SpeakerText = SpeakerText.mid(0, index);
					SpeedSubController = SpeedSubControllerText.split(",");
					if (SpeedSubController.length() > 2) {
						consoleLog("讲述控制器：速度控制器参数多于2");
						return false;
					}
					if (SpeedSubController.length() == 1) {
						SpeedSubController.append("1.75");
					}
				}
				/*
				实现有误：
				讲述控制器一行内有多个时，按SPOL规范要求应该只有一个人是可以说话的，但是这里实现的是多个人同时说话
				应该被拆分为多个CharaController和一个SpeakingController
				*/
				SPDFParserResult SpeakerController;
				SpeakerController.MethodName = YSP_Speaking;
				SpeakerController.Parameters["SpeakerCount"] = Speakers.length();
				SpeakerController.Parameters["DisplayName"] = DisplayName;
				SpeakerController.Parameters["FileName"] = FileName;
				SpeakerController.Parameters["FadeInSecond"] = FadeInSecond;
				SpeakerController.Parameters["FadeOutSecond"] = FadeOutSecond;
				SpeakerController.Parameters["SecondPerChar"] = SpeedSubController[0];
				SpeakerController.Parameters["SecondLineEnd"] = SpeedSubController[1];
				SpeakerController.Parameters["Text"] = SpeakerText;
				Parameters.append(SpeakerController);
			}
			return true;
		}
	};
}