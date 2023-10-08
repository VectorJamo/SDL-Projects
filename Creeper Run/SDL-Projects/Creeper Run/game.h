#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include "vec2.h"

class Game
{
    private:
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        SDL_Rect m_ViewportRect;
        float m_BackR, m_BackG, m_BackB;
        float m_Increment;

        // Player
        SDL_Texture* m_Player;
        float m_PlayerX, m_PlayerY, m_PlayerWidth, m_PlayerHeight;
        float m_PlayerSpeed;
        float m_Health;

        // Fireballs
        SDL_Texture* m_Fireball;
        float m_FireballX, m_FireballY, m_FireballWidth, m_FireballHeight;
        float m_FireballSpeed;
        vec2 m_FireballVel;

        float m_Fireball2X, m_Fireball2Y, m_Fireball2Width, m_Fireball2Height;
        float m_Fireball2Speed;
        vec2 m_Fireball2Vel;

        // Enemy
        SDL_Texture* m_Enemy;
        float m_EnemyX, m_EnemyY, m_EnemyWidth, m_EnemyHeight;
        float m_EnemySpeed;
        vec2 m_EnemyVel;

        // Food

        // Powerups
    public:
        bool gameRunning; 

    public:
        Game(SDL_Window* window, SDL_Renderer* renderer);
        ~Game();

        void HandleEvents();
        void Clear();
        void Update();
        void Render();
};

#endif