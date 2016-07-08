#include "FileOperate.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

string GetString(ifstream &InFile) {
	string DesStr;
	char TempChar;
	TempChar = InFile.get();
	while (TempChar != '\0') {
		DesStr.append(&TempChar, 1);
		TempChar = InFile.get();
	}
	return DesStr;
}

bool IsInStr(string StrValue,vector<string> &Vec) {
	for (int i = 0; i < Vec.size(); i++) {
		if (strcmp(StrValue.data(), Vec[i].data()) == 0) {
			return true;
		}
	}
	return false;
}

bool IsInFlo(float Value,vector<string> &Vec) {
	for (int i = 0; i < Vec.size(); i++) {
		if (Value == atof(Vec[i].data())) {
			return true;
		}
	}
	return false;
}

bool IsInInt(int Value, vector<string> &Vec) {
	for (int i = 0; i < Vec.size(); i++) {
		if (Value == atoi(Vec[i].data())) {
			return true;
		}
	}
	return false;
}