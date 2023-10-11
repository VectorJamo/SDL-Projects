#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Texture
{
	SDL_Texture* texture;

	Texture(SDL_Renderer* renderer, const char* filePath);
    ~Texture();
};

struct Tile
{
    private:
        Texture* m_Texture;
        float m_PositionX, m_PositionY, m_Width, m_Height;
		SDL_Rect m_ClipRect;

	public:
		static SDL_Renderer* s_Renderer;
		void SetRenderer(SDL_Renderer* renderer);

    Tile(Texture* texture, float x, float y, float width, float height);

    void SetPosition(float x, float y);
    void SetSize(float width, float height);
	void SetClipRect(float x, float y, float width, float height);
    
	void Draw();
};
class Sprite
{
	private:
		Texture* m_Texture;
		float m_PositionX, m_PositionY, m_Width, m_Height;
		SDL_Rect m_ClipRect;

    public:
        static SDL_Renderer* s_Renderer;
		void SetRenderer(SDL_Renderer* renderer);

	public:
        Sprite(const char* filePath);

		void SetPosition(const float& x, const float& y);
		void SetSize(const int& width, const int& height);
		void SetClipRect(const SDL_Rect& rect);

		void Draw(SDL_Renderer* renderer);

		inline float GetPosX() {return m_PositionX;}
		inline float GetPosY() {return m_PositionY;}
		inline float GetWidth() {return m_Width;}
		inline float GetHeight() {return m_Height;}
};
#endif