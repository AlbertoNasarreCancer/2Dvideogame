#include "PlayStage.h"
#include "Game.h"
#include <vector> 
#include <algorithm> 
#include <iostream> 
#include <stdio.h>
#include <string.h>

//data to save game

struct sCharacterInfo {
	Vector2 pos;
	int type;
	int energy;
};

struct sGameInfo {
	sCharacterInfo players[10];
	int num_players;
	int level;
	Vector2 camera_movenemt;
};




//array para los players
Vector2 Array[2]= { Vector2(32,32), Vector2(32,96)};
Vector2 Array2[4] = { Vector2(32,32), Vector2(32,112), Vector2(32,192) };
Vector2 Array3[4] = { Vector2(32,32), Vector2(192,32), Vector2(32,192) , Vector2(192,192) };

//inicializar los niveles
level tutorial(2, Array, "data/testmap.map"); //Tutorial2.map
level level1(2, Array, "data/Level1.map"); 
level level2(3, Array2, "data/Level2.map");
level level3(4, Array3, "data/Level3.map");

//nivel actual
level* PlayStage::current_level;
int PlayStage::current_level_id;

//array de niveles y players

std::vector<level*> PlayStage::level_list;

//void PlayStage::ChangeState(const char* state){ 
	
	//for (std::vector<player*>::iterator i = player_list.begin(); i != player_list.end(); ++i) { (*i)->player_pos = (*i)->initial_position_player; (*i)->energy = 100; Game::instance->camera_movenemt=Vector2(0,0); }
	//Current_stage = s_stages[state];
//}

PlayStage::PlayStage() :Stage("Play") {
	
	current_level_id = 0;
	player_speed = 16;
	//inicializa Primer nivel
	current_level = &tutorial;
	//inicializa los niveles
	level_list.push_back(&tutorial);
	level_list.push_back(&level1);
	level_list.push_back(&level2);
	level_list.push_back(&level3);

	test = 0;

}

void PlayStage::render(Image& Fb, float time, GameMap3& map, Vector2& camera_movenemt) {
	
	Image* minifont = Image::Get("data/tileset.tga");
	
	Fb.fill(Color(128, 128, 0));
	
	int cs = 16; //size in pixels of a cell
	
		//for every cell
	for (int x = 0; x < current_level->map->width; ++x)
		for (int y = 0; y < current_level->map->height; ++y)
		{
			//get cell info
			sCell& cell = current_level->map->getCell(x + camera_movenemt.x, y + camera_movenemt.y);
			if (cell.type == 0) //skip empty
				continue;
			//compute tile pos in tileset image
			int tilex = (cell.type % 16) * (cs); //int tilex = (cell.type % 16) * (cs -test);
			int tiley = floor(cell.type / 16) * cs;
			Area area(tilex, tiley, cs, cs);
			//avoid rendering out of screen stuff
			if (x < -cs || x * cs > Fb.width ||
				y < -cs || y * cs > Fb.height)
				continue;
			//draw area of tileset inside framebuffer
			Fb.drawImage(*minifont, x * cs, y * cs, area);
		}
	// Renderizar cada player del nivel
	for (std::vector<player*>::iterator i = current_level->player_list.begin(); i != current_level->player_list.end(); ++i) { (*i)->drawplayer(Fb, time); }

	test += 1;

	if (test == 16) { test = 0; }
}

void PlayStage::update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed) {
	
	float camera_speed = 1;
	enum { FACE_DOWN, FACE_RIGHT, FACE_LEFT, FACE_UP };
	bool anycolider = false;
	
	//Check Keyprese and move players
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		objetive_movement = Vector2(0, -1);
		facing = FACE_UP;}
	
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		objetive_movement = Vector2(0, 1);
		facing = FACE_DOWN;}
	
	if (Input::wasKeyPressed(SDL_SCANCODE_LEFT)) //if key left
	{
		objetive_movement = Vector2(-1, 0);
		facing = FACE_LEFT;}
	
	if (Input::wasKeyPressed(SDL_SCANCODE_RIGHT)) //if key right
	{
		objetive_movement = Vector2(1, 0);
		facing = FACE_RIGHT;
	}
	if (Input::wasMousePressed(SDL_BUTTON_LEFT)) //if key Z was pressed
	{
		//changelevel();
		//Reiniciar();
		EditGame();
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		//changelevel();
		//Reiniciar();
		SaveMap();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
		ChangeState("Pause");
	}

	
	//Check colisions and move players
	for (std::vector<player*>::iterator i = current_level->player_list.begin(); i != current_level->player_list.end(); ++i) {
		
		//animacion
		(*i)->facing = facing; 

		//checkear muerte
		if ((*i)->energy <= 0) {
			//reset Players position
			current_level->reiniciarlevel();
			Game::instance->vidas -= 1;
			ChangeState("End");
			
		}

		//chekear colisiones del mapa (lava y mas elementos a añadir en el futuro)
		(*i)->checkcolision(camera_movenemt, *current_level->map);
		
		//checkea si hay alguna colision de personajes principales con un muro
		if ((*i)->checkcolision_objetivo(camera_movenemt, objetive_movement, *current_level->map)) { anycolider = true; } 
	
		}
		
		//Mover personajes o camara
		if (!anycolider) {
		
		camera_movenemt += objetive_movement;
		
		}
		else {
		
			for (std::vector<player*>::iterator i = current_level->player_list.begin(); i != current_level->player_list.end(); ++i) {
				if (!(*i)->in_movement) {
				if (!(*i)->checkcolision_objetivo(camera_movenemt, objetive_movement, *current_level->map)) { 
					
					(*i)->objetive_movement = objetive_movement; 
					(*i)->in_movement = true;
				}
				}
				//(*i)->objetive_movement += objetive_movement* player_speed; No funciona **pendiente de revision
			}
			}
	
	objetive_movement = Vector2(0, 0);

	//check win
	CheckWin();
	
	//check Lost game
	if (Game::instance->vidas == 0) {
		Reiniciar();
		current_level_id = 0;
	}
}

