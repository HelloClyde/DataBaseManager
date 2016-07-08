#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "TableClass.h"
#include "DBClass.h"
#include "TypeClass.h"

using namespace std;

vector<string> Analysis(char *Code);
bool IsNum(string Str);
void ShowStrArray(vector<string> StrVec);
vector<string> SelectFromWhere(int mode,int Index,vector<string> &SQLSen);
vector<char*> And(vector<char*> a, vector<char*> b);
vector<char*> Where(int Index,vector<string> &SQLSen,TableClass *Table);

DBClass MainDataBase = DBClass();//DBClass MainDataBase()只会调用隐式的构造函数

int main(int args, char **argc) {
	cout << "DataBaseManager Debug Ver." << endl;
	if (args == 1) {
		cout << "This program needs a  parameter which is the name of SQL code file which you want to execute." << endl;
		cout << "For example:DataBaseManager SQLCode.txt" << endl << endl;
		cout << "Press any key to exit." << endl;
		system("pause");
		getchar();
	}
	else {
		
		MainDataBase.Load();
		ifstream SQLFile;
		SQLFile.open(argc[1]);
		char FileChars[10000];
		SQLFile.getline(FileChars, 10000, 0);
		SQLFile.close();
		vector<string> FileArray = Analysis(FileChars);
		for (int i = 0; i < FileArray.size(); i++) {
			if (FileArray[i] == "go") {//save database
				continue;
			}
			else if (FileArray[i] == "create") {//create table
				i++;
				if (FileArray[i] == "table") {
					i++;
					string TableName = FileArray[i];
					vector<TypeClass> TempVec;
					vector<string> Keys;
					i++;//ignore "("
					while (true) {
						if (FileArray[i + 1] == "primary" && FileArray[i + 2] == "key") {//Get PrimaryKey
							i += 4;
							while (FileArray[i] != ")") {
								Keys.push_back(FileArray[i]);
								i++;
								if (FileArray[i] == ",") {
									i++;
								}
							}
						}
						else {
							string TypeName, TypeType;
							int TypeLength;
							i++;
							TypeName = FileArray[i];
							i++;
							TypeType = FileArray[i];
							if ((FileArray[i + 1]) == "(") {
								TypeLength = atoi(FileArray[i + 2].data());
							}
							else {
								TypeLength = 1;
							}
							TypeClass TempType(TypeName, TypeType, TypeLength);
							TempVec.push_back(TempType);
							//ignore not null
						}
						while (!(FileArray[i] == "," || FileArray[i] == "\n")) {
							i++;
						}
						if (FileArray[i] == "\n") {
							break;
						}
					}
					TableClass TempTable(TableName, TempVec);

					for (string str : Keys) {
						TempTable.SetPrimaryKey(str);
					}
					MainDataBase.AddTable(TempTable);
				}
				else {
					//Noting
				}
			}
			else if (FileArray[i] == "insert") {
				i++;
				if (FileArray[i] == "into") {
					i++;
					string TableName = FileArray[i];
					i += 3;
					vector<string> TempVec;
					while (FileArray[i] != ")") {
						if (FileArray[i] != ",") {
							TempVec.push_back(FileArray[i]);
						}
						i++;
					}
					char ** StrArray = (char **)malloc(TempVec.size() * sizeof(char *));
					for (int i = 0; i < TempVec.size(); i++) {
						StrArray[i] = (char*)malloc(TempVec[i].length() + 1);
						strcpy(StrArray[i], TempVec[i].data());
					}
					TableClass *TableClassP;
					TableClassP = MainDataBase.FindTable(TableName);
					TableClassP->Insert(TempVec.size(), StrArray);
				}
			}
			else if (FileArray[i] == "drop") {//delete table
				i++;
				if (FileArray[i] == "table") {
					i++;
					int Result = MainDataBase.DelTable(FileArray[i]);
					if (Result == -1) {
						cout << "error happens when delete table." << endl;
					}
					else {
						//Nothing
					}
				}
				else {
					//Nothing
				}
			}
			else if (FileArray[i] == "select") {
				SelectFromWhere(1, i, FileArray);
				while (FileArray[i] != "\n") {
					i++;
				}
			}
			else {
				//Nothing
			}
		}
		MainDataBase.Save();
	}
	
	return 0;
}

