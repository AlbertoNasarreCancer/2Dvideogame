

#include "PausaStage.h"
#include "PlayStage.h"
#include "Game.h"

enum { PLAY, EXIT,REINICIA, REINICIA_level,SAVE,LOAD};
int state_pause = PLAY;

int Vector_states[6]= { PLAY, EXIT,REINICIA,REINICIA_level,SAVE,LOAD };
int len_array = sizeof(Vector_states) / sizeof(Vector_states[0]);

void PausaStage::render(Image& Fb, float time, GameMap3& map, Vector2& camera_movenemt) {
	Image* font = Image::Get("data/bitmap-font-white.tga");
	
	//Fb.fill(Color(0, 0, 0));

	Stage::s_stages["Play"]->render(Fb,time,map, camera_movenemt);
	
	
	Fb.drawText("PAUSE", 100, 18, *font);
	Fb.drawText("Play", 100, 68, *font);
	Fb.drawText("Exit", 100, 98, *font);
	Fb.drawText("Restart Game", 100, 128, *font);
	Fb.drawText("Restart Level", 100, 158, *font);
	Fb.drawText("SAVE Game", 100, 188, *font);
	Fb.drawText("LOAD Game", 100, 218, *font);
	
	if (state_pause == PLAY) {
		Fb.drawText(">>>", 70, 68, *font);
	}
	if (state_pause == EXIT)
	{
		Fb.drawText(">>>", 70, 98, *font);
	}
	if (state_pause == REINICIA)
	{
		Fb.drawText(">>>", 70, 128, *font);
	}
	if (state_pause == REINICIA_level) {

		Fb.drawText(">>>", 70, 158, *font);
	}
	if (state_pause == SAVE) {

		Fb.drawText(">>>", 70, 188, *font);
	}
	if (state_pause == LOAD) {

		Fb.drawText(">>>", 70, 218, *font);
	}

}

void PausaStage::update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		//ChangeState("Play");
		//PlayStage::Reiniciar();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) {
		
		Game::instance->synth.playSample("data/select.wav", 1, false);
		
		if (state_pause == Vector_states[0]) { state_pause = Vector_states[len_array - 1]; }else { state_pause = Vector_states[state_pause - 1]; }
	}
	
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) {
		
		Game::instance->synth.playSample("data/select.wav", 1, false);
	
		if (state_pause == len_array - 1) {state_pause = Vector_states[0];}else{state_pause = Vector_states[state_pause + 1];}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {

		if (state_pause == PLAY) {  Stage::ChangeState("Play"); }
		
		else if (state_pause == EXIT) { Game::instance->must_exit = true; }
		
		else if (state_pause == REINICIA) {
			state_pause = PLAY;
			PlayStage::Reiniciar(); 
			ChangeState("intro");
		}
		else if (state_pause == REINICIA_level) { PlayStage::current_level->reiniciarlevel(); state_pause = PLAY; ChangeState("Play");}

		else if (state_pause == SAVE) { PlayStage::savegame(); ChangeState("Play"); }

		else if (state_pause == LOAD) { PlayStage::LoadGame(); ChangeState("Play"); }

	}

	if (Input::wasKeyPressed(SDL_SCANCODE_S)) //if key A was pressed
	{
		
		
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_L)) //if key A was pressed
	{
		
		
	}

}