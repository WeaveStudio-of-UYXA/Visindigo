#include "../VICodeEdit.h"

def_init private_VICodeEdit::private_VICodeEdit(QWidget* parent) :QTextEdit(parent) {
	KeyBoardFreeTimer = new QTimer(this);
	KeyBoardFreeTimer->setSingleShot(true);
	KeyBoardFreeTimer->setInterval(3000);
	connect(KeyBoardFreeTimer, &QTimer::timeout, this, &private_VICodeEdit::keyBoardFree);
	KeyBoardFreeTimer->start();
}

void private_VICodeEdit::keyPressEvent(QKeyEvent* event) {
	KeyBoardFreeTimer->start();
	switch (event->key()) {
	case Qt::Key_F:
		if (event->modifiers() == Qt::ControlModifier) {
			emit shortcutKey_Find();
		}
		else {
			QTextEdit::keyPressEvent(event);
		}
		return;
	case Qt::Key_Tab:
		keyPressEvent_Tab(event);
		return;
	case Qt::Key_Backtab:
		keyPressEvent_BackTab(event);
		return;
	case Qt::Key_Return:
		keyPressEvent_Return(event);
		return;
	case Qt::Key_V:
		keyPressEvent_V(event);
		return;
	case Qt::Key_S:
		keyPressEvent_S(event);
		return;
	case Qt::Key_R:
		keyPressEvent_R(event);
		return;
	default:
		QTextEdit::keyPressEvent(event);
		return;
	}
}

void private_VICodeEdit::keyPressEvent_Tab(QKeyEvent* event) {
	//if cursor is not in selection
	if (!textCursor().hasSelection()) {
		//if the text before is empty, insert 4 spaces, else insert a tab
		QTextCursor cursor = textCursor();
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
		QString lineText = cursor.selectedText();
		for (auto i : lineText) {
			if (i != ' ' && i != '\t') {
				insertPlainText("\t");
				return;
			}
		}
		insertPlainText("    ");
		emit lineIndentChanged(cursor.blockNumber(), VICommandHost::getIndentLevel(cursor.block().text()));
		return;
	}
	else {
		//if cursor is in selection, insert 4 spaces before every line, no matter how many lines are selected
		QTextCursor cursor = textCursor();
		//get the selection start
		int startPosition = cursor.selectionStart();
		int endPosition = cursor.selectionEnd();
		//get the start line and end line
		int startLine = document()->findBlock(startPosition).blockNumber();
		int endLine = document()->findBlock(endPosition).blockNumber();
		cursor.setPosition(startPosition);
		cursor.movePosition(QTextCursor::StartOfLine);
		int fixStartPos = cursor.position();
		//add 4 spaces before every line
		for (int i = startLine; i <= endLine; i++) {
			cursor.movePosition(QTextCursor::StartOfLine);
			cursor.insertText("    ");
			emit lineIndentChanged(cursor.blockNumber(), VICommandHost::getIndentLevel(cursor.block().text()));
			cursor.movePosition(QTextCursor::Down);
		}
		cursor.setPosition(fixStartPos, QTextCursor::KeepAnchor);
		return;
	}
}

