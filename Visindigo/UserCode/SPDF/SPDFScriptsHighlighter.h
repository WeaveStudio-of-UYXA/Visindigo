#pragma once
#include "../../Visindigo/VICore/VICore.h"
#include "../../Visindigo/VIWidgets/VIStyleSheet.h"
#include "SPDFParser.h"

class SPDFScriptsHightlighter :public QSyntaxHighlighter, VIBaseObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public enum class LineType {
		Normal, Comment, CommentAsSPOL, SPOLComment,
					CommentEnd, CommentAsSPOLEnd, SPOLCommentEnd,
	};
	_Public VIColorPalette* Palette;
	_Public def_init SPDFScriptsHightlighter(QTextDocument* doc) :QSyntaxHighlighter(doc) {

	}
	_Public void highlightBlock(const QString& text) override;
};