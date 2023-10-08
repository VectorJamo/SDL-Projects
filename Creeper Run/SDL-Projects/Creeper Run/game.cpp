#include "game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer)
    :m_Window(window), m_Renderer(renderer), gameRunning(true)
{
    // Setup Stuff 
    // Window
    SDL_GetWindowSize(m_Window, &m_ViewportRect.w, &m_ViewportRect.y);
    m_ViewportRect.x = 50;
    m_ViewportRect.y = 50;
    m_ViewportRect.w = 800;
    m_ViewportRect.h = 600;
    SDL_RenderSetViewport(m_Renderer, &m_ViewportRect);
    m_BackR = 0.0f; m_BackG = 0.0f; m_BackB = 0.0f;
    m_Increment = 0.8f;

    // Player
    m_Player = IMG_LoadTexture(m_Renderer, "res/player.png");
    m_PlayerWidth = 40.0f;
    m_PlayerHeight = 40.0f;
    m_PlayerX = m_ViewportRect.w/2 - m_PlayerWidth/2;
    m_PlayerY = m_ViewportRect.h/2 - m_PlayerHeight/2;
    m_PlayerSpeed = 4.0f;
    m_Health = 100.0f;

    // Fireball
    m_Fireball = IMG_LoadTexture(m_Renderer, "res/fireball.png");
    m_FireballWidth = 30.0f;
    m_FireballHeight = 30.0f;
    m_FireballX = m_ViewportRect.w/2 - m_FireballWidth/2;
    m_FireballY = 0.0f;
    m_FireballSpeed = 4.0f;
    m_FireballVel.x = -1 * m_FireballSpeed; // Set the direction to bottom left  by default
    m_FireballVel.y = 1 * m_FireballSpeed;

    m_Fireball2Width = 30.0f;
    m_Fireball2Height = 30.0f;
    m_Fireball2X = m_ViewportRect.w/2 - m_FireballWidth/2;
    m_Fireball2Y = 0.0f;
    m_Fireball2Speed = 4.0f;
    m_Fireball2Vel.x = 1 * m_Fireball2Speed; // Set the direction to bottom left  by default
    m_Fireball2Vel.y = -1 * m_Fireball2Speed;

    // Enemy
    m_Enemy = IMG_LoadTexture(m_Renderer, "res/enemy.png");
    m_EnemyWidth = 40.0f;
    m_EnemyHeight = 40.0f;
    m_EnemyX = m_ViewportRect.w/4 + m_EnemyWidth/2;
    m_EnemyY = m_ViewportRect.h/4 - m_EnemyHeight/2;
    m_EnemySpeed = 2.0f;

    m_EnemyVel.x = m_PlayerX - m_EnemyX;
    m_EnemyVel.y = m_PlayerY - m_EnemyY;
    m_EnemyVel.Normalize();
    m_EnemyVel.x = m_EnemyVel.x * m_EnemySpeed;
    m_EnemyVel.y = m_EnemyVel.y * m_EnemySpeed;
}
Game::~Game()
{
    SDL_DestroyTexture(m_Player);
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
                if(ev.key.keysym.sym == SDLK_SPACE){
                    m_Increment = 3.0f;
                }
            }
		}

    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_W] && m_PlayerY >= 0.0f){
        m_PlayerY -= m_PlayerSpeed;
    }
    if(keyState[SDL_SCANCODE_S] && m_PlayerY + m_PlayerHeight <= m_ViewportRect.h){
        m_PlayerY += m_PlayerSpeed;
    }
    if(keyState[SDL_SCANCODE_A] && m_PlayerX >= 0.0f){
        m_PlayerX -= m_PlayerSpeed;
    }
    if(keyState[SDL_SCANCODE_D] && m_PlayerX + m_PlayerWidth <= m_ViewportRect.w){
        m_PlayerX += m_PlayerSpeed;
    }
}
void Game::Clear()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, m_BackB, 255);
	SDL_RenderClear(m_Renderer);
}