void private_VICodeEdit::keyPressEvent_BackTab(QKeyEvent* event) {
	if (!textCursor().hasSelection()) {
		//if the text before is empty, remove 4 spaces, else do nothing
		qDebug() << "Shift+Tab";
		QTextCursor cursor = textCursor();
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
		QString lineText = cursor.selectedText();
		int removeCharCount = 0;
		for (auto i : lineText) {
			if (i != ' ' && i != '\t') {
				return;
			}
		}
		for (auto i : lineText) {
			if (i == ' ') {
				removeCharCount++;
			}
			else if (i == '\t') {
				removeCharCount += 4;
			}
			if (removeCharCount >= 4) {
				removeCharCount = 4;
				break;
			}
		}
		for (int i = 0; i < removeCharCount; i++) {
			textCursor().deletePreviousChar();
		}
		emit lineIndentChanged(cursor.blockNumber(), VICommandHost::getIndentLevel(cursor.block().text()));
		return;
	}
	else {
		//if cursor is in selection, insert 4 spaces before every line, no matter how many lines are selected
		QTextCursor cursor = textCursor();
		//get the selection start
		int startPosition = cursor.selectionStart();
		int endPosition = cursor.selectionEnd();
		//get the start line and end line
		int startLine = document()->findBlock(startPosition).blockNumber();
		int endLine = document()->findBlock(endPosition).blockNumber();
		cursor.setPosition(startPosition);
		cursor.movePosition(QTextCursor::StartOfLine);
		int fixStartPos = cursor.position();
		//add 4 spaces before every line
		for (int i = startLine; i <= endLine; i++) {
			cursor.movePosition(QTextCursor::StartOfLine);
			cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
			QString lineText = cursor.selectedText();
			int removeCharCount = 0;
			for (auto i : lineText) {
				if (i == ' ') {
					removeCharCount++;
				}
				else if (i == '\t') {
					removeCharCount += 4;
				}
				else {
					break;
				}
				if (removeCharCount >= 4) {
					removeCharCount = 4;
					break;
				}
			}
			cursor.movePosition(QTextCursor::StartOfLine);
			for (int i = 0; i < removeCharCount; i++) {
				cursor.deleteChar();
			}
			emit lineIndentChanged(cursor.blockNumber(), VICommandHost::getIndentLevel(cursor.block().text()));
			cursor.movePosition(QTextCursor::Down);
		}
		cursor.setPosition(fixStartPos, QTextCursor::KeepAnchor);
		return;
	}
}

void private_VICodeEdit::keyPressEvent_Return(QKeyEvent* event) {
	//get the text of current line
	QTextCursor cursor = textCursor();
	cursor.movePosition(QTextCursor::StartOfLine);
	cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
	QString lineText = cursor.selectedText();
	//get the number of spaces at the beginning of the line
	int spaceCount = 0;
	for (int i = 0; i < lineText.size(); i++) {
		if (lineText[i] == ' ') {
			spaceCount++;
		}
		else {
			break;
		}
	}
	//create a new line and insert spaces
	insertPlainText("\n");
	for (int i = 0; i < spaceCount; i++) {
		insertPlainText(" ");
	}
	return;
}

void private_VICodeEdit::keyPressEvent_V(QKeyEvent* event) {
	//ctrl + v, paste without format(override raw)
	if (event->modifiers() == Qt::ControlModifier) {
		QClipboard* clipboard = QApplication::clipboard();
		QString text = clipboard->text();
		QStringList textList = text.split("\n");
		for (int i = 0; i < textList.size(); i++) {
			VICommandHost::stringIndentStandardization(&textList[i]);
		}
		insertPlainText(textList.join("\n"));
		return;
	}
	else {
		QTextEdit::keyPressEvent(event);
		return;
	}
}

void private_VICodeEdit::keyPressEvent_S(QKeyEvent* event) {
	if (event->modifiers() == Qt::ControlModifier) {
		emit saveNeeded(false);
		return;
	}
	else {
		QTextEdit::keyPressEvent(event);
		return;
	}
}

