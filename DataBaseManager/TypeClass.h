#pragma once
#include <string>
#include <fstream>
using namespace std;

class TypeClass
{
public:
	string Name;
	string TypeName;
	int TypeSize;
	int TypeLength;
	TypeClass(string Name, string TypeName, int Length);
	TypeClass(ifstream &InFile);
	bool IsSame(TypeClass *p);
	bool operator == (TypeClass p);
	int Save(ofstream & OutFile);
};

