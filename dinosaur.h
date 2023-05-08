#pragma once

#include "LTexture.h"
#include "common.h"

#define JUMP 1
#define FALL 2
#define RUN	0
#define DOWN 3

class Dinosaur
{
public:
	int x;
	int posX, posY;
	static const int JUMP_SPEED = 8;
	static const int FALL_SPEED = 8;
	string pathID;
	Dinosaur();
	~Dinosaur() {}
	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk *gJump);
	void GenerateDinosaur(Dinosaur& dinosaur,
		SDL_Rect* gDinosaurclips,
		SDL_Renderer* gRenderer);
	void Move();
	void LoadFromFile(string path, SDL_Renderer* gRenderer);
	void LoadFromProperties(SDL_Renderer* gRenderer);
	void Render(SDL_Renderer *gRenderer, SDL_Rect* currentClip = nullptr);

	int GetPosX();

	int GetPosY();

private:
	SDL_Texture* DinosaurTexture = nullptr;
	
	int status;
};

