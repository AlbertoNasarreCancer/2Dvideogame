#include "Game.h"
#include "Stage.h"
#include "PlayStage.h"
#include "PausaStage.h"

void Stage::ChangeState(const char* state) {
	


	if (state == "Play") {

		Game::instance->playback->volume = 1; 

		// Haz play de la moneda solo si vienes de la clase play PausaStage

		if (typeid(*Current_stage).name() == typeid(PausaStage).name()) {

			Game::instance->synth.playSample("data/coin.wav", 1, false);
		}
		

}
	if (state == "Pause") {
	
		
		// Haz play de la moneda solo si vienes de la clase play PlayStage
		
		if (typeid(*Current_stage).name() == typeid(PlayStage).name()) {

			Game::instance->synth.playSample("data/coin.wav", 1, false);
		}
		
		Game::instance->playback->volume = 0.2;
	}
	if (state == "End") {
		if(Game::instance->vidas == 0){
			Game::instance->playback->volume = 0;
		}else{
			Game::instance->playback->volume = 0.2;
		}
	}

	if (state == "Win") {

		Game::instance->playback_win->volume = 1;  
		
		Game::instance->playback->volume = 0;
	
	
	}

	if (state == "intro") {
	
		Game::instance->playback->volume = 0; 
		
		Game::instance->playback_win->volume = 0;
	
	}

	//Game::instance->playback->volume = 0.2;
	Current_stage = s_stages[state];
}