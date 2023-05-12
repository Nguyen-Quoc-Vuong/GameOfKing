#include"Button.h"

void Button::Render(SDL_Rect* Clip, SDL_Renderer* gRenderer, LTexture &LoadButtonTexture)
{
	LoadButtonTexture.Render(pos.x, pos.y, gRenderer, Clip);
}

Button::Button(){
    pos.x =0;
    pos.y =0;
    Menu = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y){
    pos.x=x;
    pos.y=y;
    Menu = BUTTON_MOUSE_OVER;
}

bool Button::InSide (SDL_Event* e,int size){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
        int button_width, button_height;
		if (size == SMALL_BUTTON)
		{
			button_width = SMALL_BUTTON_WIDTH;
			button_height = SMALL_BUTTON_HEIGHT;
		}
		else
		{
			button_width = COMMON_BUTTON_WIDTH;
			button_height = COMMON_BUTTON_HEIGHT;
		}
		SDL_GetMouseState( &x, &y );
		bool inside = true;

		if( x < pos.x )
		{
			inside = false;
		}
		else if( y < pos.y )
		{
			inside = false;
		}
		else if( y > pos.y + button_height )
		{
			inside = false;
		}
		else if( x > pos.x + button_width )
		{
			inside = false;
		}		
		return inside;
	}
    return false;
}



