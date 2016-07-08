#include "DBClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include "FIleOperate.h"

using namespace std;


DBClass::DBClass(char * Name)
{
	this->DBName = Name;
	//cout << "Create " << this->DBName << endl;
}

DBClass::DBClass()
{
	new(this) DBClass("DefaultDataBase");
}


DBClass::~DBClass()
{
}

int DBClass::AddTable(TableClass SrcTable)
{
	this->Tables.push_back(SrcTable);
	return 0;
}

int DBClass::DelTable(string TableName)
{
	for (int i = 0; i < this->Tables.size(); i++) {
		if (this->Tables[i].TableName == TableName) {
			this->Tables.erase(this->Tables.begin() + i);
			return 0;
		}
	}
	return -1;
}

TableClass * DBClass::FindTable(string TableName)
{
	for (int i = 0; i < this->Tables.size(); i++) {
		if (this->Tables[i].TableName == TableName) {
			return &(this->Tables[i]);
		}
	}
	return nullptr;
}

int DBClass::Load(char* FileName)
{
	ifstream InFile;
	InFile.open(FileName, ios::binary);
	if (!InFile) {
		return -1;
	}
	InFile.seekg(ios::beg);
	//DBName
	this->DBName = GetString(InFile);
	//Vector Size
	int VectorSize;
	InFile.read((char*)&VectorSize, sizeof(VectorSize));
	//Vector Content
	for (int i = 0; i < VectorSize; i++) {
		TableClass* TableClassP = new TableClass(InFile);
		this->Tables.push_back(*TableClassP);
	}
	InFile.close();
	return 0;
}

int DBClass::Load() {
	return this->Load("DefaultDataBase");
}

int DBClass::Save() {
	return this->Save("DefaultDataBase");
}

int DBClass::Save(char* FileName)
{
	ofstream OutFile;
	OutFile.open(FileName, ios::binary|ios::trunc);
	OutFile.seekp(ios::beg);
	//DBName
	OutFile << this->DBName << '\0';
	//Vector Size
	int VectorSize = this->Tables.size();
	OutFile.write((char*)&VectorSize, sizeof(VectorSize));
	//Vector Content
	for (int i = 0; i < VectorSize; i++) {
		TableClass* TableClassP = &(this->Tables[i]);
		TableClassP->Save(OutFile);
	}
	OutFile.close();
	return 0;
}

