#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <vector>
#include "sprite.h"

class Game
{
    private:
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        int m_Width, m_Height;

        Texture* m_BackgroundTexture;
        Sprite* m_Background;
        // Tilemap
        // Textures
        Texture* m_GrassTexture;
        Texture* m_DirtTexture;
        Texture* m_SunTexture;
        Texture* m_LavaTexture;
        Texture* m_BlobTexture;
        Texture* m_DoorTexture;

        const char* m_Tilemap;
        std::vector<Sprite*> m_Tiles;

        int m_TileSize = 50; // 50x50 pixels -> 1000/50 tiles -> 20 tiles in both X and Y.

        // Player
        Texture** m_PlayerRightTextures, **m_PlayerLeftTextures;
        Texture* m_PlayerCurrentTexture;
        Sprite* m_Player;
        float m_dx, m_dy;
        bool m_MovingLeft, m_MovingRight;

        // Player physics
        float m_VelUpJump, m_VelDownGravity;
        bool m_Jump, m_InAir;
        bool m_XCollision, m_YCollision;

        // Blob
        float m_BlobSpeed;

        // Platform
        Texture* m_PlatformTexture;
        Sprite* m_Platform;

        float m_PlatformSpeed;
        float m_PlatformDistance, m_MaxPlatformDistance;
        
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