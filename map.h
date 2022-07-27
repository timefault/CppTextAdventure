#pragma once

#include<iostream>
#include<string>
#include<vector>
#include"room.h"
#include"item.h"

using namespace std;

class Map
{
public:
	Map();
	~Map();

	Room* getStart();

private:
	Room * mStart;
	vector<Item*> worldItems;
	vector<Room*> worldRooms;
};