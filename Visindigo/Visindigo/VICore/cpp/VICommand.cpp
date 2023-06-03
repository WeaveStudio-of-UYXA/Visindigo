#include "../VICommand.h"
VICommandHost* VICommandHost::Instance = VI_NULLPTR;

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

def_init VICommandHost::VICommandHost(QObject* parent) :VIObject(parent) {
	setObjectName("VICommandHost");
	Instance = this;
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

QStringList VICommandHost::blankSplitter(QString str) {
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
bool VICommandHost::handleCommand(QString command) {
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
}