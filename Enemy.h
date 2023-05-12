#pragma once

#include"LTexture.h"
#include"common.h"

#define Enemy_max_height  300
#define Enemy_min_height  330

#define Enemy_position_range 250
#define ENEMY1_RANGE 100
#define ENEMY3_RANGE 500

class Enemy
{
public:
	int type;
	int posX, posY;
	string pathID;
	Enemy(int _type = 0);
	
	~Enemy();

	void LoadFromFile(string path, SDL_Renderer* gRenderer);

	void LoadFromProperties(SDL_Renderer* gRenderer);

	void CreateBat(Enemy& enemy,
		SDL_Rect* gEnemyClips,
		SDL_Renderer* gRenderer);//dơi

	void CreateGolem(Enemy& enemy,
		SDL_Rect(&gEnemyClips)[12],
		SDL_Renderer* gRenderer);//quái vật

	void CreateItem(Enemy& enemy,
		SDL_Rect* gItemClips,
		SDL_Renderer* gRenderer);//item

	void Move(int acceleration);//tang toc
	
	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetType();

	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int eWidth, eHeight;
	SDL_Texture *EnemyTexture;
};