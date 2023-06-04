#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static const int WIDTH = 800;
static const int HEIGHT = 600;

static int mouseX, mouseY;

static SDL_Texture* ball = nullptr;
static SDL_Rect playerRect = {WIDTH/2 - 10, HEIGHT/2 - 10, 20, 20};

void Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		std::cout << "FAILED TO INIT SDL!" << std::endl;

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		std::cout << "FAILED to INIT SDL_Image!" << std::endl;

	window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		std::cout << "Failed to create SDL window!" << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
		std::cout << "Failed to create SDL renderer!" << std::endl;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


	// Load assets
	ball = IMG_LoadTexture(renderer, "res/ball.png");
	if (ball == nullptr)
		std::cout << "Failed to load ball texture!" << std::endl;

}

void Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

struct vec2
{
	float x, y;

	vec2(): x(0), y(0) {}
	vec2 (float x, float y): x(x), y(y) {}
};

bool isWithin(int mouseX, int mouseY, const SDL_Rect& playerPos)
{
	if ((mouseX > playerPos.x && mouseX < playerPos.x + playerPos.w) && (mouseY > playerPos.y && mouseY < playerPos.y + playerPos.h))
		return true;

	return false;
}

float getDistance(int x1, int y1, int x2, int y2)
{
	float distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	return distance;
}

vec2 normalize(vec2 vector)
{
	float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
	vec2 normal(vector.x / magnitude, vector.y / magnitude);

	return normal;
}
int main(int argc, char** argv)
{
	Init();
	
	bool running = true;
	bool triggerHold = false;
	bool shoot = false;

	vec2 velocity(0, 0);
	float speed = 0;
	float friction = 0.5;

	while (running)
	{
		int startTime = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;

			// Handle keyboard input
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			}

			// Handle mouse input
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT && triggerHold == false && shoot == false)
				{
					int mx, my;
					SDL_GetMouseState(&mx, &my);

					if (isWithin(mx, my, playerRect))
					{
						triggerHold = true;
						std::cout << "Holding trigger!" << std::endl;
					}
				}
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT && triggerHold && shoot == false)
				{
					shoot = true;
					triggerHold = false;

					int mx, my;
					SDL_GetMouseState(&mx, &my);

					std::cout << "Trigger released!" << std::endl;

					vec2 initial(playerRect.x, playerRect.y);
					vec2 final(mx, my);

					velocity = normalize(vec2((playerRect.x - final.x), (playerRect.y - final.y)));
					speed = getDistance(initial.x, initial.y, final.x, final.y) / 10;

					std::cout << "Velocity: " << velocity.x << ", " << velocity.y << std::endl;
					std::cout << "Speed: " << speed << std::endl;
				}
			}
		}

		// Clear 
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if (shoot)
		{
			playerRect.x += velocity.x * speed;
			playerRect.y += velocity.y * speed;

			speed -= friction;
			if (speed <= 0)
			{
				shoot = false;
				speed = 0;
			}
			std::cout << "Player X,Y : " << playerRect.x + 10 << ", " << playerRect.y + 10 << std::endl;

		}
		else if (shoot == false && triggerHold == true) {

			int mx, my;
			SDL_GetMouseState(&mx, &my);

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(renderer, playerRect.x + 10, playerRect.y + 10, mx, my);
		}

		// Bounding collision 
		if (playerRect.x < 0 || playerRect.x + playerRect.w > WIDTH)
			velocity.x = -velocity.x;

		if (playerRect.y < 0 || playerRect.y + playerRect.h > HEIGHT)
			velocity.y = -velocity.y;
		
		// Render 
		
		SDL_RenderCopy(renderer, ball, NULL, &playerRect);

		// Show the back buffer
		SDL_RenderPresent(renderer);

		// Limit the FPS
		int endTime = SDL_GetTicks();
		if (endTime - startTime < (1000 / 60))
		{
			int deltaTime = endTime - startTime;
			SDL_Delay((1000 / 60) - deltaTime);
		}
	}

	Quit();

	return 0;
}