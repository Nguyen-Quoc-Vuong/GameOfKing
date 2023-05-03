#include "Enemy.h"
#include "common.h"
#include "Game_Base.h"
#include <vector>
void Enemy:: GenerateBat(Enemy& enemy,
    SDL_Rect *gEnemyClips,
    SDL_Renderer* gRenderer)
{
    enemy.LoadFromProperties(gRenderer);
    for (int i=0 ; i < FLYING_FRAMES ; i++) {
        gEnemyClips[i].x = 43 * i;
		gEnemyClips[i].y = 0;
		gEnemyClips[i].w = 43;
		gEnemyClips[i].h = 30;
    }
}    
//tao ra quai vat
void Enemy:: GenerateGolem(Enemy& enemy,
    SDL_Rect(&gEnemyClips)[12],
    SDL_Renderer* gRenderer)
{
    enemy.LoadFromProperties(gRenderer);
    for (int i=0; i<12; i++) {
        gEnemyClips[i].x = i*57;
        gEnemyClips[i].y = 0;
        gEnemyClips[i].w = 57;
        gEnemyClips[i].h = 57;
    }
}
//tao ra cong?
void Enemy::GenerateGate(Enemy& enemy,
    SDL_Rect*gGateClips,
    SDL_Renderer* gRenderer)
{   
    enemy.LoadFromProperties(gRenderer);
    for (int i = 0; i < 16; i++) {
		gGateClips[i].x = i * 182;
		gGateClips[i].y = 0;
		gGateClips[i].w = 182;
		gGateClips[i].h = 206;
	}
}    
Enemy::Enemy(int _type)
{
    posX = 0;
    posY = 0;
    eWidth = 0;
    eHeight = 0;
    type = _type;
    if (type == IN_AIR_ENEMY)
    {
        pathID = "src/imgs/enemy/bat.png";
        posX = rand() % (SCREEN_WIDTH + Enemy_position_range) + SCREEN_WIDTH;
        posY = rand() % (Enemy_max_height - Enemy_min_height + 1) + Enemy_min_height;
    }
    else if (type == GATE)
    {
        pathID = "src/imgs/enemy/gate.png";
        posX = SCREEN_WIDTH;
        posY = GROUND - 20;
    }
    else if (type == GOLEM)
    {
        pathID = "src/imgs/enemy/golem.png";
        posX = rand() % (SCREEN_WIDTH + Enemy_position_range) + SCREEN_WIDTH;
        posY = GROUND + 8;
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
void Enemy::LoadFromProperties(SDL_Renderer* gRenderer)
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
void Enemy::Move(int acceleration)
{
    if (type == GATE)
        posX += -(2 + acceleration);
    else posX += -(ENEMY_SPEED + acceleration); 
    if (posX + MAX_ENEMY_WIDTH <= 0)
    {
        posX = rand() % (SCREEN_WIDTH + Enemy_position_range) + SCREEN_WIDTH;

        if (type == IN_AIR_ENEMY)
        {
            posY = rand() % (Enemy_max_height - Enemy_min_height + 1) + Enemy_min_height;
        }
    }
}
void Enemy::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
    SDL_Rect renderSpace = { posX, posY, eWidth, eHeight};
    if (currentClip != nullptr)
    {
        if (type == GOLEM) {
            renderSpace.w = currentClip->w + 20;
            renderSpace.h = currentClip->h + 20;
        }
        else if (type == GATE) {
            renderSpace.w = 120;
            renderSpace.h = 120;
        }
        else {
            renderSpace.w = currentClip->w;
            renderSpace.h = currentClip->h;
        }
    }
    if (type == GOLEM) SDL_RenderCopyEx(gRenderer, EnemyTexture, currentClip, &renderSpace, 0,NULL,SDL_FLIP_HORIZONTAL);
    else SDL_RenderCopy(gRenderer, EnemyTexture, currentClip, &renderSpace);
}

int Enemy::GetType()
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