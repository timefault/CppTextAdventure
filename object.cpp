#include<iostream>
#include<string>
#include "object.h"
using std::string;

Object::Object(string name, string description) : 
m_name(name),
m_description(description)
{}

string Object::getName()
{
	return m_name;
}

string Object::getDescription()
{
	return m_description;
}
