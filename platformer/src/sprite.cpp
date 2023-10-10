#include "sprite.h"

#include <iostream>

Texture::Texture(SDL_Renderer* renderer, const char* filePath)
:texture(nullptr)
{
    texture = IMG_LoadTexture(renderer, filePath);
    if(texture == nullptr){
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }
}

Sprite::Sprite(const Texture& texture)
:m_Texture(texture), m_PositionX(0.0f), m_PositionY(0.0f)
{
    SDL_QueryTexture(m_Texture.texture, NULL, NULL, &m_Width, &m_Height);
    m_ClipRect = {0, 0, m_Width, m_Height};
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

void Sprite::SetTexture(Texture* texture)
{
    m_Texture = *texture;
}

void Sprite::SetClipRect(const SDL_Rect& rect)
{
    m_ClipRect = rect;
}

void Sprite::Draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {static_cast<int>(m_PositionX), static_cast<int>(m_PositionY), static_cast<int>(m_Width), static_cast<int>(m_Height)};

    SDL_RenderCopy(renderer, m_Texture.texture, &m_ClipRect, &destRect);
}