void private_VICodeEdit::keyPressEvent_R(QKeyEvent* event) {
	if (event->modifiers() == Qt::ControlModifier) {
		emit saveNeeded(true);
		return;
	}
	else {
		QTextEdit::keyPressEvent(event);
		return;
	}
}
def_init VICodeEdit::VICodeEdit(QWidget* parent) :VIWidget(parent) {
	this->setWindowTitle("Visindigo Code Edit");
	FilePath = "";
	needSave = false;
	CurrentLineCount = 0;
	QFont font = QFont("Microsoft YaHei");
	LineNumberArea = new QTextEdit(this);
	LineNumberArea->setReadOnly(true);
	LineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	LineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	LineNumberArea->setAlignment(Qt::AlignRight);
	LineNumberArea->setFont(font);
	CodeEdit = new private_VICodeEdit(this);
	CodeEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	CodeEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	//关闭自动换行
	CodeEdit->setLineWrapMode(QTextEdit::NoWrap);
	CodeEdit->setFont(font);
	CodeEdit->setTabStopDistance(4 * QFontMetrics(font).lineWidth());
	CodeEdit->setAcceptRichText(false);
	CodeEdit->installEventFilter(this);
	connect(CodeEdit->document(), &QTextDocument::blockCountChanged, this, &VICodeEdit::updateLineNumber);
	connect(CodeEdit, &QTextEdit::cursorPositionChanged, this, &VICodeEdit::cursorInfoGenerator);
	connect(LineNumberArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &VICodeEdit::scrollEveryEdit);
	connect(CodeEdit->verticalScrollBar(), &QScrollBar::valueChanged, this, &VICodeEdit::scrollEveryEdit);
	connect(CodeEdit->document(), &QTextDocument::cursorPositionChanged, this, &VICodeEdit::debugCursorInfo);
	connect(CodeEdit, &private_VICodeEdit::shortcutKey_Find, this, &VICodeEdit::showFindAndReplaceWidget);
	connect(CodeEdit, &private_VICodeEdit::lineIndentChanged, this, &VICodeEdit::updateLineInfoArea);
	connect(CodeEdit, &private_VICodeEdit::saveNeeded, this, &VICodeEdit::save);
	this->setStyleSheet("QWidget{background-color:#202020;color:#FFFFFF}");
	LineInfoArea = new QTextBrowser(this);
	LineInfoArea->setReadOnly(true);
	LineInfoArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	LineInfoArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	LineInfoArea->setLineWrapMode(QTextEdit::NoWrap);
	LineInfoArea->setAlignment(Qt::AlignLeft);
	LineInfoArea->setFont(font);
	LineInfoArea->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	LineInfoArea->setStyleSheet("QTextBrowser{background-color:#00000000;color:#55FFFFFF}");
	CodeCompleter = new QCompleter(this);
	CodeCompleter->setWidget(CodeEdit);
	CodeCompleter->setCompletionMode(QCompleter::PopupCompletion);
	CodeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	CodeCompleter->setWrapAround(false);
	CodeCompleter->setModel(new QStringListModel(this));
	CodeCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
}

void VICodeEdit::cursorInfoGenerator() {
	if (CodeEdit->textCursor().hasSelection()) {
		return;
	}
	QTextCursor cursor = CodeEdit->textCursor();
	int line = cursor.blockNumber() + 1;
	int column = cursor.columnNumber() + 1;
	int position = cursor.position();
	QString lineText = cursor.block().text();
	emit cursorPositionChanged(line, column, position, lineText);
}
bool VICodeEdit::eventFilter(QObject* tar, QEvent* eve) {
	if (tar == CodeEdit) {
		if (eve->type() == QEvent::KeyPress) {
			needSave = true;
			return false;
		}
	}
	return false;
}

bool VICodeEdit::openFile(const QString& filePath) {
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}
	QTextStream in(&file);
	in.setEncoding(QStringConverter::Utf8);
	CodeEdit->setText(in.readAll());
	file.close();
	FilePath = filePath;
	QString langType = filePath.split(".").last();
	if (langType != LanguageType) {
		LanguageType = langType.toLower();
		emit languageTypeChanged(LanguageType);
	}
	return true;
}

bool VICodeEdit::saveFile(const QString& filePath) {
	if (filePath == "") {
		if (FilePath == "") {
			return false;
		}
		else {
			QFile file(FilePath);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
				return false;
			}
			QTextStream out(&file);
			out.setEncoding(QStringConverter::Utf8);
			out << CodeEdit->toPlainText();
			file.close();
			needSave = false;
			return true;
		}
	}
	else {
		QFile file(filePath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			return false;
		}
		QTextStream out(&file);
		out.setEncoding(QStringConverter::Utf8);
		out << CodeEdit->toPlainText();
		file.close();
		FilePath = filePath;
		needSave = false;
		return true;
	}
}

