#pragma once
#include <string>
#include <vector>
class VEVM_StdExtension {
public:
	static void splitStdString(const std::string& str, const std::string& splits, std::vector<std::string>& res)
	{
		if (str == "") { return; }
		std::string strs = str + splits;
		size_t pos = strs.find(splits);
		int step = splits.size();
		while (pos != strs.npos)
		{
			std::string temp = strs.substr(0, pos);
			res.push_back(temp);
			strs = strs.substr(pos + step, strs.size());
			pos = strs.find(splits);
		}
	}
	static void splitStdStringReserveString(const std::string& str, char split, std::vector<std::string>& res) {
		bool inString = false;
		bool afterBackslash = false;
		std::string temp = "";
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '\\') {
				if (afterBackslash) {
					temp += '\\';
				}
				else {
					afterBackslash = true;
					continue;
				}
			}
			else if (str[i] == '\"') {
				if (afterBackslash) {
					temp += '\"';
				}
				else {
					inString = !inString;
				}
			}
			else if (str[i] == split && !inString) {
				res.push_back(temp);
				temp = "";
			}
			afterBackslash = false;
		}
	}
};