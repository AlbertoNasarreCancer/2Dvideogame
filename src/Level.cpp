#include "Level.h"
#include "Game.h"


level::level(int num_players, Vector2 Array_position_players[],const char* direccion) {

	this->num_players = num_players;
	map = new GameMap3(32, 32);
	map->loadMap(direccion);
	this->direccion=direccion;
	for (int i = 0; i < num_players; ++i)
		this->Array_position_players[i] = Array_position_players[i];

	for (int i = 0; i < num_players; ++i) {
		player* player0 = new player(Array_position_players[i].x, Array_position_players[i].y, "data/spritesheet.tga");
		player_list.push_back(player0);
	}
}

void level::reiniciarlevel() {


	for (std::vector<player*>::iterator i = player_list.begin(); i != player_list.end(); ++i) { 
		
		(*i)->player_pos = (*i)->initial_position_player; (*i)->energy = 100; (*i)->in_movement = false;
		Game::instance->camera_movenemt = Vector2(0, 0);
}
}