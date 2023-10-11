#include "sprite.h"

#include <iostream>

SDL_Renderer* Tile::s_Renderer;
SDL_Renderer* Sprite::s_Renderer;
// Texture Class
Texture::Texture(SDL_Renderer* renderer, const char* filePath)
:texture(nullptr)
{
    texture = IMG_LoadTexture(renderer, filePath);
    if(texture == nullptr){
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }
}
Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

// Tile Class
Tile::Tile(Texture* texture, float x, float y, float width, float height)
:m_Texture(texture), m_PositionX(x), m_PositionY(y), m_Width(width), m_Height(height)
{
    int w, h;
    SDL_QueryTexture(m_Texture->texture, NULL, NULL, &w, &h);
    m_ClipRect = {0, 0, w, h};
}
void Tile::SetRenderer(SDL_Renderer* renderer)
{
    s_Renderer = renderer;
}
void Tile::SetPosition(float x, float y)
{
    m_PositionX = x;
    m_PositionY = y;
}

void Tile::SetSize(float width, float height)
{
    m_Width = width;
    m_Height = height;
}

void Tile::SetClipRect(float x, float y, float width, float height)
{
    m_ClipRect = {static_cast<int>(x),  static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
}

void Tile::Draw()
{
    SDL_Rect rect = {static_cast<int>(m_PositionX), static_cast<int>(m_PositionY), static_cast<int>(m_Width), static_cast<int>(m_Height)};
    SDL_RenderCopy(s_Renderer, m_Texture->texture, &m_ClipRect, &rect);
}

// Sprite Class
Sprite::Sprite(const char* filePath)
:m_Texture(nullptr), m_PositionX(0.0f), m_PositionY(0.0f)
{
    m_Texture = new Texture(s_Renderer, filePath);
    if(m_Texture == nullptr){
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }else{
        int w, h;
        SDL_QueryTexture(m_Texture->texture, NULL, NULL, &w, &h);
        m_ClipRect = {0, 0, w, h};
        m_Width = static_cast<float>(w);
        m_Height = static_cast<float>(h);
    }
}
void Sprite::SetRenderer(SDL_Renderer* renderer)
{
    s_Renderer = renderer;
}
void Sprite::SetPosition(const float& x, const float& y)
{
    m_PositionX = x;
    m_PositionY = y;
}

void Sprite::SetSize(const int& width, const int& height)
{
    m_Width = width;
    m_Height = height;
}

void Sprite::SetClipRect(const SDL_Rect& rect)
{
    m_ClipRect = rect;
}

void Sprite::Draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {static_cast<int>(m_PositionX), static_cast<int>(m_PositionY), static_cast<int>(m_Width), static_cast<int>(m_Height)};

    SDL_RenderCopy(renderer, m_Texture->texture, &m_ClipRect, &destRect);
}