#pragma once
#include "VISObject.h"
#include "VEVM_Memory.h"
#include "VEVMStdExtension.h"
#include <fstream>
class VISDefConstructor {
	std::ifstream VEVMIFile;
	std::string filePath;
	std::stack<VISObject*> defStack;
public:
	VISDefConstructor() {}
	VISDefConstructor(std::string path) {
		filePath = path;
	}
	void setFilePath(std::string path) {
		filePath = path;
	}
	void doConstructor() {
		VEVMIFile.open(filePath);
		if (!VEVMIFile.is_open()) {
			throw std::exception("File not found");
		}
		else {
			while (!VEVMIFile.eof()) {
				char* line = nullptr;
				VEVMIFile.getline(line, 65535);
				if (line != nullptr) {
					std::string lineStr = line;
					eachLine(lineStr);
				}
			}
		}
	}
private:
	void eachLine(std::string &line) {
		std::vector<std::string> lineSplit = {}; 
		VEVM_StdExtension::splitStdStringReserveString(line, ' ', lineSplit);
		if (lineSplit.size() == 0) { return; }
		if (lineSplit[0] == "C_CLASS") {
			
		}
	}
};