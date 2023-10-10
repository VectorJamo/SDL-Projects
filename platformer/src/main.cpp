#include "game.h"

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
	SDL_Window* window = SDL_CreateWindow("Tile Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
	
	// Create the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Game* game = new Game(window, renderer);

	float FPS_MAX = 75.0f;
	// Game Loop
	while(game->gameRunning){
		float startTime = (float)SDL_GetTicks();

		game->HandleEvents();

		game->Clear();
		game->Update();
		game->Render();

		LimitFps(FPS_MAX, startTime);
	}

	// Free all the objects allocated by game on the heap
	delete game;

	// Close all SDL systems
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}