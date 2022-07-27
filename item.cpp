#include<iostream>
#include<string>
#include"item.h"
using namespace std;

Item::Item(string name, string description, bool setIsFull) :Object(name, description),
isFull(setIsFull)
{}

void Item::fillContainer()
{
	isFull= true;
}
void Item::emptyContainer()
{
	isFull = false;
}

bool Item::getIsFull()
{
	return isFull;
}