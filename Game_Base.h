#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "common.h"

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define SMALL_BUTTON 1
#define  COMMON_BUTTON 2

#define TIME_MAX 1000
#define GROUND 400
#define MAX_HEIGHT 260

#define BASE_OFFSET_SPEED 0

#define GROUND_SPEED 5
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define SLOW_FRAME_DINO 2
#define SLOW_FRAME_ITEM 3
#define SLOW_FRAME_ENEMY 4

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SPEED_UP 1
#define SCORE_UP 1
#define TIME_UP 1
#define FRAME_UP 1

#define IN_AIR_ENEMY  1
#define ITEM 0
#define GOLEM 2
#define DINO  0
#define MINOTOUR1  1
#define MINOTOUR2 2
#define MINOTOUR3  3
void LogError(string msg, int error_code = SDL_ERROR);
const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 57;
const int SMALL_BUTTON_HEIGHT = 57;

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const int PLAY_BUTON_POSX = 389;
const int PLAY_BUTTON_POSY= 186;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 292;
const int EXIT_BUTTON_POSX = 389;
const int EXIT_BUTTON_POSY = 402;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;
const int SOUND_BUTTON_POSX = 31;
const int SOUND_BUTTON_POSY = 89;

const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;

const int TEXT_1_POSX = 670;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 80;
const int TEXT_3_POSX = 670;
const int TEXT_3_POSY = 140;
const int SCORE_POSX = 845;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 845;
const int HIGH_SCORE_POSY = 80;
const int DEADTH_COUNT_POSX = 770;
const int DEADTH_COUNT_POSY = 140;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.2; 
const double LAYER_3_SPEED = 0.4;
const double LAYER_4_SPEED = 0.6;
const double LAYER_5_SPEED = 0.8;
const double LAYER_6_SPEED = 1.00;
const double LAYER_7_SPEED = 1.2;
const double LAYER_8_SPEED = 1.4;
const double LAYER_9_SPEED = 1.6;

const int RUNNING_FRAMES = 6;
const int FLYING_FRAMES = 5;
const int BACKGROUND_LAYER = 9;


const string WINDOW_TITLE = "Dinosaur Run";

enum ButtonMenu
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2

};

