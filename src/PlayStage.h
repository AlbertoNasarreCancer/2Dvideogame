#pragma once
#include "Stage.h"
#include "Level.h"




class PlayStage : public Stage {
public:
	enum { FACE_DOWN, FACE_RIGHT, FACE_LEFT, FACE_UP };
	PlayStage() ;
	
	static std::vector<level*> level_list;
	static level* current_level;
	void render(Image& Fb,float time, GameMap3& map, Vector2& camera_movenemt);
	void update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed);
	//static void ChangeState(const char* state);
	float player_speed;
	static void changelevel();
	void CheckWin();
	Vector2 objetive_movement;
	Vector2 objetive_movement_colision;
	int facing = FACE_DOWN;
	static int current_level_id;
	int test;

	static void Reiniciar();
	static void savegame();
	static void LoadGame();
	static void EditGame();
	void SaveMap();
};