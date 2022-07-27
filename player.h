#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"item.h"
#include"object.h"
#include"room.h"
using namespace std;

class Player : public Object
{
public:
	~Player();
	Player(string name, string description, Room* pStart, bool playGame=true, bool isElectricityOn = true);
	void showInventory();
	void lookAround();
	void showHelp();

	void getItem();
	void dropItem();
	void findLockedRoom();
	void useItem();
	

	void simpleParser(char);
	void getDirection(char);
	void setLocation(Room*);

	Room* getLocation();

	void quitGame();
	bool getGameStatus();

	void changeElectricity();
	bool getIsElectricityOn();


private:
	vector<Item*> m_inventory;
	Room* pLoc;
	bool stillPlaying;
	bool electricityOn;
};