void VICodeEdit::save(bool saveAs) {
	if (FilePath == "" || saveAs) {
		//save as dialog
		QString filePath = QFileDialog::getSaveFileName(this, "Save As", "", "All Files(*.*)");
		if (filePath == "") {
			QMessageBox::critical(this, "Error", "Save Failed!");
			return;
		}
		else {
			if (!saveFile(filePath)) {
				QMessageBox::critical(this, "Error", "Save Failed!");
			}
			else {
				FilePath = filePath;
			}
		}
	}
	else {
		if (!saveFile()) {
			QMessageBox::critical(this, "Error", "Save Failed!");
		}
	}
}

void VICodeEdit::closeEvent(QCloseEvent* event) {
	if (needSave) {
		QMessageBox::StandardButton button = QMessageBox::question(this, "Save", "Do you want to save the file?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (button == QMessageBox::Yes) {
			if (!saveFile()) {
				event->ignore();
			}
			else {
				event->accept();
				this->deleteLater();
			}
		}
		else if (button == QMessageBox::No) {
			event->accept();
			this->deleteLater();
		}
		else {
			event->ignore();
		}
	}
	else {
		event->accept();
	}
}

bool VICodeEdit::find(const QString& substr, QTextDocument::FindFlags flags) {
	return CodeEdit->find(substr, flags);
}

void VICodeEdit::showFindAndReplaceWidget() {
	if (FindAndReplaceWidget != VI_NULL) {
		FindAndReplaceWidget->show();
		return;
	}
	else {
		FindAndReplaceWidget = new private_VICodeEdit_FindAndReplaceWidget(CodeEdit, this);
		FindAndReplaceWidget->setMaximumSize(480, 200);
		FindAndReplaceWidget->show();
	}
	FindAndReplaceWidget->raise();
	int width = qMin(this->width() * 0.4, 480.0);
	FindAndReplaceWidget->setGeometry(this->width() - width - 11, 11, width, this->width() * 0.4 * 0.5);
}

void VICodeEdit::setFont(const QFont& font) {
	LineNumberArea->setFont(font);
	CodeEdit->setFont(font);
	CodeEdit->setTabStopDistance(4 * QFontMetrics(font).lineWidth());
}

void VICodeEdit::setCodeSyntaxHighlighter(QSyntaxHighlighter* highlighter) {
	if (CodeHighlighter != nullptr) {
		CodeHighlighter->deleteLater();
	}
	CodeHighlighter = highlighter;
	CodeHighlighter->setDocument(CodeEdit->document());
}

void VICodeEdit::resizeEvent(QResizeEvent* event) {
	LineNumberArea->setGeometry(0, 0, 50, this->height());
	CodeEdit->setGeometry(50, 0, this->width() - 50, this->height());
	LineInfoArea->setGeometry(50, 0, this->width() - 50, this->height());
	if (FindAndReplaceWidget != VI_NULL) {
		int width = qMin(this->width() * 0.4, 480.0);
		FindAndReplaceWidget->setGeometry(this->width() - width - 11, 11, width, this->width() * 0.4 * 0.5);
	}
}

void VICodeEdit::debugCursorInfo() {
	QTextCursor cursor = CodeEdit->textCursor();
	QString text = "Line: " + QString::number(cursor.blockNumber() + 1) + "\n";
	text += "Column: " + QString::number(cursor.columnNumber() + 1) + "\n";
	text += "Position: " + QString::number(cursor.position() + 1) + "\n";
	//LineInfoArea->setText(text);
	//高亮当前行
	QTextEdit::ExtraSelection selection;
	QColor lineColor = QColor("#9966CCFF");
	selection.format.setBackground(lineColor);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);
	selection.cursor = CodeEdit->textCursor();
	selection.cursor.clearSelection();
	CodeEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>() << selection);
}

void VICodeEdit::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		QTextCursor cursor = CodeEdit->cursorForPosition(event->pos());
		CodeEdit->setTextCursor(cursor);
		CodeEdit->setFocus();
	}
}

