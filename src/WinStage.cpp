#include "WinStage.h"
#include "Game.h"


enum { PLAY, EXIT };
int _winstate = PLAY;

void WinStage::render(Image& Fb, float time, GameMap3& map, Vector2& camera_movenemt) {
	Image* font = Image::Get("data/bitmap-font-white.tga");
	Fb.fill(Color(0, 255, 0));
	Fb.drawText("You finish the game!", 75, 18, *font);
	Fb.drawText("Play Again", 100, 98, *font);
	Fb.drawText("Exit", 100, 128, *font);
	//Fb.drawText("Hello World", 90, 128, *font);
	if (_winstate == PLAY) {
		Fb.drawText(">>>", 70, 98, *font);
	}
	else
	{
		Fb.drawText(">>>", 70, 128, *font);
	}

}

void WinStage::update(Vector2& camera_movenemt, GameMap3& map, double seconds_elapsed) {
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
		//ChangeState("Play");
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_UP)) {

		Game::instance->synth.playSample("data/select.wav", 1, false);
		if (_winstate == PLAY)
		{
			_winstate = EXIT;

		}
		else { _winstate = PLAY; }
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_DOWN)) {

		Game::instance->synth.playSample("data/select.wav", 1, false);
		if (_winstate == PLAY)
		{
			_winstate = EXIT;

		}
		else { _winstate = PLAY; }

	}
	if (Input::wasKeyPressed(SDL_SCANCODE_RETURN)) {

		if (_winstate == PLAY) {ChangeState("intro"); }
		else { Game::instance->must_exit = true; }

	}
}
