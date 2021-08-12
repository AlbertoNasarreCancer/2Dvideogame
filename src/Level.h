#pragma once
#include "player.h"
#include "image.h"
class level {

public:
	
	
	GameMap3* map;
	int num_players;
	Vector2 Array_position_players[10];
	const char* direccion;
	level(int num_players, Vector2 Array_position_players[], const char* direccion);
	std::vector<player*> player_list;
	void reiniciarlevel();

};