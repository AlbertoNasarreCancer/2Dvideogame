#include "EndStage.h"
#include "Game.h"


//std::map<std::string, Stage*> Stage::s_stages;
//Stage* Stage::Current_stage = NULL;
enum{PLAY,EXIT};
int state_end = PLAY;
int alive = true;
void EndStage::render(Image& Fb, float time, GameMap3& map, Vector2& camera_movenemt) {

	if (Game::instance->vidas == 0) { alive = false; }

	

	

	Fb.fill(Color(255, 0, 0));
	Image* font = Image::Get("data/bitmap-font-white.tga");
	if(alive) {
	Fb.drawText("You are dead!!", 75, 18, *font);
	}else{ Fb.drawText("GAME OVER", 75, 18, *font); }
	if (alive) {
	Fb.drawText("Come Back!", 100, 98, *font);
	}
	else { Fb.drawText("Play again", 100, 98, *font); }
	Fb.drawText("Exit", 100, 128, *font);
	//Fb.drawText("Hello World", 90, 128, *font);
	if (state_end == PLAY) {
		Fb.drawText(">>>", 70, 98, *font);
	}
	else
	{
		Fb.drawText(">>>", 70, 128, *font);
	}
}

void EndStage::update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		//ChangeState("Play");
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) {
		Game::instance->synth.playSample("data/select.wav", 1, false);
		if (state_end == PLAY)
		{
			state_end = EXIT;

		}
		else { state_end = PLAY; }
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) {
		Game::instance->synth.playSample("data/select.wav", 1, false);

		if (state_end == PLAY)
		{
			state_end = EXIT;

		}
		else { state_end = PLAY; }

	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {

		if (state_end == PLAY) { 
			
			if (alive) {
				
				ChangeState("Play");
			}else{ 
				Game::instance->vidas = 3;
				alive = true;
				ChangeState("intro"); }
		}else { Game::instance->must_exit = true; }
		
		

	}


}