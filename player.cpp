#include<iostream>
#include<string>
#include<vector>
#include "item.h"
#include "object.h"
#include "player.h"
using namespace std;


Player::~Player()
{
}

Player::Player(string name, string description, Room* pStart, bool playGame, bool isElectricityOn) :Object(name, description),
pLoc(pStart),
stillPlaying(playGame),
electricityOn(isElectricityOn)
{}


void Player::showInventory()
{
	vector<Item*>::iterator iter;
	iter = m_inventory.begin();

	if(m_inventory.size() == 0)
			cout << "Inventory is EMPTY." << endl;
	else
	{
		cout << "----- Inventory -----" << endl;
		for (iter; iter != m_inventory.end(); ++iter)
		{
				cout << (*iter)->getName() << endl;
		}
	}
}

void Player::getItem()
{
	if (m_inventory.size() > 1)
		cout << "Inventory is full." << endl;
	else if (pLoc->getInventory().size() == 0)
		cout << "Nothing appears useful." << endl;
	// if only one item in room, get it
	else if (pLoc->getInventory().size() == 1)
	{
		m_inventory.push_back(pLoc->getInventory()[0]);
		cout << "Got " << pLoc->getInventory()[0]->getName() << endl;
		pLoc->getInventory().clear();
	}
	else
	{
		int i = 1;
		int item = 0;
		vector<Item*>::iterator iter = pLoc->getInventory().begin();
		for (iter; iter != pLoc->getInventory().end(); ++iter)
		{
			cout << i << ":" << (*iter)->getName() << endl;
			++i;
		}
		cout << i << ":Cancel" << endl;
		cout << "Which item to get?(1-" << --i << ")\n>";
		cin >> item;
		if (item < 1 || item > i)
			cout << "Did not get anything." << endl;
		else
		{
			m_inventory.push_back(pLoc->getInventory()[item - 1]);
			cout << "Got " << pLoc->getInventory()[item - 1]->getName() << endl;
			pLoc->getInventory().erase(pLoc->getInventory().begin() + (item - 1));
		}

	}
	

}

void Player::dropItem()
{
	if (m_inventory.size() == 0)
		cout << "Inventory is EMPTY." << endl;
	else if (m_inventory.size() == 1)
	{
		pLoc->getInventory().push_back(m_inventory[0]);
		cout << "Dropped " << m_inventory[0]->getName() << endl;
		m_inventory.clear();
	}
	else
	{
		int item = 0;
		cout << "1:" << m_inventory[0]->getName() << endl;
		cout << "2:" << m_inventory[1]->getName() << endl;
		cout << "3:Cancel" << endl;
		cout << "Drop which item?(1 or 2)\n>";

		cin >> item;
		if (item == 1 || item == 2)
		{
			vector<Item*>::iterator iter = m_inventory.begin();
			cout << "Dropped " << m_inventory[item - 1]->getName() << endl;
			pLoc->getInventory().push_back(m_inventory[item - 1]);
			m_inventory.erase(iter + (item - 1));
		}
		else
		{
			cout << "Did not drop anything." << endl;
		}

	}

}

void Player::findLockedRoom()
{
	char checkRoom[] = { 'n', 's', 'e', 'w', 'u', 'd' };
	for (int i = 0; i < 6; ++i)
	{
		if (pLoc->getRoom(checkRoom[i]) == NULL) {}
		else if (pLoc->getRoom(checkRoom[i])->isRoomLocked())
		{
			pLoc->getRoom(checkRoom[i])->unlockRoom();
			break;
		}
	}
}

void Player::useItem()
{
	// if room has lock, check if right item
	
	// if it is, unlock room
	if (m_inventory.size() == 0)
		cout << "No item to use." << endl;
	else if (m_inventory.size() == 1)
	{
		if (m_inventory[0]->getName() == "Fuel Can" && pLoc->getName() == "Storage Room")
		{
			if (m_inventory[0]->getIsFull())
				cout << "Fuel Can is already full." << endl;
			else { m_inventory[0]->fillContainer(); cout << "Filled Fuel Can" << endl; }
		}
		// check if it is room key
		else if (pLoc->getName() == "Hangar")
		{
			if (m_inventory[0]->getIsFull() && m_inventory[0]->getName() == "Fuel Can")
			{
				findLockedRoom();
				cout << "Used " << m_inventory[0]->getName() << endl;
				m_inventory[0]->emptyContainer();
			}
			else if(m_inventory[0]->getName() == "Fuel Can")
			{
				cout << "Fuel Can is empty." << endl;
			}
			else
				cout << "Cannot use " << m_inventory[0]->getName() << " here." << endl;
				
			
		}
		else if (m_inventory[0]->getName() == "Lever" && pLoc->getName() == "Engine Room") { m_inventory.clear(); changeElectricity(); cout << "Used Lever\nThe power is now off.\nRemoved Lever from inventory" << endl; }
		else if (m_inventory[0] == pLoc->getRoomKey())
		{
			if (pLoc->getName() == "Fence Perimeter" && m_inventory[0]->getName() == "Bolt Cutters" && electricityOn) { cout << "Cannot use " << m_inventory[0]->getName() << endl; }

			else
			{
				findLockedRoom();
				cout << "Used " << m_inventory[0]->getName() << endl;

				if (m_inventory[0]->getName() == "Propeller")
				{
					m_inventory.clear();
					cout << "Removed Propeller from inventory" << endl;
				}
			}
		}
		else
					cout << "Cannot use " << m_inventory[0]->getName() << " here." << endl;
	}
	else
	{
		int item = 0;
		cout << "1:" << m_inventory[0]->getName() << endl;
		cout << "2:" << m_inventory[1]->getName() << endl;
		cout << "3:Cancel" << endl;
		cout << "Use which item?(1 or 2)\n>";

		cin >> item;
		if (item == 1 || item == 2)
		{
			if (m_inventory[item - 1]->getName() == "Fuel Can" && pLoc->getName() == "Storage Room") 
			{ 
				if (m_inventory[item - 1]->getIsFull()) { cout << "Fuel Can is already full."; }
				else
				{
					m_inventory[item - 1]->fillContainer();
					cout << "Filled Fuel Can";
				}
				
			}
			else if (pLoc->getName() == "Fence Perimeter" && m_inventory[item -1]->getName() == "Bolt Cutters" && electricityOn) { cout << "Cannot use " << m_inventory[item - 1]->getName() << endl; }
			else if (m_inventory[item - 1]->getName() == "Lever" && pLoc->getName() == "Engine Room")
			{
				m_inventory.erase(m_inventory.begin() + (item - 1)) ; 
				changeElectricity();
				cout << "Used Lever\nPower is now off.\nRemoved Lever from inventory" << endl;
			}
			else if (pLoc->getName() == "Hangar")
			{
				if (m_inventory[item - 1]->getIsFull() && m_inventory[item - 1]->getName() == "Fuel Can")
				{
					findLockedRoom();
					cout << "Used " << m_inventory[item - 1]->getName() << endl;
					m_inventory[item - 1]->emptyContainer();
				}
				else if(m_inventory[item - 1]->getName() == "Fuel Can" )
				{
					cout << "Fuel Can is empty." << endl;
				}
				else
				{
					cout << "Cannot use " << m_inventory[item - 1]->getName() << " here." << endl;
				}
			}
			else if (m_inventory[item - 1] == pLoc->getRoomKey())
			{
				findLockedRoom();
				cout << "Used " << m_inventory[item - 1]->getName() << endl;
				if (m_inventory[item - 1]->getName() == "Propeller")
				{
					m_inventory.erase(m_inventory.begin() + (item - 1));
					cout << "Removed Propeller from inventory" << endl;
				}
				
			}
			else
				cout << "Cannot use " << m_inventory[item - 1]->getName() << " here." << endl;
		}
		else
			cout << "Did not use anything." << endl;
	}
}

