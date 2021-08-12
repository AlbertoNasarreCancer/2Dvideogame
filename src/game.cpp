#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"

#include <cmath>
#include "Header.h"
#include "player.h"
#include "IntroStage.h"
#include "PlayStage.h"
#include "Endstage.h"
#include "PausaStage.h"
#include "WinStage.h"

#include <string>
#include <sstream>

// patch porque el to_string no funciona
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}
Game* Game::instance = NULL;
Vector2 Game::camera_movenemt = Vector2(0,0);

//Image font;
Image minifont;
Image sprite;
Color bgcolor(130, 80, 100);

GameMap3 map(128, 128);



Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;
	vidas = 3;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	test = 0;
	
	
	//enable audio staff
	
	enableAudio(); 
	
	playback =synth.playSample("data/Lounge_Game1.wav", 0, true);
	playback_win = synth.playSample("data/Victoy_short.wav", 0, true);
	
	//inicializate stage

	new IntroStage();
	new PlayStage();
	new EndStage();
	new PausaStage();
	new WinStage();
	
}

//what to do when the image has to be draw
void Game::render(void)
{
	Image* font = Image::Get("data/bitmap-font-white.tga");
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer(256, 256); 
	// Render
	Stage::Current_stage->render(framebuffer,time,map, camera_movenemt);
	//framebuffer.drawImage(sprite, 128-camera_movenemt.x*15+time*3, 128-camera_movenemt.y*15+time*3, Area((int(0 * 15) % 4) * 14, 0 * 18, 14, 18));
	// print lives
	framebuffer.drawText( "Vidas:"+ patch::to_string(vidas), 200, 10, *font );
	//send image to screen
	showFramebuffer(&framebuffer);
}

void Game::update(double seconds_elapsed)
{
	
	Stage::Current_stage->update(camera_movenemt,map, seconds_elapsed);
	
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static Image finalframe;

	if (window_width < img->width * 4 || window_height < img->height * 4)
	{
		finalframe = *img;
		finalframe.scale( window_width, window_height );
	}
	else
	{
		if (finalframe.width != window_width || finalframe.height != window_height)
		{
			finalframe.resize(window_width, window_height);
			finalframe.fill(Color::BLACK);
		}
		finalframe.drawImage(*img, (window_width - img->width * 4) * 0.5, (window_height - img->height * 4) * 0.5, img->width * 4, img->height * 4);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (1) //flip
	{
		glRasterPos2f(-1, 1);
		glPixelZoom(1, -1);
	}

	glDrawPixels(finalframe.width, finalframe.height, GL_RGBA, GL_UNSIGNED_BYTE, finalframe.pixels); //glDrawPixels(finalframe.width-1, finalframe.height, GL_RGBA, GL_UNSIGNED_BYTE, finalframe.pixels);

	test += 1;

	if (test == 3) { test = 0; }
}

//AUDIO STUFF ********************

SDL_AudioSpec audio_spec;

void AudioCallback(void*  userdata,
	Uint8* stream,
	int    len)
{
	static double audio_time = 0;

	memset(stream, 0, len);//clear
	if (!Game::instance)
		return;

	Game::instance->onAudio((float*)stream, len / sizeof(float), audio_time, audio_spec);
	audio_time += len / (double)audio_spec.freq;
}

void Game::enableAudio()
{
	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.freq = 48000;
	audio_spec.format = AUDIO_F32;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = AudioCallback; /* you wrote this function elsewhere. */
	if (SDL_OpenAudio(&audio_spec, &audio_spec) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

void Game::onAudio(float *buffer, unsigned int len, double time, SDL_AudioSpec& audio_spec)
{
	//fill the audio buffer using our custom retro synth
	synth.generateAudio(buffer, len, audio_spec);
}
