#include "entity.h"

Texture::Texture()
:texture(nullptr)
{
}

Texture::Texture(SDL_Renderer* renderer, const char* filePath)
{
    texture = IMG_LoadTexture(renderer, filePath);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

Entity::Entity(Texture* texture, const vec2& position, const vec2& size)
{
    m_Texture = texture;
    m_Position = position;
    m_Size = size;
}

void Entity::SetVelocity(const vec2& velocity)
{
    m_Velocity = velocity;
}

void Entity::SetPosition(const vec2& position)
{
    m_Position = position;
}

void Entity::SetSize(const vec2& size)
{
    m_Size = size;
}

void Entity::Draw(SDL_Renderer* renderer)
{
    SDL_Rect rect = {static_cast<int>(m_Position.x), static_cast<int>(m_Position.y), static_cast<int>(m_Size.width), static_cast<int>(m_Size.height)};
    SDL_RenderCopy(renderer, m_Texture->texture, NULL, &rect);
}


