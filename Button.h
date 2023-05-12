#pragma once

#include "common.h"
#include"LTexture.h"
#include"Game_Base.h"

class Button 
{
public:
    ButtonMenu Menu;

    Button();
    
    Button(int x, int y);

    bool InSide (SDL_Event *e, int size);

    void Render(SDL_Rect* Clip, SDL_Renderer* gRenderer, LTexture &LoadButtonTexture);

private:
    SDL_Point pos;    
};
