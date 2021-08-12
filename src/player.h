#pragma once

#include "Image.h"
#include "GameMap3.h"



class player {

public:
	enum { FACE_DOWN, FACE_RIGHT, FACE_LEFT, FACE_UP };
	int facing = FACE_DOWN;
	Vector2 player_pos;
	//Image sprite;
	Vector2 initial_position_player;
	Vector2 position_player_cell;
	int energy;
	const char* direcction_image;
	//void LoadImage(const char);
	player(int x, int y, const char* image);
	void drawplayer(Image& image,float time);
	void checkcolision(Vector2 camera, GameMap3& map); //, GameMap3& map
	bool checkcolision_objetivo(Vector2 camera, Vector2 objetivo, GameMap3& map); //, GameMap3& map
	float check_position_fluence;
	Vector2 objetive_movement;
	bool in_movement;

};