#pragma once
#include "Image.h"
#include "player.h"
#include "input.h"
#include "synth.h"
class Stage {



public:
	static std::map<std::string, Stage*> s_stages;
	static Stage* Current_stage;
	Stage(const char* name) { s_stages[name] = this; if (Current_stage == NULL) Current_stage = this;}
	static void ChangeState(const char* state);
	virtual void render(Image& Fb,float time, GameMap3& map, Vector2& camera_movenemt) {}; //empty body
	virtual void update(Vector2& camera_movenemt, GameMap3& map,double seconds_elapsed) {}; //empty body


};

//std::map<std::string, Stage*> Stage::s_stages;
//Stage* Stage::Current_stage = NULL;