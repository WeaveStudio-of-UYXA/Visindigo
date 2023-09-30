#pragma once
#include "../../VICore/VICore.h"

class VICodeSyntax :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public enum class MetaType {
		Keyword,
		Operator,
		Number,
		String,
		SingleComment,
		MultiComment_Start,
		MultiComment_End,
		Other
	};
	_Private QHash<MetaType, QColor> TokenColor;
	_Private QHash<MetaType, QRegExp> TokenRegExp;
	_Private QList<MetaType> TokenOrder;
	_Public void setKeywordColor(QColor color) {
		TokenColor[MetaType::Keyword] = color;
	}
	_Public void setKeywords(QStringList keywords) {
		TokenRegExp[MetaType::Keyword] = QRegExp("\\b(" + keywords.join("|") + ")\\b");
	}
	_Public void setStringColor(QColor color) {
		TokenColor[MetaType::String] = color;
	}
	_Public void setStringMark(QStringList marks) {
		//将marks中的字符作为字符串前后的引号标记，并忽略有转义字符的引号
		TokenRegExp[MetaType::String] = QRegExp("((?<!\\\\)(?:\\\\\\\\)*)(?:" + marks.join("|") + ")(\\1|.)*?(?:" + marks.join("|") + ")");
	}
};