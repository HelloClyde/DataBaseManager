#include "TypeClass.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include "FIleOperate.h"

using namespace std;

TypeClass::TypeClass(string Name, string TypeName, int Length)
{
	this->Name = Name;
	this->TypeName = TypeName;
	if (TypeName == "char") {
		this->TypeSize = sizeof(char);
	}
	else if (TypeName == "float") {
		this->TypeSize = sizeof(float);
	}
	else if (TypeName == "int") {
		this->TypeSize = sizeof(int);
	}
	else if (TypeName == "datetime") {
		this->TypeSize = 10;//For example:2008-01-01
	}
	else {
		throw "Not Support TypeName.";
	}
	this->TypeLength = Length*this->TypeSize;
}

TypeClass::TypeClass(ifstream &InFile)
{
	//Name
	this->Name = GetString(InFile);
	//TypeName
	this->TypeName = GetString(InFile);
	//TypeSize
	InFile.read((char *)&this->TypeSize, sizeof(this->TypeSize));
	//TypeLength
	InFile.read((char *)&this->TypeLength, sizeof(this->TypeLength));
}


bool TypeClass::IsSame(TypeClass *p) {
	if (p->Name == this->Name &&
		p->TypeName == this->TypeName &&
		p->TypeSize == this->TypeSize &&
		p->TypeLength == this->TypeLength)
		return true;
	else
		return false;
}

bool TypeClass::operator==(TypeClass p)
{
	return this->IsSame(&p);
}

int TypeClass::Save(ofstream &OutFile) {
	//Name
	OutFile << this->Name << '\0';
	//TypeName
	OutFile << this->TypeName << '\0';
	//TypeSize
	OutFile.write((char *)&this->TypeSize, sizeof(this->TypeSize));
	//TypeLength
	OutFile.write((char *)&this->TypeLength, sizeof(this->TypeLength));
	return 0;
}
