#include "TableClass.h"
#include "TypeClass.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string>
#include "FIleOperate.h"

using namespace std;

TableClass::TableClass(string Name, vector<TypeClass> Array)
{
	this->TableName = Name;
	this->TypeArray = Array;
	this->TypeArrayLength = this->CalTypeArrayLength();
	this->Data = nullptr;
	this->LastLine = nullptr;
}

TableClass::TableClass(ifstream & InFile)
{
	//TableName
	this->TableName = GetString(InFile);
	//TypeArraySize
	int TypeArraySize;
	InFile.read((char*)&TypeArraySize, sizeof(TypeArraySize));
	//TypeArraySize
	for (int i = 0; i < TypeArraySize; i++) {
		TypeClass* TypeClassP = new TypeClass(InFile);
		this->TypeArray.push_back(*TypeClassP);
	}
	//TypeArrayLength
	InFile.read((char*)&(this->TypeArrayLength), sizeof(this->TypeArrayLength));
	//Data
	int IsEmpty;
	InFile.read((char*)&IsEmpty, sizeof(IsEmpty));
	if (IsEmpty) {
		this->Data = nullptr;
		this->LastLine = nullptr;
	}
	else {
		this->Data = nullptr;
		while (true) {
			char* p = (char *)malloc(this->TypeArrayLength + sizeof(char *));
			InFile.read(p, this->TypeArrayLength + sizeof(char *));
			if (this->Data == nullptr) {
				this->Data = p;
			}
			else {
				*(char **)(this->LastLine + this->TypeArrayLength) = p;
			}
			this->LastLine = p;
			if (*(char **)(p + this->TypeArrayLength) == nullptr) {
				break;
			}
		}
	}
	
}

TypeClass * TableClass::FindType(string Name)
{
	for (int i = 0; i < this->TypeArray.size(); i++) {
		TypeClass *p;
		p = &(this->TypeArray[i]);
		if (p->Name == Name) {
			return p;
		}
	}
	return nullptr;
}

int TableClass::SetPrimaryKey(string KeyName)
{
	TypeClass *p = this->FindType(KeyName);
	if (p == nullptr) {
		return -1;
	}
	else {
		this->PrimaryKey.push_back(*p);
		return 0;
	}
}

int TableClass::ClearPrimaryKey()
{
	this->PrimaryKey.clear();
	return 0;
}

int TableClass::CalTypeArrayLength()
{
	this->TypeArrayLength = 0;
	for (int i = 0; i < this->TypeArray.size(); i++) {
		TypeClass *p;
		p = &(this->TypeArray[i]);
		this->TypeArrayLength += p->TypeLength;
	}
	return this->TypeArrayLength;
}


int TableClass::Insert(int ValuesNum,char ** Values)
{
	char *p;
	p = (char *)malloc(this->TypeArrayLength + sizeof(char *));
	char *MemP = p;
	for (int i = 0,StrIndex = 0; i < this->TypeArray.size(); i++,StrIndex ++) {
		TypeClass *TypeP;
		TypeP = &(this->TypeArray[i]);
		if (TypeP->TypeName == "char") {
			strcpy(MemP, Values[StrIndex]);
		}
		else if (TypeP->TypeName == "datetime") {
			strcpy(MemP, Values[StrIndex]);
		}
		else if (TypeP->TypeName == "float") {
			float *FloatP = (float *)MemP;
			*FloatP = atof(Values[StrIndex]);
		}
		else if (TypeP->TypeName == "int") {
			int *IntP = (int *)MemP;
			*IntP = atoi(Values[StrIndex]);
		}
		else {
			throw "Not supported TypeName.";
		}
		MemP += TypeP->TypeLength;
	}
	//Next Point
	*(char **)MemP = nullptr;
	if (this->Data == nullptr) {
		this->Data = p;
	}
	else {
		MemP = this->LastLine + this->TypeArrayLength;
		*(char **)MemP = p;
	}
	this->LastLine = p;
	return 0;
}

int TableClass::Save(ofstream &OutFile) {
	//TableName
	OutFile << this->TableName << '\0';
	//TypeArraySize
	int TypeArraySize = this->TypeArray.size();
	OutFile.write((char*)&TypeArraySize, sizeof(TypeArraySize));
	//TypeArraySize
	for (int i = 0; i < TypeArraySize; i++) {
		TypeClass* TypeClassP = &(this->TypeArray[i]);
		TypeClassP->Save(OutFile);
	}
	//TypeArrayLength
	OutFile.write((char*)&(this->TypeArrayLength), sizeof(this->TypeArrayLength));
	//Data
	int IsEmpty;
	if (this->Data == nullptr) {
		IsEmpty = true;
	}
	else {
		IsEmpty = false;
	}
	OutFile.write((char*)&IsEmpty, sizeof(IsEmpty));
	char* p = this->Data;
	while (p != nullptr) {
		OutFile.write(p, this->TypeArrayLength + sizeof(char*));
		p = *(char**)(p + this->TypeArrayLength);
	}
	return 0;
}

