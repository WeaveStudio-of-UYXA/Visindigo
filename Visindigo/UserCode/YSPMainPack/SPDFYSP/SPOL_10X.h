#pragma once
#include "../../SPDF/SPDFParser.h"

namespace SPOL_10X {
	class SpeakingController :public SPDFAbstractControllerParser {
		Q_OBJECT;
		VI_OBJECT;
		_Public def_init SpeakingController() {
			setControllerName(">>>");
		}
		_Public bool parseLine(const QString& line) override {
			SPDFParserObject speaker;
			speaker.MethodName = "Speaker_1";
			speaker.Parameters["Name"] = line.split(":")[0];
			speaker.Parameters["Text"] = line.split(":")[1];
			Parameters.append(speaker);
			return true;
		}
	};
}