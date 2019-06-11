#ifndef INIT_HPP
#define INIT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_physfs.h>
//#include <physfs.h>

#include <list>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "content.hpp"

#define DEBUG 1
extern bool debug_mode;

// ENUMS
enum STATE{ MAINMENU, GAMESCREEN, VICTORY, GAMEOVER };
enum DIRECTION { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

// Globals
const int SCREEN_W = 950;
const int SCREEN_H = 750;
const double FPS = 60;
extern int screenstate;
extern bool exit_program;
extern int redraws;
extern float volBGM;
extern float volSFX;

extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* event_queue;
extern ALLEGRO_EVENT game_event;
extern ALLEGRO_TIMER* timer_FPS;
extern ALLEGRO_BITMAP* icon;
extern ALLEGRO_KEYBOARD_STATE keystate;

// Functions
void init();
void destroy();
int width(ALLEGRO_BITMAP* img);
int height(ALLEGRO_BITMAP* img);
// void fade(int r, int g, int b, float speed);
int max(int a, int b);
int min(int a, int b);
int oposite_direction(int dir);

#endif
