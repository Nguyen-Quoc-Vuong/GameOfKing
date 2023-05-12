#include "dinosaur.h"
#include "common.h"
#include "Game_Base.h"
int minHeight = 360;

Dinosaur::Dinosaur() {
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;
	pathID = "src/imgs/dinosaur/dino.png";
	status = 0;
}
bool Dinosaur::OnGround(){
    return posY  == GROUND;
}
void Dinosaur::HandleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (OnGround())
				{
					Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
					status = JUMP;
				}
			}
			
		
		}
	}
	if (e.type == SDL_KEYUP )
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (posY <= minHeight)
					status = FALL;
			}
		}
	}
} 

void Dinosaur::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
	}
}
void Dinosaur::CreateDinosaur(Dinosaur& dinosaur,SDL_Rect* gDinosaurClips, SDL_Renderer* gRenderer) {
	dinosaur.LoadFromProperties(gRenderer);
	for (int i = 0; i < 6; i++) {
		gDinosaurClips[i].x = 57 * i;
		gDinosaurClips[i].y = 0;
		gDinosaurClips[i].w = 57;
		gDinosaurClips[i].h = 57;
	}
}
void Dinosaur::LoadFromFile(string path, SDL_Renderer* gRenderer) {
	SDL_Texture* tmpTexture = nullptr;
	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
	tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	DinosaurTexture = tmpTexture;
}
void Dinosaur::LoadFromProperties(SDL_Renderer* gRenderer) {
	SDL_Texture* tmpTexture = nullptr;
	SDL_Surface* tmpSurface = IMG_Load(pathID.c_str());
	if (tmpSurface == nullptr)
	{
		LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			LogError("Can not create texture from surface.", SDL_ERROR);
		}
		SDL_FreeSurface(tmpSurface);
	}
	DinosaurTexture = tmpTexture;
}
void Dinosaur::Render(SDL_Renderer *gRenderer,SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = {posX, posY, 57, 57 };
	renderSpace.w = currentClip->w + 20;
	renderSpace.h = currentClip->h + 20;
	SDL_RenderCopy(gRenderer, DinosaurTexture, currentClip, &renderSpace);
}

int Dinosaur::GetPosX()
{
	return posX;
}

int Dinosaur::GetPosY()
{
	return posY;
}
