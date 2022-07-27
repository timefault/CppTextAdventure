#include<iostream>
#include<string>
#include<vector>
#include"map.h"
#include"room.h"
#include"item.h"

using namespace std;


Map::~Map()
{
	//
	for (vector<Room*>::iterator iter = worldRooms.begin(); iter != worldRooms.end(); ++iter)
	{
		delete *iter;

	}
	for (vector<Item*>::iterator iter = worldItems.begin(); iter != worldItems.end(); ++iter)
	{
		delete *iter;

	}

}

Map::Map()
{
	Room* boat_dock_south = new Room("Boat Dock South", "You are standing on a boat dock.");
	worldRooms.push_back(boat_dock_south);
	

	Room* winding_path = new Room("Winding Path", "You are on a small winding path.");
	worldRooms.push_back(winding_path);
	
	Room* cabin = new Room("Cabin", "You stand in an old wooden cabin.", true, "The door is locked.\n\n");
	worldRooms.push_back(cabin);
	
	Room* kitchen = new Room("Kitchen", "You are in a kitchen.");
	worldRooms.push_back(kitchen);
	
	Room* bedroom = new Room("Bedroom", "You are in a bedroom.");
	worldRooms.push_back(bedroom);
	

	Room* lake = new Room("Lake", "You are on a small lake.", true, "The boat is missing something.\n\n");
	worldRooms.push_back(lake);

	Room* boat_dock_north = new Room("Boat Dock North", "You are standing on a boat dock.");
	worldRooms.push_back(boat_dock_north);

	Room* boat_dock_west = new Room("Boat Dock West", "You are standing on a boat dock.");
	worldRooms.push_back(boat_dock_west);

	Room* boat_dock_east = new Room("Boat Dock East", "You are standing on a boat dock.");
	worldRooms.push_back(boat_dock_east);
	
	Room* camp_area = new Room("Camp Area", "You are at a camping area.");
	worldRooms.push_back(camp_area);

	Room* lake_shore = new Room("Lake Shore", "You stand at the shore of a lake.");
	worldRooms.push_back(lake_shore);
											
	Room* creek_bed = new Room("Creek Bed", "You are near a dry creek bed.");
	worldRooms.push_back(creek_bed);
	

	Room* narrow_path = new Room("Narrow Path", "You are along a narrow path.");
	worldRooms.push_back(narrow_path);

	Room* salvage_yard = new Room("Salvage Yard", "You are in front of a salvage yard.");
	worldRooms.push_back(salvage_yard);
	
	
	Room* shed = new Room("Shed", "You stand in a small storage shed.", true, "The door is chained shut.\n\n");
	worldRooms.push_back(shed);

	Room* tunnel = new Room("Basement Tunnel", "You are in a damp underground tunnel.");
	worldRooms.push_back(tunnel);

	Room* storage_room = new Room("Storage Room", "You stand in room filled with surplus utitlies. There is a drum of fuel here.", true, "The door is locked.\n\n");
	worldRooms.push_back(storage_room);
	

	Room* engine_room = new Room("Engine Room", "You are in a room with an engine that seems to provide electricity.", false, "It is missing something.\n\n");
	worldRooms.push_back(engine_room);

	Room* airfield_gate = new Room("Airfield Gate", "You stand within a small gate house. The gate is locked.");
	worldRooms.push_back(airfield_gate);
	

	Room* fence_perimeter = new Room("Fence Perimeter", "You are along the exterior fence perirmeter of an airfield.");
	worldRooms.push_back(fence_perimeter);
	

	Room* airfield = new Room("Airfield", "You stand on a large airfield.", true, "The fence is blocking your path.\n\n");
	worldRooms.push_back(airfield);

	Room* hangar = new Room("Hangar", "You stand in an airplane hangar.");
	worldRooms.push_back(hangar);

	Room* airplane = new Room("Airplane", "You take off in the airplane.", true, "The airplane won't start. The fuel gauge is pointing at E.\n\n");
	worldRooms.push_back(airplane);


	Item* cabin_key = new Item("Cabin Key", "A small key.");
	boat_dock_south->setItem(cabin_key);
	winding_path->setKey(cabin_key);
	worldItems.push_back(cabin_key);

	Item* propeller = new Item("Propeller", "It looks like this could be used on a boat motor.");
	bedroom->setItem(propeller);
	boat_dock_south->setKey(propeller);
	worldItems.push_back(propeller);

	Item* fuel_can = new Item("Fuel Can", "An old fuel can.");
	creek_bed->setItem(fuel_can);
	storage_room->setKey(fuel_can);
	airplane->setKey(fuel_can);
	worldItems.push_back(fuel_can);

	Item* lever = new Item("Lever", "A mechanical lever.");
	salvage_yard->setItem(lever);
	engine_room->setKey(lever);
	worldItems.push_back(lever);

	Item* storage_room_key = new Item("Storage Room Key", "A key for a door somewhere.");
	airfield_gate->setItem(storage_room_key);
	tunnel->setKey(storage_room_key);
	worldItems.push_back(storage_room_key);

	Item* bolt_cutters = new Item("Bolt Cutters", "A pair of bolt cutters.");	// needs to be used in two places
	fence_perimeter->setItem(bolt_cutters);
	narrow_path->setKey(bolt_cutters);
	fence_perimeter->setKey(bolt_cutters);
	worldItems.push_back(bolt_cutters);


	boat_dock_south->setUpExits(lake, winding_path, NULL, NULL, NULL, NULL);

	winding_path->setUpExits(boat_dock_south, cabin, NULL, NULL, NULL, NULL);

	cabin->setUpExits(winding_path, NULL, bedroom, kitchen, NULL, NULL);

	kitchen->setUpExits(NULL, NULL, cabin, NULL, NULL, NULL);

	bedroom->setUpExits(NULL, NULL, NULL, cabin, NULL, NULL);

	lake->setUpExits(boat_dock_north, boat_dock_south, boat_dock_east, boat_dock_west, NULL, NULL);

	boat_dock_east->setUpExits(NULL, NULL, camp_area, lake, NULL, NULL);

	camp_area->setUpExits(creek_bed, lake_shore, NULL, boat_dock_east, NULL, NULL);

	creek_bed->setUpExits(NULL, camp_area, NULL, NULL, NULL, NULL);

	lake_shore->setUpExits(camp_area, NULL, NULL, NULL, NULL, NULL);

	boat_dock_west->setUpExits(NULL, NULL, lake, narrow_path, NULL, NULL);

	narrow_path->setUpExits(salvage_yard, NULL, boat_dock_west, shed, NULL, NULL);
	
	salvage_yard->setUpExits(NULL, narrow_path, NULL, NULL, NULL, NULL);

	shed->setUpExits(NULL, NULL, narrow_path, NULL, NULL, tunnel);

	tunnel->setUpExits(NULL, NULL, storage_room, NULL, shed, NULL);

	storage_room->setUpExits(NULL, NULL, engine_room, tunnel, NULL, NULL);

	engine_room->setUpExits(NULL, NULL, NULL, storage_room, NULL, NULL);

	boat_dock_north->setUpExits(airfield_gate, lake, NULL, NULL, NULL, NULL);

	airfield_gate->setUpExits(NULL, boat_dock_north, fence_perimeter, NULL, NULL, NULL);

	fence_perimeter->setUpExits(airfield, NULL, NULL, airfield_gate, NULL, NULL);

	airfield->setUpExits(NULL, fence_perimeter, NULL, hangar, NULL, NULL);

	hangar->setUpExits(NULL, NULL, airfield, airplane, NULL, NULL);


	mStart = boat_dock_south;
}


Room* Map::getStart()
{
	return mStart;
}