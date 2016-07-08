#pragma once
#include <vector>
#include <string>
#include "TypeClass.h"

using namespace std;

class TableClass
{
public:
	string TableName;
	vector<TypeClass> TypeArray;
	int TypeArrayLength;
	vector<TypeClass> PrimaryKey;
	char *Data;//Each Line links by point
	char *LastLine;
	TableClass(string Name,vector<TypeClass> Array);
	TableClass(ifstream &InFile);
	TypeClass *FindType(string Name);
	int SetPrimaryKey(string KeyName);
	int ClearPrimaryKey();
	int CalTypeArrayLength();
	int Insert(int ValuesNum, char ** Values);
	int Save(ofstream &OutFile);
	vector<char*> Where(string TypeName,string TypeValue);
	vector<char*> WhereIn(string TypeName, vector<string> TypeValue);
	vector<string> Select(string TypeName,vector<char *> Where);
};

