#include "LTexture.h"
#include "Game.h"
#include "Game_Utils.h"
#include "dinosaur.h"
#include "Game_Base.h"
#include "Button.h"
#include "Enemy.h"
#include "common.h"
#include <ctime>
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;

LTexture LoadMenuTexture;
LTexture LoadPlayTexture;
LTexture LoadExitTexture;
LTexture LoadPauseTexture;
LTexture LoadContinueTexture;
LTexture LoadLoseTexture;
LTexture LoadBackTexture;
LTexture LoadSoundTexture;
LTexture LoadText1Texture;
LTexture LoadScoreTexture;
LTexture LoadDeathCountTexture;
LTexture LoadText2Texture;
LTexture LoadText3Texture;
LTexture LoadHighScoreTexture;
LTexture LoadGroundTexture;
LTexture BackgroundTexture[BACKGROUND_LAYER];
LTexture BackgroundTexture1[BACKGROUND_LAYER];
LTexture BackgroundTexture2[BACKGROUND_LAYER];
LTexture BackgroundTexture3[BACKGROUND_LAYER];
LTexture gText1Texture;
LTexture gText2Texture;
LTexture gText3Texture;
LTexture gScoreTexture;
LTexture gHighScoreTexture;
LTexture gDeathCountTexture;

SDL_Rect LoadPlay[BUTTON_TOTAL];
SDL_Rect LoadExit[BUTTON_TOTAL];
SDL_Rect LoadPause[BUTTON_TOTAL];
SDL_Rect LoadBack[BUTTON_TOTAL];
SDL_Rect LoadPlayAgain[BUTTON_TOTAL];
SDL_Rect LoadSound[BUTTON_TOTAL];
SDL_Rect LoadContinue[BUTTON_TOTAL];
SDL_Rect gDinosaurClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips3[FLYING_FRAMES];
SDL_Rect gGateClips[16];
SDL_Rect gEnemyClips1[12];
SDL_Rect gEnemyClips2[12];
SDL_Rect gEnemyClipsGolem[18];

SDL_Color textColor = {0,0,0};
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
//Mix_Chunk* gTele = nullptr;
Mix_Chunk* gLose = nullptr;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button SoundButton(852, 12);
Button BackButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);

Dinosaur dinosaur(MINOTOUR1);

const string SCENCE1[BACKGROUND_LAYER] = {
	"src/imgs/background/Scence_01.png",
	"src/imgs/background/Scence_02.png",
	"src/imgs/background/Scence_03.png",
	"src/imgs/background/Scence_04.png",
	"src/imgs/background/Scence_05.png",
	"src/imgs/background/Scence_06.png",
	"src/imgs/background/Scence_07.png",
	"src/imgs/background/Scence_08.png",
	"src/imgs/background/Scence_09.png",
};


bool Game::init()
{
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == nullptr )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_OPENGL );
			if( gRenderer == nullptr )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;}
