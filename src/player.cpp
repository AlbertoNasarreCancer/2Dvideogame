#include "player.h"
#include <iostream>
#include <cmath>
#include <string>
#include <iostream>
#include <assert.h> 
#include "PlayStage.h"
#include "game.h"



void player::drawplayer(Image& image,float time) {

	Image* sprite = Image::Get(direcction_image);
	image.drawImage(*sprite, player_pos.x, player_pos.y, Area((int(time * 15) % 4) * 14, facing * 18, 14, 18));


}

player::player(int x, int y, const char *image) {

	player_pos.x = x;
	player_pos.y = y;
	//sprite.loadTGA(image);
	energy = 100;
	initial_position_player.x = x;
	initial_position_player.y = y;
	direcction_image = image;

	check_position_fluence = 0;
}

void player::checkcolision(Vector2 camera, GameMap3& map) { //, GameMap3& map

	position_player_cell.x = int(player_pos.x) / 16 + camera.x;//cambiar nombre variable no hay porque usar la camara
	position_player_cell.y = int(player_pos.y) / 16 + camera.y;

	sCell& cell = map.getCell(position_player_cell.x, position_player_cell.y);

	//Check colisions with red

	if (cell.type == 24) { std::cout << energy << std::endl; energy -= 10; Game::instance->synth.playSample("data/hurt.wav", 1, false);}

	//if (energy <=0){ PlayStage::ChangeState("End"); }

	////Intento de suavizar movimiento del personaje
	if (in_movement) {
	player_pos += objetive_movement;

	check_position_fluence = check_position_fluence + 1;

	

		if (check_position_fluence == 16) { check_position_fluence = 0; objetive_movement = Vector2(0, 0); in_movement = false; }
	
	}
}

bool player::checkcolision_objetivo(Vector2 camera, Vector2 objetivo, GameMap3& map) {

	position_player_cell.x = int(player_pos.x) / 16 + camera.x;//cambiar nombre variable no hay porque usar la camara
	position_player_cell.y = int(player_pos.y) / 16 + camera.y;

	sCell& cell2 = map.getCell(position_player_cell.x + objetivo.x, position_player_cell.y + objetivo.y);

	if (cell2.type == 5) { return true; }
	else { return false; }
}

