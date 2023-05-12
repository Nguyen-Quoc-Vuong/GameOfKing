#pragma once

#include"LTexture.h"
#include"common.h"

#define Enemymaxheight  300
#define Enemyminheight  330

#define Enemy_pos_range 250

class Enemy
{
public:
	int type;
	int posX, posY;
	string pathID;
	Enemy(int v = 0);
	
	~Enemy();

	void LoadFromFile(string path, SDL_Renderer* gRenderer);

	void LoadFromPro(SDL_Renderer* gRenderer);

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

	int Type();

	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int eWidth, eHeight;
	SDL_Texture *EnemyTexture;
};