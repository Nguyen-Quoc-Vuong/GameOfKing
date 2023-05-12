#include "Enemy.h"
#include "common.h"
#include "Game_Base.h"
#include <vector>
void Enemy:: CreateBat(Enemy& enemy,
    SDL_Rect *gEnemyClips,
    SDL_Renderer* gRenderer)
{
    enemy.LoadFromPro(gRenderer);
    for (int i=0 ; i < FLYING_FRAMES ; i++) {
        gEnemyClips[i].x = 43 * i;
		gEnemyClips[i].y = 0;
		gEnemyClips[i].w = 43;
		gEnemyClips[i].h = 30;
    }
}    

void Enemy:: CreateGolem(Enemy& enemy,
    SDL_Rect(&gEnemyClips)[12],
    SDL_Renderer* gRenderer)
{
    enemy.LoadFromPro(gRenderer);
    for (int i=0; i<12; i++) {
        gEnemyClips[i].x = 57 * i;
        gEnemyClips[i].y = 0;
        gEnemyClips[i].w = 57;
        gEnemyClips[i].h = 57;
    }
}

void Enemy:: CreateItem(Enemy& enemy,
		SDL_Rect* gItemClips,
		SDL_Renderer* gRenderer)
{
    enemy.LoadFromPro(gRenderer);
    for (int i=0; i< 16; i++) {
        gItemClips[i].x = i * 182;
        gItemClips[i].y = 0;
		gItemClips[i].w = 182;
		gItemClips[i].h = 206;
    }
}
Enemy::Enemy(int v)
{
    posX = 0;
    posY = 0;

    eWidth = 0;
    eHeight = 0;

    type = v;
    if (type == AIR)
    {
        pathID = "src/imgs/enemy/bat.png";
        posX = rand() % (SCREEN_WIDTH + Enemy_pos_range) + SCREEN_WIDTH;
        posY = rand() % (Enemymaxheight - Enemyminheight + 1) + Enemyminheight;
    }
    else if (type == GOLEM)
    {
        pathID = "src/imgs/enemy/golem.png";
        posX = rand() % (SCREEN_WIDTH + Enemy_pos_range) + SCREEN_WIDTH;
        posY = GROUND + 8;
    }
    else if (type == ITEM)
    {
        pathID = "src/imgs/enemy/item2.png";
        posX = rand() % (SCREEN_WIDTH + Enemy_pos_range) + SCREEN_WIDTH;
        posY = GROUND - 8 ;
    }
    EnemyTexture = nullptr;
}

Enemy::~Enemy()
{
    posX = 0;
    posY = 0;
    eWidth = 0;
    eHeight = 0;
    type = 0;
    if (EnemyTexture != nullptr) {
        EnemyTexture = nullptr;
    }
}

void Enemy::LoadFromFile(string path, SDL_Renderer* gRenderer)
{
    SDL_Texture* tmpTexture = nullptr;
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
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
        else 
        {
            eWidth = tmpSurface->w;
            eHeight = tmpSurface->h;
        }
        SDL_FreeSurface(tmpSurface);
       
    }
     EnemyTexture = tmpTexture;
}
void Enemy::LoadFromPro(SDL_Renderer* gRenderer)
{
    SDL_Texture* tmpTexture = nullptr;
    SDL_Surface* tmpSurface = IMG_Load(pathID.c_str());
    if (tmpSurface == nullptr)
    {
        LogError("Can not load image.", IMG_ERROR);
    }
    else 
    {
        SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format,0,255,255));
        tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (tmpTexture == nullptr)
        {
            LogError("Can not create texture from surface.", SDL_ERROR);
        }
        else
        {
            eWidth = tmpSurface->w;
            eHeight = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }
    EnemyTexture = tmpTexture;
}
void Enemy::Move(int acce)
{   
    if (type == ITEM) posX += -(2+ acce);
    else  posX += -(ENEMY_SPEED + acce); 
    if (posX + MAX_ENEMY_WIDTH <= 0)
    {
        posX = rand() % (SCREEN_WIDTH + Enemy_pos_range) + SCREEN_WIDTH;

        if (type == AIR)
        {
            posY = rand() % (Enemymaxheight - Enemyminheight + 2) + Enemyminheight;
        }   
    }
}
void Enemy::Render(SDL_Renderer* gRenderer, SDL_Rect* Clip)
{
    SDL_Rect renderSpace = { posX, posY, eWidth, eHeight};
    if (Clip != nullptr)
    {
        if (type == GOLEM) 
        {
            renderSpace.w = Clip->w + 20;
			renderSpace.h = Clip->h + 20;
        }
        else if (type == ITEM) 
        {
            renderSpace.w = 140;
            renderSpace.h = 140;
        }
        else 
        {
            renderSpace.w = Clip->w;
            renderSpace.h = Clip->h;
        }   
        
    }
    if (type == GOLEM ) SDL_RenderCopyEx(gRenderer, EnemyTexture, Clip, &renderSpace, 0, NULL, SDL_FLIP_HORIZONTAL);
    else  SDL_RenderCopy(gRenderer, EnemyTexture, Clip, &renderSpace);
}

int Enemy::Type()
{
    return type;
}

int Enemy::GetSpeed(const int &acceleration)
{
    return ENEMY_SPEED + acceleration;
}

int Enemy::GetPosX()
{
    return posX;
}

int Enemy::GetPosY()
{
    return posY;
}

int Enemy::GetWidth()
{
    return eWidth;
}

int Enemy::GetHeight()
{
    return eHeight;
}