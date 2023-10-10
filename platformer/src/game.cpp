#include "game.h"

static float g_FrameCount = 0.0f;
static float g_Increment = 0.1f;

void SetAnimation(Sprite* player, Texture** animationTextures)
{
    g_FrameCount += g_Increment;
    if((int)g_FrameCount > 3)
        g_FrameCount = 0;
    else
        player->SetTexture(animationTextures[(int)g_FrameCount]);

}
Game::Game(SDL_Window* window, SDL_Renderer* renderer)
    :m_Window(window), m_Renderer(renderer), gameRunning(true)
{
    // Setup Stuff 
    // Window
    SDL_GetWindowSize(m_Window, &m_Width, &m_Height);

    m_BackgroundTexture = new Texture(m_Renderer, "../assets/img/sky.png");
    m_Background = new Sprite(*m_BackgroundTexture);
    
    m_GrassTexture = new Texture(m_Renderer, "../assets/img/grass.png");
    m_DirtTexture = new Texture(m_Renderer, "../assets/img/dirt.png");
    m_SunTexture = new Texture(m_Renderer, "../assets/img/sun.png");
    m_LavaTexture = new Texture(m_Renderer, "../assets/img/lava.png");
    m_BlobTexture = new Texture(m_Renderer, "../assets/img/blob.png");

    // Tilemap
    m_Tilemap = 
    "DDDDDDDDDDDDDDDDDDDD"
    "D000000000000000000D"
    "D0S0000000000000000D"
    "D0000G00000000000GGD"
    "D000000000GG0000000D"
    "D00000000000GG00000D"
    "D000GGGG00000000000D"
    "DG00000000000000000D"
    "D000000000000000000D"
    "D0G0000000000000000D"
    "D00G00000B000000000D"
    "D00000000GGGGGGG000D"
    "D000000000000000000D"
    "D0000000000000000G0D"
    "D000000000000000000D"
    "D000000000G0G0GGGGGD"
    "D00000GGG00000DDDDDD"
    "D0000GDDDLLLLLDDDDDD"
    "D000GDDDDDDDDDDDDDDD"
    "DGGGDDDDDDDDDDDDDDDD";

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(m_Tilemap[i*20 + j] == 'G'){
                Sprite* grass = new Sprite(*m_GrassTexture);
                grass->SetPosition(j*m_TileSize, i*m_TileSize);
                grass->SetSize(m_TileSize, m_TileSize);
                grass->tileIdentifier = 'G';

                m_Tiles.push_back(grass);

            }else if(m_Tilemap[i*20 + j] == 'D'){
                Sprite* dirt = new Sprite(*m_DirtTexture);
                dirt->SetPosition(j*m_TileSize, i*m_TileSize);
                dirt->SetSize(m_TileSize, m_TileSize);
                dirt->tileIdentifier = 'D';

                m_Tiles.push_back(dirt);
            }else if(m_Tilemap[i*20 + j] == 'S'){
                Sprite* sun = new Sprite(*m_SunTexture);
                sun->SetPosition(j*m_TileSize, i*m_TileSize);
                sun->SetSize(m_TileSize, m_TileSize);
                sun->tileIdentifier = 'S';

                m_Tiles.push_back(sun);
            }else if(m_Tilemap[i*20 + j] == 'L'){
                Sprite* lava = new Sprite(*m_LavaTexture);
                lava->SetPosition(j*m_TileSize, i*m_TileSize);
                lava->SetSize(m_TileSize, m_TileSize);
                lava->tileIdentifier = 'L';

                m_Tiles.push_back(lava);
            }else if(m_Tilemap[i*20 + j] == 'B'){
                Sprite* blob = new Sprite(*m_BlobTexture);
                blob->SetPosition(j*m_TileSize, i*m_TileSize);
                blob->SetSize(m_TileSize, m_TileSize);
                blob->tileIdentifier = 'B';

                m_Tiles.push_back(blob);
            }
        }
    }

    // Player
    m_PlayerCurrentTexture = new Texture(m_Renderer, "../assets/img/player/player_right1.png");

    m_PlayerRightTextures = (Texture**)malloc(sizeof(Texture*)*4);
    m_PlayerLeftTextures = (Texture**)malloc(sizeof(Texture*)*4);

    m_PlayerRightTextures[0] = new Texture(m_Renderer, "../assets/img/player/player_right1.png");
    m_PlayerRightTextures[1] = new Texture(m_Renderer, "../assets/img/player/player_right2.png");
    m_PlayerRightTextures[2] = new Texture(m_Renderer, "../assets/img/player/player_right3.png");
    m_PlayerRightTextures[3] = new Texture(m_Renderer, "../assets/img/player/player_right4.png");
    
    m_PlayerLeftTextures[0] = new Texture(m_Renderer, "../assets/img/player/player_left1.png");
    m_PlayerLeftTextures[1] = new Texture(m_Renderer, "../assets/img/player/player_left2.png");
    m_PlayerLeftTextures[2] = new Texture(m_Renderer, "../assets/img/player/player_left3.png");
    m_PlayerLeftTextures[3] = new Texture(m_Renderer, "../assets/img/player/player_left4.png");

    m_PlayerCurrentTexture = m_PlayerRightTextures[0];

    m_Player = new Sprite(*m_PlayerCurrentTexture);
    m_Player->SetSize(40, 80);
    m_Player->SetPosition(100.0f, 800.0f);

    m_dx = 0.0f; 
    m_dy = 0.0f;
    m_MovingLeft = false; m_MovingRight = false;

    // Player physics
    m_VelUpJump = 30.0f;
    m_VelDownGravity = 2.0f;
    m_Jump = false;
    m_InAir = false;

    m_XCollision = false;
    m_YCollision = false;

    // Blob
    m_BlobSpeed = 0.5f;
}
Game::~Game()
{
    delete m_BackgroundTexture;
    delete m_Background;

    delete m_GrassTexture;
    delete m_DirtTexture;
    delete m_SunTexture;
    delete m_LavaTexture;
    delete m_BlobTexture;

    for(int i = 0; i < 4; i++){
        delete m_PlayerRightTextures[i];
        delete m_PlayerLeftTextures[i];
    }
    free(m_PlayerRightTextures);
    free(m_PlayerLeftTextures);

    for(auto& tile: m_Tiles){
        delete tile;
    }

}
void Game::HandleEvents()
{
    SDL_Event ev;
    // Handle the events from the queue each frame
		while(SDL_PollEvent(&ev)){
			if(ev.type == SDL_QUIT){
				gameRunning = false;
			}
            if(ev.type == SDL_KEYDOWN){
                if(ev.key.keysym.sym == SDLK_SPACE && !m_Jump && !m_InAir){
                    m_Jump = true;
                    m_InAir = true;
                }
            }
            if(ev.type == SDL_KEYUP){
                if(ev.key.keysym.sym == SDLK_a && m_MovingLeft){
                    m_MovingLeft = false;
                    m_Player->SetTexture(m_PlayerLeftTextures[0]);
                }
                if(ev.key.keysym.sym == SDLK_d && m_MovingRight){
                    m_MovingRight = false;
                    m_Player->SetTexture(m_PlayerRightTextures[0]);
                }
            }
		}

        // Key events
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        if(keyState[SDL_SCANCODE_A] && m_Player->GetPosX() >= 0.0f){
            m_MovingLeft = true;
            m_MovingRight = false;
            m_dx = -2.0f;
            SetAnimation(m_Player, m_PlayerLeftTextures);
        }
        if(keyState[SDL_SCANCODE_D] && m_Player->GetPosX() + m_Player->GetWidth() <= m_Width){
            m_MovingRight = true;
            m_MovingLeft = false;
            m_dx = 2.0f;
            SetAnimation(m_Player, m_PlayerRightTextures);
        }
}
void Game::Clear()
{
	SDL_RenderClear(m_Renderer);
}