bool Game::LoadMedia(){
		
	bool success = true;
	
	gMusic = Mix_LoadMUS("src/sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}
	gMenuMusic = Mix_LoadMUS("src/sound/menu_audio.wav");
	if (gMenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}
		//gTele = 
	gClick = Mix_LoadWAV("src/sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}
	gJump = Mix_LoadWAV("src/sound/jump_sound.wav");
	if (gJump == nullptr)
	{
		LogError ("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}
	gLose = Mix_LoadWAV("src/sound/lose_sound.wav");
	if (gLose == nullptr)
	{
		LogError ("Failed to load lose sound", MIX_ERROR);
		success = false;
	}
	else {
		gFont = TTF_OpenFont("src/font/PressStart2P.ttf", 15);
		if (gFont == nullptr)
		{
			LogError("Failed to load font",MIX_ERROR);
			success = false;
		}
		else
		{
			if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text1 texture" << endl;
				success = false;
			}
			if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text2 texture" << endl;
				success = false;
			}
			if (!gText3Texture.LoadFromRenderedText("Death: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text3 texture" << endl;
				success = false;
			}
			if (!LoadMenuTexture.LoadFromFile( "src/imgs/background/menu.png", gRenderer))
			{
				cout << "Failed to load menu image" << endl;
				success = false;
			}

			if (!LoadPlayTexture.LoadFromFile("src/imgs/button/big_button/play_button.png",gRenderer))
			{
				cout << "Failed to load instruction image" << endl;
				success = false;
			}
			else {
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					LoadPlay[i].x = 130 * i;
					LoadPlay[i].y = 0;
					LoadPlay[i].w = 130;
					LoadPlay[i].h = 45;
				}
			}
			if (!LoadBackTexture.LoadFromFile( "src/imgs/button/big_button/back_button.png", gRenderer))
				{
					cout<<"Failed to load back_button image"<<endl;
					success = false;
				}
				else 
				{
					for (int i=0; i < BUTTON_TOTAL ; ++i)
					{
						LoadBack[i].x = 57 *i;
						LoadBack[i].y = 0;
						LoadBack[i].w = 57;
						LoadBack[i].h = 57;
					}
				}
			
	if (!LoadExitTexture.LoadFromFile("src/imgs/button/big_button/exit_button.png", gRenderer))
			{
				cout << "Failed to load instruction image" << endl;
				success = false;
			}
			else {
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					LoadExit[i].x = 130 * i;
					LoadExit[i].y = 0;
					LoadExit[i].w = 130;
					LoadExit[i].h = 45;
				}
			}
	//if (!LoadSoundTexture.LoadFromFile())
	if (!LoadPauseTexture.LoadFromFile("src/imgs/button/big_button/pause_button.png",gRenderer))
			{
				cout << "Failed to load instruction image" << endl;
				success = false;
			}
			else {
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					LoadPause[i].x = 57 * i;
					LoadPause[i].y = 0;
					LoadPause[i].w = 57;
					LoadPause[i].h = 57;
				}
			}
	if (!LoadContinueTexture.LoadFromFile("src/imgs/button/big_button/continue_button.png", gRenderer ))
			{
				cout << "Failed to load instruction image" << endl;
				success = false;
			}	
			else {
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					LoadContinue[i].x = 57 * i;
					LoadContinue[i].y = 0;
					LoadContinue[i].w = 57;
					LoadContinue[i].h = 57;
				}
			}
	
	for (int i=0; i < BACKGROUND_LAYER; ++i)
	{
		if(!BackgroundTexture1[i].LoadFromFile(SCENCE1[i].c_str(), gRenderer))
		{
			cout<<"Failed to load background image" <<endl;
			success = false;
		}
	}
	if (!LoadGroundTexture.LoadFromFile( "src/imgs/background/ground.png", gRenderer))
	{
		cout<<  "Failed to load ground image" << endl;
		success = false;
	}
	if (!LoadLoseTexture.LoadFromFile( "src/imgs/background/lose.png", gRenderer))
	{
		cout<< "Failed to load lose imgae"<<endl;
		success = false;
	}

	}
	
	}
return success;

 }