vector<char*> TableClass::Where(string TypeName, string TypeValue)
{
	vector<char*> DesVec;
	int TempTypeLength = 0;
	TypeClass* TempType;
	for (int i = 0; i < this->TypeArray.size(); i++) {
		if (this->TypeArray[i].Name == TypeName) {
			TempType = &this->TypeArray[i];
			break;
		}
		else {
			TempTypeLength += this->TypeArray[i].TypeLength;
		}
	}
	char* p = this->Data;
	while (p != nullptr) {
		char *MemP = p + TempTypeLength;
		if (TempType->TypeName == "char" || TempType->TypeName == "datetime") {
			string TempString(MemP, TempType->TypeLength);
			if (strcmp(TempString.data(),TypeValue.data()) == 0) {//string.compare not ignore size,so strcmp is better
				DesVec.push_back(p);
			}
		}
		else if (TempType->TypeName == "float") {
			float *TempF = (float*)MemP;
			if (*TempF == atof(TypeValue.data())) {
				DesVec.push_back(p);
			}
		}
		else if (TempType->TypeName == "int") {
			int *TempI = (int *)MemP;
			if (*TempI == atof(TypeValue.data())) {
				DesVec.push_back(p);
			}
		}
		p = *(char**)(p + this->TypeArrayLength);
	}
	return DesVec;
}

vector<char*> TableClass::WhereIn(string TypeName, vector<string> TypeValue)
{
	vector<char*> DesVec;
	int TempTypeLength = 0;
	TypeClass* TempType;
	for (int i = 0; i < this->TypeArray.size(); i++) {
		if (this->TypeArray[i].Name == TypeName) {
			TempType = &this->TypeArray[i];
			break;
		}
		else {
			TempTypeLength += this->TypeArray[i].TypeLength;
		}
	}
	char* p = this->Data;
	while (p != nullptr) {
		char *MemP = p + TempTypeLength;
		if (TempType->TypeName == "char" || TempType->TypeName == "datetime") {
			string TempString(MemP, TempType->TypeLength);
			if (IsInStr(TempString,TypeValue)) {//string.compare not ignore size,so strcmp is better
				DesVec.push_back(p);
			}
		}
		else if (TempType->TypeName == "float") {
			float *TempF = (float*)MemP;
			if (IsInFlo(*TempF,TypeValue)) {
				DesVec.push_back(p);
			}
		}
		else if (TempType->TypeName == "int") {
			int *TempI = (int *)MemP;
			if (IsInInt(*TempI,TypeValue)) {
				DesVec.push_back(p);
			}
		}
		p = *(char**)(p + this->TypeArrayLength);
	}
	return DesVec;
}

vector<string> TableClass::Select(string TypeName, vector<char*> Where)
{
	vector<string> DesVec;
	int TempTypeLength = 0;
	TypeClass* TempType;
	for (int i = 0; i < this->TypeArray.size(); i++) {
		if (this->TypeArray[i].Name == TypeName) {
			TempType = &this->TypeArray[i];
			break;
		}
		else {
			TempTypeLength += this->TypeArray[i].TypeLength;
		}
	}
	for (int i = 0; i < Where.size(); i++) {
		char *MemP = Where[i] + TempTypeLength;
		if (TempType->TypeName == "char" || TempType->TypeName == "datetime") {
			string TempString(MemP, TempType->TypeLength);
			string TempStr2(TempString.data());
			DesVec.push_back(TempStr2);
		}
		else if (TempType->TypeName == "float") {
			float *TempF = (float*)MemP;
			char TempCharArray[256];
			sprintf(TempCharArray, "%f", *TempF);
			string TempStr(TempCharArray);
			DesVec.push_back(TempStr);
		}
		else if (TempType->TypeName == "int") {
			int *TempI = (int *)MemP;
			char TempCharArray[256];
			sprintf(TempCharArray, "%d", *TempI);
			string TempStr(TempCharArray);
			DesVec.push_back(TempStr);
		}
	}
	return DesVec;
}
