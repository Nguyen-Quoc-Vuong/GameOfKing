#include "Game_Utils.h"
#include "Game.h"
#include "common.h"
#include "Game_Base.h"
#include "dinosaur.h"
#include "Enemy.h"
#include "LTexture.h"
string GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path, ios::in);
	HighScoreFile >> highscore;

	return highscore;
}
void UpdateHighScore(string path,
	const int& score, 
	const string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = to_string(oldHighScore);

	HighScoreFile << newHighScore;
}
int UpdateGameTimeAndScore(int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 20 == 0)
	{
		score += SCORE_INCREASEMENT;
	}
	
	time += TIME_INCREASEMENT;

	return time;
}
void RenderScrollingBackground(vector <double>& offsetSpeed,
	LTexture(&BackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* gRenderer)
{	
	vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);
	layer_speed.push_back(LAYER_6_SPEED);
	layer_speed.push_back(LAYER_7_SPEED);
	layer_speed.push_back(LAYER_8_SPEED);
	layer_speed.push_back(LAYER_9_SPEED);

	for (int i=0; i < BACKGROUND_LAYER ; i++) {
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -BackgroundTexture[i].GetWidth()){
			offsetSpeed[i] = 0;
		}
		BackgroundTexture[i].Render(offsetSpeed[i], 0, gRenderer);
		BackgroundTexture[i].Render(offsetSpeed[i] + BackgroundTexture[i].GetWidth(), 0,gRenderer);
	}
}


void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play,
	Mix_Chunk* gClick
    ) 
{
    if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.InSide(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentMenu = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentMenu = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentMenu = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_TOTAL],
    Button& HelpButton,
    Button& BackButton,
    LTexture& gInstructionTexture,
    LTexture& gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& Quit_game,
    Mix_Chunk* gClick){
		if (HelpButton.InSide(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentMenu = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentMenu = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{	Game q;
						q.Close();
						ReadDone = true;
						Quit_game = true;
						
					}

					else if (BackButton.InSide(e, COMMON_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentMenu = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentMenu = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentMenu = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentMenu];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentMenu = BUTTON_MOUSE_OUT;
	}
	}
void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit,
	Mix_Chunk* gClick
    )
{
        if (ExitButton.InSide(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentMenu = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentMenu = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentMenu = BUTTON_MOUSE_OUT;
	}
}
void HandleContinueButton(Button& ContinueButton,
    LTexture& gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    bool& Game_State,
	Mix_Chunk* gClick){
        bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.InSide(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.currentMenu = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					ContinueButton.currentMenu = BUTTON_MOUSE_OVER;
					Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
					Mix_ResumeMusic();
					Game_State = true;
					Back_To_Game = true;
				}
				break;
				}
			}
			else
			{
				ContinueButton.currentMenu = BUTTON_MOUSE_OUT;
			}
		
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentMenu];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
    }
void HandlePauseButton(SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    Button& PauseButton,
    Button& ContinueButton,
    LTexture& gContinueButtonTexture,
    bool& game_state,
	Mix_Chunk *gClick
    )
{
		if (PauseButton.InSide(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.currentMenu = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.currentMenu = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			Mix_PauseMusic();
			break;
		case SDL_MOUSEBUTTONUP:
			game_state = false;
			HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, game_state, gClick);
			break;
		}
	}
	else
	{
		PauseButton.currentMenu = BUTTON_MOUSE_OUT;
	}
	}	
bool soundOn= true;
void HandleSoundButton(SDL_Event* e,
    Button& SoundButton,
    Mix_Chunk* gClick)
	{
		if (SoundButton.InSide(e, COMMON_BUTTON))
		{
			switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (!soundOn) {
				soundOn = true;
				Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
				Mix_ResumeMusic();
				SoundButton.currentMenu = BUTTON_MOUSE_OUT;
				break;
			}
			else if (soundOn){
				soundOn = false;
				Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
				Mix_PauseMusic();
				SoundButton.currentMenu = BUTTON_MOUSE_OVER;
				break;
			}
		}
	}
	if (soundOn)
		SoundButton.currentMenu = BUTTON_MOUSE_OUT;
		}

