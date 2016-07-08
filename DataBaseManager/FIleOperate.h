#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string GetString(ifstream &InFile);
bool IsInStr(string StrValue, vector<string> &Vec);
bool IsInFlo(float Value, vector<string> &Vec);
bool IsInInt(int Value, vector<string> &Vec);