#pragma once
#include "Button.h"
#include "Game_Base.h"
#include "LTexture.h"
#include "common.h"
#include "dinosaur.h"
#include "Enemy.h"
string GetBestScore(string path);

void UpdateBestScore(string path,
    const int& score, 
    const string& old_high_score);

int UpdateGame(int& time, int& speed, int& score);

void RenderBackground(vector <double>& offsetSpeed, LTexture(&BackgroundTexture)[BACKGROUND_LAYER], SDL_Renderer* gRenderer);
      
void HandlePlayButton(SDL_Event* e,Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick);
    
void HandleHelpButton(SDL_Event* e,SDL_Rect(&gBackButton)[BUTTON_TOTAL],Button& HelpButton, Button& BackButton,LTexture& gInstructionTexture,  LTexture& gBackButtonTexture, SDL_Renderer* gRenderer, bool& Quit_game, Mix_Chunk* gClick);
    
void HandleExitButton(SDL_Event* e,Button& ExitButton, bool& Quit, Mix_Chunk* gClick );
    
void HandleContinueButton(Button& ContinueButton, LTexture& gContinueButtonTexture, SDL_Event* e, SDL_Renderer* gRenderer, SDL_Rect(&gContinueButton)[BUTTON_TOTAL],  bool& Game_State,  Mix_Chunk* gClick);
    
void HandlePauseButton(SDL_Event* e, SDL_Renderer* gRenderer,SDL_Rect(&gContinueButton)[BUTTON_TOTAL],Button& PauseButton,  Button& ContinueButton,  LTexture& gContinueButtonTexture,  bool& game_state,  Mix_Chunk* gClick);
      
void HandleSoundButton(SDL_Event* e, Button& SoundButton,  Mix_Chunk* gClick);
     
bool Colission(Dinosaur dinosaur, SDL_Rect* dino_clip,Enemy enemy,SDL_Rect* enemy_clip = nullptr);
    
bool CheckEnemyColission(Dinosaur dinosaur,  Enemy enemy1,  Enemy enemy3, SDL_Rect* char_clip, SDL_Rect* enemy_clip1 = nullptr, SDL_Rect* enemy_clip3= nullptr);

void DrawPlayerScore(LTexture& gTextTexture,
	LTexture& gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont, 
	const int& score);
void DrawDeath(LTexture& gTextTexture,
	LTexture& gDeathTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const int& deathCount);
void DrawBestScore(LTexture& TextTexture,
	LTexture& gHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const string& HighScore);
void DrawEndGame(LTexture& gLoseTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool &Play_Again);

  
void ControlDinoFrame(int &frame);

void ControlBatFrame(int &frame);

void ControlGolemFrame(int &frame);

void ControlItemFrame(int &frame);