void Game::Update()
{
    // Update the position of player
    m_dy += m_VelDownGravity;

    // Player physics
    if(m_Jump){
        m_dy -= m_VelUpJump;
        m_VelUpJump -= m_VelDownGravity;
        if(m_VelUpJump <= 0.0f){
            m_VelUpJump = 30.0f;
            m_Jump = false;
        }
    }

    // Check if collison happens 
    float playerXNew = m_Player->GetPosX() + m_dx;
    float playerYNew = m_Player->GetPosY() + m_dy;
    const float playerWidth = 40.0f;
    const float playerHeight = 80.0f;
    const float tileSize = 50.0f;

    for(auto& tile: m_Tiles){
        if(!(tile->GetPosX() > playerXNew + playerWidth || tile->GetPosX() + tileSize < playerXNew || tile->GetPosY() > m_Player->GetPosY() + playerHeight || tile->GetPosY() + tileSize < m_Player->GetPosY()))
        {
            if(tile->tileIdentifier == 'B'){
                gameRunning = false;
            }
            m_XCollision = true;
        }
        if(!(tile->GetPosX() > m_Player->GetPosX() + playerWidth || tile->GetPosX() + tileSize < m_Player->GetPosX() || tile->GetPosY() > playerYNew + playerHeight || tile->GetPosY() + tileSize < playerYNew))
        {
            if(tile->tileIdentifier == 'L'){
                gameRunning = false;
            }
            m_YCollision = true;
        }
    }    

    if(!m_Jump && m_InAir && m_YCollision){
        m_InAir = false;
    }
     
    // If no collision, continue with the new position, if collision, discard the change in position
    if(m_XCollision){
        m_dx = 0.0f;
    }
    if(m_YCollision){
        m_dy = 0.0f;
        m_Jump = false;
        m_VelUpJump = 30.0f;
    }

    // Update the position of enemies and moving platforms
    for(auto& tile: m_Tiles){
        if(tile->tileIdentifier == 'B'){
            tile->SetPosition(tile->GetPosX() + m_BlobSpeed, tile->GetPosY());
            if(tile->GetPosX() + tile->GetWidth() > 800.0f){
                m_BlobSpeed = -m_BlobSpeed;
            }else if(tile->GetPosX() < 450.0f){
                m_BlobSpeed = abs(m_BlobSpeed);
            }
        }
    }

    // Set the position
    m_Player->SetPosition(m_Player->GetPosX() + m_dx, m_Player->GetPosY() + m_dy);
    m_dx = 0.0f;
    m_dy = 0.0f;
    m_XCollision = false;
    m_YCollision = false;
}

void Game::Render(){
    // Draw stuff
    
    // Background
    m_Background->Draw(m_Renderer);
    
    // Tiles
    for(auto& tile: m_Tiles){
        tile->Draw(m_Renderer);
    }
    // Player
    m_Player->Draw(m_Renderer);


    // Draw the grids
#if 1
    SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
    SDL_Rect rect = {m_Player->GetPosX(), m_Player->GetPosY(), m_Player->GetWidth(), m_Player->GetHeight()};
    SDL_RenderDrawRect(m_Renderer, &rect);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    for(int i = 0; i < 20; i++){
        SDL_RenderDrawLine(m_Renderer, m_TileSize*i, 0, m_TileSize*i, m_Height);
        SDL_RenderDrawLine(m_Renderer, 0, m_TileSize*i, m_Width, m_TileSize*i);
    }
#endif    

	SDL_RenderPresent(m_Renderer);
}