void Game::Update()
{
    if(m_BackB <= 40.0f)
        m_Increment = abs(m_Increment);
    else if(m_BackB >= 120.0f)
        m_Increment = -(abs(m_Increment));

    m_BackB += m_Increment;

    // Fireball 1
    m_FireballX += m_FireballVel.x;
    m_FireballY += m_FireballVel.y;

    if(m_FireballX <= 0){
        m_FireballVel.x = abs(m_FireballVel.x);
    }else if(m_FireballX + m_FireballWidth > m_ViewportRect.w){
        m_FireballVel.x = -abs(m_FireballVel.x);
    }

    if(m_FireballY <= 0){
        m_FireballVel.y = abs(m_FireballVel.y);
    }else if(m_FireballY + m_FireballHeight > m_ViewportRect.h){
        m_FireballVel.y = -abs(m_FireballVel.y);
    } 

    // Fireball 2
    m_Fireball2X += m_Fireball2Vel.x;
    m_Fireball2Y += m_Fireball2Vel.y;

    if(m_Fireball2X <= 0){
        m_Fireball2Vel.x = abs(m_Fireball2Vel.x);
    }else if(m_Fireball2X + m_Fireball2Width > m_ViewportRect.w){
        m_Fireball2Vel.x = -abs(m_Fireball2Vel.x);
    }

    if(m_Fireball2Y <= 0){
        m_Fireball2Vel.y = abs(m_Fireball2Vel.y);
    }else if(m_Fireball2Y + m_Fireball2Height > m_ViewportRect.h){
        m_Fireball2Vel.y = -abs(m_Fireball2Vel.y);
    }

    // Enemy
    m_EnemyVel.x = m_PlayerX - m_EnemyX;
    m_EnemyVel.y = m_PlayerY - m_EnemyY;
    m_EnemyVel.Normalize();
    m_EnemyVel.x = m_EnemyVel.x * m_EnemySpeed;
    m_EnemyVel.y = m_EnemyVel.y * m_EnemySpeed;

    m_EnemyX += m_EnemyVel.x;
    m_EnemyY += m_EnemyVel.y;

    // Healthbar
    if(!(m_PlayerX > m_EnemyX + m_EnemyWidth || m_PlayerX+m_PlayerWidth < m_EnemyX || m_PlayerY+m_PlayerHeight < m_EnemyY || m_PlayerY > m_EnemyY + m_EnemyHeight)){
        m_Health -= 0.2f;
    }

    if(m_Health <= 0.0f)
        gameRunning = false;
}

void Game::Render(){
    // Draw stuff
    // White rect
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_Rect rect = {0, 0, m_ViewportRect.w, m_ViewportRect.h};    
    SDL_RenderDrawRect(m_Renderer, &rect);

    // Player
    SDL_Rect destRect = {(int)m_PlayerX, (int)m_PlayerY, (int)m_PlayerWidth, (int)m_PlayerHeight};
    SDL_RenderCopy(m_Renderer, m_Player, NULL, &destRect);

    // Fireball 1
    SDL_Rect destRect2 = {(int)m_FireballX, (int)m_FireballY, (int)m_FireballWidth, (int)m_FireballHeight};
    SDL_RenderCopy(m_Renderer, m_Fireball, NULL, &destRect2);

    // Fireball 2
    SDL_Rect destRect4 = {(int)m_Fireball2X, (int)m_Fireball2Y, (int)m_Fireball2Width, (int)m_Fireball2Height};
    SDL_RenderCopy(m_Renderer, m_Fireball, NULL, &destRect4);

    // Enemy
    SDL_Rect destRect3 = {(int)m_EnemyX, (int)m_EnemyY, (int)m_EnemyWidth, (int)m_EnemyHeight};
    SDL_RenderCopy(m_Renderer, m_Enemy, NULL, &destRect3);


    // Healthbar
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_Rect viewRect = {0, 0, 800+100, 600+100};
    SDL_RenderSetViewport(m_Renderer, &viewRect);
    SDL_Rect healthRect = {600, 10, static_cast<int>(m_Health), 30};
    SDL_RenderFillRect(m_Renderer, &healthRect);

    // Reset the rendering viewport
    SDL_RenderSetViewport(m_Renderer, &m_ViewportRect);

	SDL_RenderPresent(m_Renderer);
}