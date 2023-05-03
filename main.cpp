
#include "Game.h"
#include "LTexture.h"
#include "Button.h"
#include "dinosaur.h"
#include "Enemy.h"
#include "Game_Base.h"
#include "Game_Utils.h"
int main( int argc, char* args[] ){
	Game* game = new Game();
	game->init();
	game->LoadMedia();
	game->HandleEvents();
	game->Close();
	return 0;
}