void Game::HandleEvents(){
	bool Quit_Menu = false;
	bool Play_Again = false;
	Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
	while (!Quit_Menu)
	{
		SDL_Event e_mouse;
		while (SDL_PollEvent(&e_mouse) != 0)
		{
			if (e_mouse.type == SDL_QUIT)
			{
				Quit_Menu = true;
			}

			bool Quit_Game = false;
			
			HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);	
			HandleSoundButton(&e_mouse, SoundButton, gClick);
			HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);
		}
		LoadMenuTexture.Render(0, 0, gRenderer);


		SDL_Rect* currentClip_Play = &LoadPlay[PlayButton.currentMenu];
		PlayButton.Render(currentClip_Play, gRenderer, LoadPlayTexture);
		SDL_Rect* currentClip_Sound = &LoadSound[SoundButton.currentMenu];
		SoundButton.Render(currentClip_Sound, gRenderer, LoadSoundTexture);
		SDL_Rect* currentClip_Exit = &LoadExit[ExitButton.currentMenu];
		ExitButton.Render(currentClip_Exit, gRenderer, LoadExitTexture);
		SDL_RenderPresent(gRenderer);


	}
	int deathCount = 0;
	while (Play_Again){
		for (int i = 0; i < 9; i++) {
			BackgroundTexture[i] = BackgroundTexture1[i];
		}
	bool winter=true;
	bool createGate = false;
	srand(time(nullptr));
	int time = 0;
	int score = 0;
	int acceleration = 2;
	int frame_Dinosaur = 0;
	int frame_Enemy = 0;
	int frame_Enemy1 = 0;
	int frame_Enemy2 = 0;
	int frame_Enemy3 = 0;
	int frame_Gate = 0;
	int count = 0;
	string highscore = GetHighScoreFromFile("high_score.txt");
		SDL_Event e;
	 	Enemy enemy1(GOLEM);
		Enemy enemy2(GOLEM);
		Enemy enemy3(IN_AIR_ENEMY);
		//Enemy gate(GATE);
		Mix_PlayMusic(gMusic, IS_REPEATITIVE);
		enemy1.GenerateGolem(enemy1, gEnemyClips1, gRenderer);
		enemy2.GenerateGolem(enemy2, gEnemyClips2, gRenderer);
		enemy3.GenerateBat(enemy3, gEnemyClips3, gRenderer);
		
		dinosaur.GenerateDinosaur(dinosaur, gDinosaurClips, gRenderer);
		int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
		vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);
		bool Quit = false;
		bool Game_State = true;
		int next = 0;
		bool lose = false;
		while (!Quit){
			if (Game_State) {
				if (enemy1.GetPosX() >= 0 && abs(enemy1.GetPosX() - enemy2.GetPosX()) < 170 + 20 * acceleration) {
					enemy2.posX = enemy1.posX - (170 + 20 * acceleration);
				}
				 UpdateGameTimeAndScore(time, acceleration, score);
				while (SDL_PollEvent(&e) != 0){
					if (e.type == SDL_QUIT) {
						Quit = true;
						Play_Again = false;
					}
					else HandlePauseButton(&e,gRenderer,LoadContinue,
						PauseButton,ContinueButton,LoadContinueTexture,Game_State,gClick);
					dinosaur.HandleEvent(e, gJump);	
				}
				SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
				SDL_RenderClear(gRenderer);
				if (winter){
					enemy1.GenerateGolem(enemy1, gEnemyClips1, gRenderer);
					enemy2.GenerateGolem(enemy2, gEnemyClips2, gRenderer);
					enemy1.pathID = "src/imgs/enemy/golem.png";
					enemy2.pathID = "src/imgs/enemy/golem.png";
					//portal.pathID = "imgs/enemy/portal.png";
					RenderScrollingBackground(OffsetSpeed_Bkgr, BackgroundTexture1, gRenderer);
				}
				// if (score >= 180 && score % 180 == 0 )
				// {
				// 	createPortal = true;
				// }
				dinosaur.Move();
				SDL_Rect* currentClip_Dinosaur = nullptr;
				if (dinosaur.OnGround())
				{
					currentClip_Dinosaur = &gDinosaurClips[frame_Dinosaur / SLOW_FRAME_DINO];
					dinosaur.Render(gRenderer, currentClip_Dinosaur);
				}
				else if (dinosaur.GetPosY() < GROUND)
				{
					currentClip_Dinosaur = &gDinosaurClips[0];
					dinosaur.Render(gRenderer, currentClip_Dinosaur);
				}
				SDL_Rect* currentClip_Enemy1 = &gEnemyClips1[frame_Enemy1 / SLOW_FRAME_ENEMY];
				SDL_Rect* currentClip_Enemy2 = &gEnemyClips2[frame_Enemy2 / SLOW_FRAME_ENEMY];
				SDL_Rect* currentClip_Enemy3 = &gEnemyClips3[frame_Enemy3 / SLOW_FRAME_ENEMY];
				//SDL_Rect* currentClip_Gate = &gGateClips[frame_Gate / SLOW_FRAME_ENEMY];
				enemy1.Move(acceleration);
				enemy1.Render(gRenderer, currentClip_Enemy1);
				enemy2.Move(acceleration);
				enemy2.Render(gRenderer, currentClip_Enemy2);
				enemy3.Move(acceleration);
				enemy3.Render(gRenderer, currentClip_Enemy3);
				// if (createGate) {
				// 	if
				// }
				SDL_Rect* currentClip_Pause = &LoadPause[PauseButton.currentMenu];
				PauseButton.Render(currentClip_Pause, gRenderer, LoadPauseTexture);
				DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
				DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);
				DrawDeath(gText3Texture, gDeathCountTexture, textColor, gRenderer, gFont, deathCount);
				if (CheckEnemyColission(dinosaur,
					enemy1, enemy2, enemy3, 
					currentClip_Dinosaur, currentClip_Enemy1, currentClip_Enemy2, currentClip_Enemy3))
				{
					deathCount++;
					Mix_PauseMusic();
					Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
					UpdateHighScore("high_score.txt", score, highscore);
					Quit = true;
					DrawEndGameSelection(LoadLoseTexture, &e, gRenderer, Play_Again);
					if (!Play_Again)
					{
						enemy1.~Enemy();
						enemy2.~Enemy();
						enemy3.~Enemy();
						//gate.~Enemy();
					}
				}
				// if (CheckColission(dinosaur, currentClip_Dinosaur, gate, currentClip_Gate) && createGate) 
				// {
				// 	createGate = false;

				// }
				SDL_RenderPresent(gRenderer);
				ControlDinoFrame(frame_Dinosaur);
				ControlGolemFrame(frame_Enemy1);
				ControlGolemFrame(frame_Enemy2);
				ControlBatFrame(frame_Enemy3);
				//ControlGateFrame(frame_Gate);
			}
		}
	}

}   
// void Game::Render(){
// 	//Main loop flag
// 			bool quit = false;

