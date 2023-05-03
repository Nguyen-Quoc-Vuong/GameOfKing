#include"Button.h"

Button::Button(){
    position.x =0;
    position.y =0;
    currentMenu = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y){
    position.x=x;
    position.y=y;

    currentMenu = BUTTON_MOUSE_OVER;
}

bool Button::InSide (SDL_Event* e,int size){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
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

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + button_width )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + button_height )
		{
			inside = false;
		}

		//Mouse is outside button
		// if( !inside )
		// {
		// 	currentMenu = BUTTON_MOUSE_OUT;
		// }
		return inside;
	}
    return false;
}
void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip);
}


