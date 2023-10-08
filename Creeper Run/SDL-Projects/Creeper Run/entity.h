#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vec2.h"

struct Texture
{
    SDL_Texture* texture;

    Texture();
    Texture(SDL_Renderer* renderer, const char* filePath);
    ~Texture();

    void LoadTexture(SDL_Renderer* renderer, const char* filePath);
};
class Entity
{
    private:
        Texture* m_Texture;
        vec2 m_Position, m_Size, m_Velocity;

    public:
        Entity(Texture* texture, const vec2& position, const vec2& size);

        void SetVelocity(const vec2& velocity);
        void SetPosition(const vec2& position);
        void SetSize(const vec2& size);

        void Draw(SDL_Renderer* renderer);

        inline vec2& GetPosition(){ return m_Position; };
        inline vec2& GetSize(){ return m_Size; };
        inline vec2& GetVelocity(){return m_Velocity;};
};