vector<string> Analysis(char *Code) {
	vector<string> StrArray;
	int StrIndex = 0;
	string *TempStr = new string();
	bool IsStr = false;
	for (int StrIndex = 0; Code[StrIndex]; StrIndex++) {
		char TempChar = Code[StrIndex];
		if (IsStr) {
			if (TempChar == '\'' || TempChar == '"') {
				IsStr = false;
				StrArray.push_back(*TempStr);
				TempStr = new string();
			}
			else {
				//append
				*TempStr += TempChar;
			}
		}
		else {
			if (TempChar == '\'' || TempChar == '"') {
				IsStr = true;
			}
			else {
				if ((TempChar >= 'a' && TempChar <= 'z') ||
					(TempChar >= 'A' && TempChar <= 'Z') ||
					(TempChar >= '0' && TempChar <= '9') ||
					TempChar == '_') {
					*TempStr += TempChar;
				}
				else {
					if (TempStr->length() == 0) {
						//Nothing
					}
					else {
						StrArray.push_back(*TempStr);
						TempStr = new string();
					}
					if (TempChar == ',') {
						StrArray.push_back(",");
					}
					else if (TempChar == '(') {
						StrArray.push_back("(");
					}
					else if (TempChar == ')') {
						StrArray.push_back(")");
					}
					else if (TempChar == '=') {
						StrArray.push_back("=");
					}
					else if (TempChar == '\n') {
						StrArray.push_back("\n");
					}
				}
			}
		}
		
	}
	/*
	for (int i = 0; i < StrArray.size(); i++) {
		cout << StrArray[i] << " ";
	}
	cout << endl;
	*/
	return StrArray;
}

bool IsNum(string Str) {
	for (int i = 0; i < Str.length(); i++) {
		if (!(Str[i] >= '0' && Str[i] <= '9')) {
			return false;
		}
	}
	return true;
}

void ShowStrArray(vector<string> StrVec) {
	for (int i = 0; i < StrVec.size(); i++) {
		cout << StrVec[i] << endl;
	}
}

/*
mode = 1 show result
mode = 0 not show result
Index mean the Index of SQLSen
*/
vector<string> SelectFromWhere(int mode, int Index, vector<string> &SQLSen) {
	vector<string> Des;
	vector<char*>Result;
	int i = Index;
	if (SQLSen[i] == "select") {
		i++;
		string SelectName = SQLSen[i];
		if (SQLSen[i + 1] == "from") {
			i += 2;
			string TableName = SQLSen[i];
			if (SQLSen[i + 1] == "where") {
				i += 2;
				TableClass *DesTable = MainDataBase.FindTable(TableName);
				Result = Where(i, SQLSen, DesTable);
				Des = DesTable->Select(SelectName, Result);
			}
		}
	}
	if (mode == 1) {
		ShowStrArray(Des);
	}
	return Des;
}

vector<char*> Where(int Index, vector<string> &SQLSen, TableClass *Table){
	vector<char*> Des;
	int i = Index;
	string WhereName = SQLSen[i];
	if (SQLSen[i + 1] == "in") {
		Des = Table->WhereIn(WhereName, SelectFromWhere(0, i + 3, SQLSen));
	}
	else if (SQLSen[i + 1] == "=") {
		i += 2;
		string WhereValue = SQLSen[i];
		Des = Table->Where(WhereName, WhereValue);
		if (SQLSen[i + 1] == "and") {
			Des = And(Des, Where(i + 2, SQLSen, Table));
		}
	}
	
	return Des;
}



vector<char*> And(vector<char*> a, vector<char*> b) {
	vector<char*> Des;
	for (int i = 0; i < a.size(); i++) {
		bool IsExist = false;
		for (int j = 0; j < b.size(); j++) {
			if (a[i] == b[j]) {
				IsExist = true;
				break;
			}
		}
		Des.push_back(a[i]);
	}
	return Des;
}