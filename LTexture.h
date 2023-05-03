#pragma once
#include "common.h"
#include "Game_Base.h"
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool LoadFromFile( string path, SDL_Renderer* gRenderer );

		bool LoadFromRenderedText(string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);
		void free();

		//Renders texture at given point
		void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);
		void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* src,int scale);
		
		//Gets image dimensions
		int GetWidth();
		int GetHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};