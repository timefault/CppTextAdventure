#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"object.h"
#include"item.h"

using namespace std;

class Room : public Object
{
public:
	Room(string, string, bool = false, string = "", Item* = NULL);

	void setItem(Item*);
	void setKey(Item*);

	vector<Item*>& getInventory();

	void showInventory();

	Room* getRoom(char);

	bool isRoomLocked();
	void unlockRoom();

	void setUpExits(Room* N,Room* S,Room* E,Room* W,Room* U,Room* D);

	string getHint();
	Item* getRoomKey();
private:
	vector<Item*> m_inventory;
	bool isLocked;
	string m_hint;
	Item* roomKey;

	Room* pNorth;
	Room* pSouth;
	Room* pEast;
	Room* pWest;
	Room* pUp;
	Room* pDown;
};
