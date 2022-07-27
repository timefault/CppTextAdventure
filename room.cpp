#include<iostream>
#include<string>
#include"item.h"
#include"room.h"
using namespace std;

Room::Room(string name, string description, bool Locked, string hint, Item* key):Object(name, description),
isLocked(Locked),
m_hint(hint)
{}

void Room::setItem(Item* itemToSet)
{
	m_inventory.push_back(itemToSet);
}

void Room::setKey(Item* key)
{
	roomKey = key;
}

Item* Room::getRoomKey()
{
	return roomKey;
}

void Room::showInventory()
{
	vector<Item*>::iterator iter;
	iter = m_inventory.begin();
	if (m_inventory.size() == 0)
	{
		if (m_name == "Storage Room" || m_name == "Engine Room") {}
		else
		cout << "Nothing appears useful." << endl;
	}
		
	else if (m_name == "Engine Room")
	{

	}
	else
	{
		for (iter; iter != m_inventory.end(); ++iter)
		{
			if ((*iter)->getName() == "Bolt Cutters")
				cout << "There are " << (*iter)->getName() << " here." << endl;
			else if ((*iter)->getName() == "Fuel Can (Full)")
				cout << "Ther is Fuel here." << endl;
			else
				cout << "There is a " << (*iter)->getName() << " here." << endl;
		}
	}
}


vector<Item*>& Room::getInventory()
{
	return m_inventory;
}

Room* Room::getRoom(char  dir)
{
	if (dir == 'n' || dir == 'N')
		return pNorth;
	else if (dir == 's' || dir == 'S')
		return pSouth;
	else if (dir == 'e' || dir == 'E')
		return pEast;
	else if (dir == 'w' || dir == 'W')
		return pWest;
	else if (dir == 'u' || dir == 'U')
		return pUp;
	else if (dir == 'd' || dir == 'D')
		return pDown;
	else
	{
		cout << "Not a valid direction" << endl;
		return NULL;
	}

}


bool Room::isRoomLocked()
{
	return isLocked;
}

void Room::unlockRoom()
{
	isLocked = false;
}

void Room::setUpExits(Room* N, Room* S, Room* E, Room* W, Room* U, Room* D)
{
	pNorth = N;
	pSouth = S;
	pEast = E;
	pWest = W;
	pUp = U;
	pDown = D;
}

string Room::getHint()
{
	cout << endl;
	return m_hint;
}