void PlayStage::changelevel() {

	current_level->reiniciarlevel();

	std::vector<level*>::iterator it = std::find(level_list.begin(), level_list.end(), current_level);
	
	int objetive = it - level_list.begin() + 1;

	current_level_id = objetive;
	
	if (objetive == level_list.size()) { objetive = 0; ChangeState("Win"); current_level_id = 0;}
	
	if (it != level_list.end())
	{
		current_level = level_list.at(objetive);
	}
	else { std::cout << "Element not found.\n\n"; }

}

void PlayStage::CheckWin(){

	std::vector<Vector2> vectores;

	for (std::vector<player*>::iterator i = current_level->player_list.begin(); i != current_level->player_list.end(); ++i) { (*i)->position_player_cell;
	
	vectores.push_back(Vector2(floor((*i)->position_player_cell.x ), floor((*i)->position_player_cell.y )));
	
	}

	if (std::equal(vectores.begin() + 1, vectores.end(), vectores.begin()))
	{
		Stage::ChangeState("Play"); Game::instance->synth.playSample("data/win.wav", 1, false); 
		changelevel();
	}


}

void PlayStage::Reiniciar() {

	current_level->reiniciarlevel();

	current_level = level_list.at(0);

	current_level->reiniciarlevel();

}


void PlayStage::savegame() {
//data to save game

sGameInfo game_info;

game_info.level = current_level_id;
game_info.num_players = current_level->num_players;
game_info.camera_movenemt = Game::instance->camera_movenemt;

for (int i = 0; i < game_info.num_players; i++) {
	
	sCharacterInfo player;
	player.pos = current_level->player_list.at(i)->player_pos;
	player.energy = current_level->player_list.at(i)->energy;
	
	game_info.players[i] = player;
}

// Save to a file

FILE* fp = fopen("savegame.bin", "wb");
fwrite(&game_info, sizeof(sGameInfo), 1, fp);
fclose(fp);


}

void PlayStage::LoadGame() {

	sGameInfo game_info;

	//load file
	FILE* fp = fopen("savegame.bin", "rb");
	if (fp == NULL) { std::cout << "No se puedo abrir el fichero" << "\n"; return; } //no savegame found
		
	std::cout << "Loaded" << "\n";

	fread(&game_info, sizeof(sGameInfo), 1, fp);
	fclose(fp);

	//transfer data from game_info to Game
	//…
	current_level->reiniciarlevel();
	current_level = level_list.at(game_info.level);
	current_level->reiniciarlevel();
	
	//current_level->num_players = game_info.num_players;
	Game::instance->camera_movenemt = game_info.camera_movenemt;
	int ii = 0;
	
	for (std::vector<player*>::iterator i = current_level->player_list.begin(); i != current_level->player_list.end(); ++i) { 
		
		(*i)->player_pos = game_info.players[ii].pos;
		ii++;
	}

	
	

}

void PlayStage::EditGame(){


	Vector2 position = Vector2(Input::mouse_position.x, Input::mouse_position.y);

	sCell cell = current_level->map->getCell(13, 13);

	std::cout << Game::camera_movenemt.x << "   "<< Game::camera_movenemt.y;

	cell.type = 24;

	int x = Game::camera_movenemt.x;
	int y = Game::camera_movenemt.y;

	current_level->map->data[((int)floor(position.x/32)+x) + ((int)floor(position.y / 32)+y) * current_level->map->width].type = 24;

}

void PlayStage::SaveMap() {

	struct sMapHeader {
		int w;
		int h;
		unsigned char bytes;
		unsigned char extra[7];
	};

	sMapHeader header;

	header.w = 32;
	header.h = 32;
	header.bytes = 1;

	
	const char* hola = current_level->direccion;

	char strt[80];
	strcpy(strt, "newLevel/");
	strcat(strt, hola);

FILE* fp = fopen(strt, "wb");
fwrite(&header, sizeof(sMapHeader), 1, fp);
//fwrite(&current_level->map->data, sizeof(current_level->map->data), 1, fp);
int type;
int width = header.w;
int height = header.h;

//girar mapa

//for (int x = 0; x < width; x++){
//	for (int y = 0; y < height; y++){
//		type = current_level->map->getCell(x, y).type;
//		fwrite(&type, sizeof(unsigned char), 1, fp);
//	}
//}

for (int x = 0; x < width; x++) {
	for (int y = 0; y < height; y++) {
		type = current_level->map->getCell(y, x).type;
		fwrite(&type, sizeof(unsigned char), 1, fp);
	}
}

fclose(fp);



std::cout << strt <<  std::endl;

}