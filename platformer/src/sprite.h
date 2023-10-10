#ifndef SPRITE_H
#define SPRITE_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Texture
{
	SDL_Texture* texture;

	Texture(SDL_Renderer* renderer, const char* filePath);
};

class Sprite
{
	private:
		Texture m_Texture;
		float m_PositionX, m_PositionY;
		int m_Width, m_Height;
		SDL_Rect m_ClipRect;

	public:
		char tileIdentifier;


	public:
		Sprite(const Texture& texture);

		void SetPosition(const float& x, const float& y);
		void SetSize(const int& width, const int& height);
		void SetClipRect(const SDL_Rect& rect);
		void SetTexture(Texture* texture);

		void Draw(SDL_Renderer* renderer);

		inline float GetPosX() {return m_PositionX;}
		inline float GetPosY() {return m_PositionY;}
		inline float GetWidth() {return m_Width;}
		inline float GetHeight() {return m_Height;}
};
#endif