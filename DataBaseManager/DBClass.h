#pragma once
#include <vector>
#include "TableClass.h"
#include <string>

using namespace std;

class DBClass
{
public:
	string DBName;
	vector <TableClass> Tables;
	DBClass(char *Name);
	DBClass();
	~DBClass();
	int AddTable(TableClass SrcTable);
	int DelTable(string TableName);
	TableClass *FindTable(string TableName);
	int Load(char *FileName);
	int Load();
	int Save();
	int Save(char *FileName);
};

