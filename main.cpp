#include<iostream>
#include<string>
#include<vector>
#include"item.h"
#include"object.h"
#include"player.h"
#include"room.h"
#include"map.h"


using namespace std;

int main()
{
	Map* GameWorld = new Map();
	Player* Player1 = new Player("Roger", "The first player.", GameWorld->getStart());
	
	char command;

	cout << Player1->getLocation()->getName() << endl;
	cout << Player1->getLocation()->getDescription() << endl;

	while (Player1->getGameStatus())
	{
		cout << "\n>";
		cin >> command;

		Player1->simpleParser(command);
	}
	cout << "\nThanks for playing!" << endl;
	delete Player1;
	delete GameWorld;




	
	

	

	system("pause");
	return 0;
}