void VICodeEdit::scrollEveryEdit(int value) {
	LineNumberArea->verticalScrollBar()->setValue(value);
	CodeEdit->verticalScrollBar()->setValue(value);
	LineInfoArea->verticalScrollBar()->setValue(value);
}
void VICodeEdit::updateLineNumber() {
	int latestlineCount = CodeEdit->document()->blockCount();
	int delta = latestlineCount - CurrentLineCount;
	if (delta > 0) {
		quint32 startLine = CurrentLineCount + 1;
		quint32 endLine = latestlineCount;
		QString text = "<p align=\"right\">";
		for (int i = startLine; i <= endLine; i++) {
			text += QString::number(i) + "<br>";
		}
		text += "</p>";
		QTextCursor cursor = LineNumberArea->textCursor();
		cursor.movePosition(QTextCursor::End);
		cursor.insertHtml(text);

		QTextCursor editCursor = CodeEdit->textCursor();
		editCursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, delta);
		quint32 lineIndex = editCursor.blockNumber();
		qDebug() << lineIndex;
		QList<int> indentLevelList;
		for (int i = 0; i < delta; i++) {
			indentLevelList.append(VICommandHost::getIndentLevel(editCursor.block().text()));
			editCursor.movePosition(QTextCursor::Down);
		}
		QTextCursor lineInfoCursor = LineInfoArea->textCursor();
		lineInfoCursor.movePosition(QTextCursor::Start);
		lineInfoCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineIndex);
		lineInfoCursor.movePosition(QTextCursor::StartOfLine);
		for (auto i = indentLevelList.begin(); i != indentLevelList.end(); i++) {
			lineInfoCursor.movePosition(QTextCursor::StartOfLine);
			if (*i == 0) {
				lineInfoCursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
				lineInfoCursor.insertText("\n");
				//lineInfoCursor.movePosition(QTextCursor::Down);
				continue;
			}
			QString line = getIndentNotice(*i);
			line += "\n";
			lineInfoCursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
			lineInfoCursor.insertText(line);
			//lineInfoCursor.movePosition(QTextCursor::Down);
		}
	}
	else {
		QTextCursor cursor = LineNumberArea->textCursor();
		cursor.movePosition(QTextCursor::Start);
		cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, latestlineCount);
		cursor.movePosition(QTextCursor::StartOfLine);
		cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
		cursor.removeSelectedText();

		QTextCursor editCursor = CodeEdit->textCursor();
		editCursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, -delta);
		quint32 lineIndex = editCursor.blockNumber();
		QTextCursor lineInfoCursor = LineInfoArea->textCursor();
		lineInfoCursor.movePosition(QTextCursor::Start);
		lineInfoCursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, lineIndex + 1);
		for (int i = 0; i < -delta; i++) {
			lineInfoCursor.movePosition(QTextCursor::StartOfLine);
			lineInfoCursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor);
			lineInfoCursor.removeSelectedText();
		}
	}
	CurrentLineCount = latestlineCount;
	LineNumberArea->verticalScrollBar()->setRange(CodeEdit->verticalScrollBar()->minimum(), CodeEdit->verticalScrollBar()->maximum());
	LineNumberArea->verticalScrollBar()->setValue(CodeEdit->verticalScrollBar()->value());
	LineInfoArea->verticalScrollBar()->setRange(CodeEdit->verticalScrollBar()->minimum(), CodeEdit->verticalScrollBar()->maximum());
	LineInfoArea->verticalScrollBar()->setValue(CodeEdit->verticalScrollBar()->value());
}

void VICodeEdit::updateLineInfoArea(quint32 lineIndex, quint32 indentLevel) {
	if (indentLevel == 0) {
		return;
	}
	QString line = getIndentNotice(indentLevel);
	//修改LineInfoArea的内容
	QTextCursor cursor = LineInfoArea->textCursor();
	cursor.movePosition(QTextCursor::Start);
	for (int i = 0; i < lineIndex; i++) {
		cursor.movePosition(QTextCursor::Down);
	}
	cursor.movePosition(QTextCursor::StartOfLine);
	cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
	cursor.insertText(line);
}

QString VICodeEdit::getIndentNotice(quint32 indentLevel) {
	QString result = "";
	for (int i = 0; i < indentLevel; i++) {
		result += ":   ";
	}
	return result;
}