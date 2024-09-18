#include "../VIDifferenceAnalyzer.h"		

void VIDifferenceAnalyzer::analyze(const QString& previous, const QString& current, VIDifferenceData* data) {
	QFile previousFile(previous);
	QFile currentFile(current);
	if (!previousFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		VIConsole::printLine("Previous file could not be opened.");
		return;
	}
	if (!currentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		VIConsole::printLine("Current file could not be opened.");
		return;
	}
	QTextStream previousStream(&previousFile);
	QTextStream currentStream(&currentFile);
	previousStream.setEncoding(QStringConverter::Utf8);
	currentStream.setEncoding(QStringConverter::Utf8);
	while (!previousStream.atEnd()) {
		data->PreviousDocument.append(previousStream.readLine());
	}
	while (!currentStream.atEnd()) {
		data->CurrentDocument.append(currentStream.readLine());
	}
	previousFile.close();
	currentFile.close();
	analyze(data);
}
void VIDifferenceAnalyzer::analyze(VIDifferenceData* data) {
	auto previous = data->PreviousDocument.begin();
	auto previousIndex = 0;
	auto current = data->CurrentDocument.begin();
	auto currentIndex = 0;
	bool addPreviousOrCurrent = true;
	while (previous != data->PreviousDocument.end() && current != data->CurrentDocument.end()) {
		if (*previous == *current) {
			data->CommonSubsequencePrevious.append(previousIndex);
			data->CommonSubsequenceCurrent.append(currentIndex);
			addPreviousOrCurrent = !addPreviousOrCurrent;
			previous++;
			previousIndex++;
			current++;
			currentIndex++;
		}
		else {
			if (addPreviousOrCurrent) {
				previous++;
				previousIndex++;
				if (previous == data->PreviousDocument.end()) {
					previousIndex = data->CommonSubsequencePrevious.last();
					previous = data->PreviousDocument.begin() + previousIndex;
					currentIndex++;
					current++;
					if (current == data->CurrentDocument.end()) {
						break;
					}
				}
			}
			else {
				current++;
				currentIndex++;
				if (current == data->CurrentDocument.end()) {
					currentIndex = data->CommonSubsequenceCurrent.last();
					current = data->CurrentDocument.begin() + currentIndex;
					previousIndex++;
					previous++;
					if (previous == data->PreviousDocument.end()) {
						break;
					}
				}
			}
		}
	}
	for (auto i = 0; i < data->PreviousDocument.length(); i++) {
		if (!data->CommonSubsequencePrevious.contains(i)) {
			data->RemovedLines.append(i);
		}
	}
	for (auto i = 0; i < data->CurrentDocument.length(); i++) {
		if (!data->CommonSubsequenceCurrent.contains(i)) {
			data->AddedLines.append(i);
		}
	}
}

void VIDifferenceAnalyzer::debugPrint(VIDifferenceData* data) {
	VIConsole::printLine("Previous Document Removed Lines: ");
	for (auto i = 0; i < data->RemovedLines.length(); i++) {
		VIConsole::printLine(data->PreviousDocument[data->RemovedLines[i]]);
	}
	VIConsole::printLine("Current Document Added Lines: ");
	for (auto i = 0; i < data->AddedLines.length(); i++) {
		VIConsole::printLine(data->CurrentDocument[data->AddedLines[i]]);
	}
}