// 			//Event handler
// 			SDL_Event e;

// 			//While application is running
// 			while( !quit )
// 			{
// 				//Handle events on queue
// 				while( SDL_PollEvent( &e ) != 0 )
// 				{
// 					//User requests quit
// 					if( e.type == SDL_QUIT )
// 					{
// 						quit = true;
// 					}
// 				}

// 				//Clear screen
							
				
// 				SDL_RenderClear( gRenderer );
				
				
				
				
// 				//Render texture to screen
// 				SDL_RenderCopy( gRenderer, gTexture, nullptr, nullptr );
// 				LoadMenuTexture.Render(SCREEN_WIDTH,SCREEN_HEIGHT,gRenderer,nullptr);
				
// 				LoadPlayTexture.Render(350,200,gRenderer,nullptr);
// 				LoadExitTexture.Render(350,398,gRenderer,nullptr);
// 				// LoadPauseTexture.Render(SCREEN_WIDTH/2-250,SCREEN_HEIGHT/2,gRenderer);
// 				// LoadContinueTexture.Render(SCREEN_WIDTH/2-250,SCREEN_HEIGHT/2-200,gRenderer);

// 				//Render texture to screen
				

// 				//Update screen
// 				SDL_RenderPresent( gRenderer ); 
// 			}
// }
void Game::Close(){
	LoadMenuTexture.free();
    LoadPlayTexture.free();
    LoadExitTexture.free();
    LoadPauseTexture.free();
    LoadContinueTexture.free();
	LoadGroundTexture.free();
	LoadScoreTexture.free();
	LoadBackTexture.free();
	LoadLoseTexture.free();
	LoadText1Texture.free();
	LoadText2Texture.free();
	LoadText3Texture.free();
	LoadScoreTexture.free();
	LoadHighScoreTexture.free();
	LoadDeathCountTexture.free();
	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		BackgroundTexture1[i].free();
	}
	//Destroy Sound
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gJump);
	Mix_FreeChunk(gLose);

	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	gRenderer = nullptr;
	SDL_DestroyWindow( gWindow );
	gWindow = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
 }