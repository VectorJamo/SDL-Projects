#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Game
{
    private:
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        float m_Width, m_Height;

    public:
        bool running; 

    public:
        Game(SDL_Window* window, SDL_Renderer* renderer);
        ~Game();

        void HandleEvents();
        void Clear();
        void Update();
        void Render();
        

};
#endif