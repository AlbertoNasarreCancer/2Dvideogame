#include "IntroStage.h"
#include "Game.h"


std::map<std::string, Stage*> Stage::s_stages;
Stage* Stage::Current_stage = NULL;

enum { PLAY, EXIT};
int state = PLAY;

int Vector_states_int[2] = { PLAY, EXIT };
int len_arrays_int = sizeof(Vector_states_int) / sizeof(Vector_states_int[0]);

void IntroStage::render(Image& Fb,float time, GameMap3& map, Vector2& camera_movenemt){
	Image* font = Image::Get("data/bitmap-font-white.tga");
	Fb.fill(Color(0,0,255));
	Fb.drawText("ALL TOGETHER", 75, 18, *font);
	Fb.drawText("Play", 100, 98, *font);
	Fb.drawText("Exit", 100, 128, *font);
	//Fb.drawText("Hello World", 90, 128, *font);
	if (state == PLAY){
	Fb.drawText(">>>", 70, 98, *font);
	}else
	{Fb.drawText(">>>", 70, 128, *font);
	}

}

void IntroStage::update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed) {
	
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) {

		Game::instance->synth.playSample("data/select.wav", 1, false);

		if (state == Vector_states_int[0]) { state= Vector_states_int[len_arrays_int - 1]; }
		else { state = Vector_states_int[state - 1]; }
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) {

		Game::instance->synth.playSample("data/select.wav", 1, false);

		if (state == len_arrays_int - 1) { state = Vector_states_int[0]; }
		else { state = Vector_states_int[state + 1]; }
	}
	
	
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {
	
		if (state == PLAY) { 
		
		ChangeState("Play");
		
		}
		
		else{ Game::instance->must_exit = true; }
		
	}
}