void Player::setLocation(Room* room)
{
	pLoc = room;
}

void Player::simpleParser(char command)
{
	// show help
	if (command == 'h' || command == 'H')
		showHelp();
	// show inventory
	else if (command == 'i' || command == 'I')
		showInventory();
	// quit game
	else if (command == 'q' || command == 'Q')
		quitGame();
	// get item
	else if (command == 'g' || command == 'G')
		getItem();	// either parse another argument, or list room items
	// drop item
	else if (command == 'r' || command == 'R')
		dropItem();
	// look
	else if (command == 'l' || command == 'L')
		lookAround();
	// go
	else if (command == 'n' || command == 'N'
		|| command == 's' || command == 'S'
		|| command == 'e' || command == 'E'
		|| command == 'w' || command == 'W'
		|| command == 'u' || command == 'U'
		|| command == 'd' || command == 'D')
		getDirection(command);
	// use item
	else if (command == 'a' || command == 'A')
		useItem();
	else
		cout << "Command not recognized." << endl;
}


void Player::getDirection(char dir)
{
	
	if (pLoc->getRoom(dir) == NULL)
	{
		cout << "Nothing of interest over there." << endl;
	}
	else if (pLoc->getRoom(dir)->getName() == "Airfield" && electricityOn)
	{ 
			cout << "Fence is electrified. Better keep a safe distance from it." << endl;
	}	
	else if (pLoc->getRoom(dir)->isRoomLocked())
		
	{
		cout << pLoc->getRoom(dir)->getName();
		cout << pLoc->getRoom(dir)->getHint();
		cout << pLoc->getName();
	}
	
	else
	{
		setLocation(pLoc->getRoom(dir));
		cout << pLoc->getName() << endl;
		if (pLoc->getName() == "Airplane")
		{
			cout << pLoc->getDescription() << endl;
			stillPlaying = false;
		}
	}
}

Room* Player::getLocation()
{
	return pLoc;
}

void Player::quitGame()		// add member m_running to Game.h, and accessor functions
{
	stillPlaying = false;
}

void Player::showHelp()
{
	cout << " l ... look" << endl;
	cout << " i ... inventory" << endl;
	cout << " g ... get item" << endl;
	cout << " r ... remove item" << endl;
	cout << " a ... use item" << endl;
	cout << " n ... go north" << endl;
	cout << " s ... go south" << endl;
	cout << " e ... go east" << endl;
	cout << " w ... go west" << endl;
	cout << " u ... go up" << endl;
	cout << " d ... go down" << endl;
	cout << " q ... quit" << endl;
	cout << " h ... help" << endl;
}

void Player::lookAround()
{
	cout << pLoc->getDescription() << endl;
	pLoc->showInventory();
	if (pLoc->getName() == "Engine Room")
	{
		cout << "There is a power box here.";
		if (electricityOn) cout << pLoc->getHint();
		cout << endl;
			
	}
	cout << "- ";
	if (pLoc->getRoom('n') != NULL) { cout << "n "; }
	if (pLoc->getRoom('s') != NULL) { cout << "s "; }
	if (pLoc->getRoom('e') != NULL) { cout << "e "; }
	if (pLoc->getRoom('w') != NULL) { cout << "w "; }
	if (pLoc->getRoom('u') != NULL) { cout << "u "; }
	if (pLoc->getRoom('d') != NULL) { cout << "d "; }
	cout << "-\n";
}

bool Player::getGameStatus()
{
	return stillPlaying;
}

void Player::changeElectricity()
{
	electricityOn = !electricityOn;
}

bool Player::getIsElectricityOn()
{
	return electricityOn;
}