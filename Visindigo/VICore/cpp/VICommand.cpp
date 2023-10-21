#include "../VICommand.h"
#include <iostream>

VI_Singleton_StaticInit(VICommandHost);

VICommandHandler::VICommandHandler() {
}
VICommandHandler::~VICommandHandler() {
	VICommandHost::getInstance()->removeCommandHandler(this);
}
bool VICommandHost::addCommandHandler(VICommandHandler* handler) {
	if (CommandHandlers.contains(handler->CommandName)) {
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "There is already an instance that can handle the command \"" +
			handler->CommandName + "\". You cannot add another instance that can handle this command"));
		return false;
	}
	else {
		CommandHandlers[handler->CommandName] = handler;
		VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "The command \"" + handler->CommandName + "\" is added."));
		return true;
	}
}

def_init VIStdIOCommandHandler::VIStdIOCommandHandler(QObject* parent) :QThread(parent) {
	setObjectName("VIStdIOCommandHandler");
}

void VIStdIOCommandHandler::run() {
	VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "The standard input/output listener is started."));
	while (true) {
		Mutex.lock();
		bool running = Running;
		Mutex.unlock();
		if (!running) {
			break;
		}
		QString command = VIConsole::getLine();
		if (command == "") {
			continue;
		}
		emit commandReceived(command);
	}
	VIConsole::printLine(VIConsole::inNoticeStyle(getLogPrefix() + "The standard input/output listener is stopped."));
}
def_init VICommandHost::VICommandHost(bool listenStdIO, QObject* parent) :VIObject(parent) {
	VI_Singleton_Init;
	ListenStdIO = listenStdIO;
	if (ListenStdIO) {
		enableStdIOListener();
	}
	setObjectName("VICommandHost");
	consoleLog("Initialized");
}
void VICommandHost::removeCommandHandler(VICommandHandler* handler) {
	if (CommandHandlers.contains(handler->CommandName)) {
		CommandHandlers.remove(handler->CommandName);
	}
	else {
		VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "There is no instance that can handle the command \"" +
			handler->CommandName + "\"."));
	}
}

bool VICommandHost::handleCommand(const QString& command) {
	if (command == "") {
		return false;
	}
	CommandOutput = "";
	QStringList rawspl = VICommandHost::blankSplitter(command);
	if (rawspl.length() == 0) {
		return false;
	}
	QList<QStringList> commands;
	QStringList currentCommand;
	for (int i = 0; i < rawspl.length(); i++) {
		if (rawspl[i] == "|") {
			commands.append(currentCommand);
			currentCommand.clear();
		}
		else {
			currentCommand.append(rawspl[i]);
		}
	}
	commands.append(currentCommand);
	for (int i = 0; i < commands.length(); i++) {
		QStringList args = commands[i];
		QString commandName = args[0];
		QMap<QString, QString> namedArgs;
		QStringList unnamedArgs;
		for (int i = 1; i < args.length();) {
			if (args[i].startsWith("-") || args[i].startsWith("\\")) {
				namedArgs[args[i].remove(0, 1)] = args[i + 1];
				i += 2;
			}
			else {
				unnamedArgs.append(args[i]);
				i++;
			}
		}
		if (CommandOutput != "") {
			unnamedArgs.append(CommandOutput);
		}
		if (CommandHandlers.contains(commandName)) {
			CommandHandlers[commandName]->UnnamedArgs = unnamedArgs;
			CommandHandlers[commandName]->NamedArgs.clear();
			CommandHandlers[commandName]->NamedArgs = namedArgs;
			if (!CommandHandlers[commandName]->handleCommand()) {
				VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "The command \"" + commandName + "\" failed to execute."));
				return false;
			}
			CommandOutput = CommandHandlers[commandName]->CommandOutput;
		}
		else {
			VIConsole::printLine(VIConsole::inWarningStyle(getLogPrefix() + "There is no instance that can handle the command \"" +
				commandName + "\"."));
			return false;
		}
	}
	return true;
}

void VICommandHost::enableStdIOListener() {
	if (StdIOListener != nullptr) {
		return;
	}
	StdIOListener = new VIStdIOCommandHandler(this);
	connect(StdIOListener, &VIStdIOCommandHandler::commandReceived, this, &VICommandHost::handleCommand,
		Qt::BlockingQueuedConnection);
	StdIOListener->start();
}

void VICommandHost::disableStdIOListener() {
	if (StdIOListener == nullptr) {
		return;
	}
	StdIOListener->Mutex.lock();
	StdIOListener->Running = false;
	StdIOListener->Mutex.unlock();
	StdIOListener->deleteLater();
	StdIOListener = nullptr;
}
QStringList VICommandHost::blankSplitter(const QString& str) {
	QStringList result;
	QString current = "";
	bool inString = false;
	for (int i = 0; i < str.size(); i++) {
		if ((str[i] == ' ' || str[i] == "\t") && !inString) {
			if (current != "") {
				result.append(current);
				current = "";
			}
			continue;
		}
		if (str[i] == '|' && !inString) {
			if (current != "") {
				result.append(current);
				current = "";
			}
			result.append("|");
		}
		else if (str[i] == '"' && str[i - 1] != '\\') {
			if (inString) {
				if (current != "") {
					result.append(current);
					current = "";
				}
				inString = false;
			}
			else {
				inString = true;
			}
		}
		else {
			current += str[i];
		}
	}
	if (current != "") {
		result.append(current);
	}
	return result;
}

QStringList VICommandHost::scientificSplitter(const QString& str, const QChar& ch) {
	return scientificSplitter(str, QString(ch));
}

QStringList VICommandHost::scientificSplitter(const QString& str, const QString& ch) {
	QStringList result = str.split(ch);
	for (auto i = 0; i < result.length() - 1;) {
		quint32 count = 0;
		for (auto j = result[i].length() - 1; j > 0; j--) {
			if (result[i][j] == '\\') {
				count++;
			}
			else {
				break;
			}
		}
		if (count % 2) {
			result[i].remove(result[i].length() - 1, 1);
			result[i].replace("\\\\", "\\");
			result[i] += ch + result[i + 1];
			result.removeAt(i + 1);
		}
		else {
			result[i].replace("\\\\", "\\");
			i++;
		}
	}
	return result;
}

quint32 VICommandHost::getIndentLevel(const QString& str, quint8 levelSize) {
	quint32 result = 0;
	for (auto i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			result++;
		}
		else if (str[i] == '\t') {
			result += levelSize;
		}
		else {
			break;
		}
	}
	return result / levelSize;
}

quint32 VICommandHost::getIndentCount(const QString& str) {
	quint32 result = 0;
	for (auto i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			result++;
		}
		else if (str[i] == '\t') {
			result++;
		}
		else {
			break;
		}
	}
	return result;
}

void VICommandHost::removeIndent(QString* str) {
	quint32 indentCount = getIndentCount(*str);
	str->remove(0, indentCount);
}

void VICommandHost::stringIndentStandardization(QString* str, quint8 levelSize) {
	quint32 indentStandard = getIndentLevel(*str, levelSize) * levelSize;
	removeIndent(str);
	for (auto i = 0; i < indentStandard; i++) {
		str->insert(0, " ");
	}
}