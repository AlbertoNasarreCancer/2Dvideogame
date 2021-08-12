#pragma once
#include "Stage.h"

class PausaStage : public Stage {
public:
	PausaStage() :Stage("Pause") {}
	void render(Image& Fb, float time, GameMap3& map, Vector2& camera_movenemt);
	void update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed);
	//static void ChangeState(const char* state) { Current_stage = s_stages[state]; }
}; 