bool CheckColission(Dinosaur dinosaur,
    SDL_Rect* dino_clip,
    Enemy enemy,
    SDL_Rect* enemy_clip)
{
	bool collide = false;
	int left_a = dinosaur.GetPosX() + 20;
	int right_a = dinosaur.GetPosX() + dino_clip->w - 10;
	int top_a = dinosaur.GetPosY() + 10;
	int bottom_a = dinosaur.GetPosY() + dino_clip->h - 10;
	if (enemy.GetType() == IN_AIR_ENEMY)
	{
		const int TRASH_PIXEL_1 = 12;
		const int TRASH_PIXEL_2 = 18;
		int left_b = enemy.GetPosX() + TRASH_PIXEL_1;
		int right_b = enemy.GetPosX() + enemy_clip->w - TRASH_PIXEL_1;
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy_clip->h - TRASH_PIXEL_2;
		if (right_a > left_b and left_a < right_b and bottom_a > top_b and top_a < bottom_b)
			collide = true;
	}
	else {
		const int TRASH_PIXEL_1 = 18;
		const int TRASH_PIXEL_2 = 12;
		int left_b = enemy.GetPosX() + TRASH_PIXEL_1;
		int right_b = enemy.GetPosX() + enemy_clip->w - TRASH_PIXEL_1;
		int top_b = enemy.GetPosY() - 8 + TRASH_PIXEL_2;
		int bottom_b = enemy.GetPosY()+ enemy_clip->h - TRASH_PIXEL_2;
		if (right_a > left_b and left_a < right_b and bottom_a >top_b and top_a < bottom_b)
			collide = true;
	}
	return collide;
}

bool CheckEnemyColission(Dinosaur dinosaur,
    Enemy enemy1,
    Enemy enemy3,
    SDL_Rect* dino_clip,
    SDL_Rect* enemy_clip1, SDL_Rect* enemy_clip3)
{
	if (CheckColission(dinosaur, dino_clip, enemy1, enemy_clip1))
	{
		return true;
	}
	if (CheckColission(dinosaur, dino_clip, enemy3, enemy_clip3))
	{
		return true;
	}
	return false;
}

void ControlDinoFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_DINO >= RUNNING_FRAMES)
	{
		frame = 0;
	}
}

void ControlBatFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY >= FLYING_FRAMES)
	{
		frame = 0;
	}
}

void ControlGolemFrame(int &frame)
{
	frame +=FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY >= 12)
	{
		frame = 0;
	}
}

void ControlItemFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / 5 >= 12)
	{
		frame = 0;
	}
}

void DrawPlayerScore(LTexture& gTextTexture,
	LTexture& gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont, 
	const int& score)
{
	gTextTexture.Render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
	if (gScoreTexture.LoadFromRenderedText(to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
}

void DrawPlayerHighScore(LTexture& gTextTexture,
	LTexture& gHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const string& HighScore)
{
	gTextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
	if (gHighScoreTexture.LoadFromRenderedText(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
	}
}

void DrawDeath(LTexture& gTextTexture,
	LTexture& gDeathTexture,
	SDL_Color textColor,
	SDL_Renderer* gRenderer,
	TTF_Font* gFont,
	const int& deathCount) 
{
	gTextTexture.Render(TEXT_3_POSX, TEXT_3_POSY, gRenderer);
	if (gDeathTexture.LoadFromRenderedText(to_string(deathCount), gFont, textColor, gRenderer))
	{
		gDeathTexture.Render(DEADTH_COUNT_POSX, DEADTH_COUNT_POSY, gRenderer);
	}
}

void DrawEndGameSelection(LTexture& gLoseTexture,
	SDL_Event *e,
	SDL_Renderer *gRenderer,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while(!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
						case SDLK_SPACE:
							End_Game = true;
							break;
						case SDLK_ESCAPE:
							End_Game = true;
							Play_Again = false;
							break;
					}
				}
			}

			gLoseTexture.Render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
}

    