#include "game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer)
:m_Window(window), m_Renderer(renderer)
{
    // Initalize stuff
    int w, h;
    running = true;
    SDL_GetWindowSize(m_Window, &w, &h);
    m_Width = w;
    m_Height = h;
}

Game::~Game()
{
    // Clean up the heap allocated memory
}   

void Game::Clear()
{
    // Clear the screen
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);
}

void Game::HandleEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            running = false;
        }
    }
}

void Game::Update()
{
    // Update the game state
}

void Game::Render()
{
    // Render to the screen
    SDL_RenderPresent(m_Renderer);
}