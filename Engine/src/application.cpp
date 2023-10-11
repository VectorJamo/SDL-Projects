#include "game.h"
#include "sprite.h"

bool InitializeSDL()
{
	bool success = true;
	// Initialize SDL Systems
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "Failed to initialize SDL2!" << std::endl;
		success = false;
	}
	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0){
		std::cout << "Failed to initialze SDL_image!" << std::endl;
		success = false;
	}
	if(TTF_Init() == -1){
		std::cout << "Failed to initialize SDL_TTF" << std::endl;;
		success = false;
	}
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1){
		std::cout << "Failed to initialize SDL_Mixer" << std::endl;;		
		success = false;
	}
	return success;	
}
void LimitFps(float& FPS, float& startTime)
{
	float deltaTime = SDL_GetTicks()-startTime;
	float desiredTime = 1000.0f/FPS; 
	if(deltaTime < desiredTime)
		SDL_Delay(desiredTime - deltaTime);
}

int main(int argc, char** argv)
{
	if(!InitializeSDL())
		return -1;

	// Create the window object
	SDL_Window* window = SDL_CreateWindow("Tile Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	float FPS = 75.0f;
	
	// Create the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Game* game = new Game(window, renderer);

	while(game->running){
		float startTime = SDL_GetTicks();

		game->Clear();
		game->HandleEvents();
		game->Update();
		game->Render();

		LimitFps(FPS, startTime);
	}
	delete game;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

	return 0;
}