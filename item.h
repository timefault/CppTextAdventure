#pragma once
#include<iostream>
#include<string>
#include "object.h"

using namespace std;

class Item: public Object
{
public:
	Item(string name, string description, bool setIsFull= false);

	void fillContainer();
	void emptyContainer();
	bool getIsFull();

private:
	bool isFull;


};