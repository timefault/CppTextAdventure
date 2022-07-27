// base object class
#pragma once
#include<iostream>
#include<string>
#include<vector>
using std::string;
using std::vector;

class Object
{
protected:
	string m_name;
	string m_description;			// is there a good way to initialize the vector for many objects

public:
	Object(string name, string description);
	string virtual getName();
	string virtual getDescription();

};