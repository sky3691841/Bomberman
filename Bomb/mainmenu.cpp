#include "mainmenu.hpp"

void mainmenu()
{
	// Initialize contents to be used
	LoadMainmenuContent();
	redraws = 0;
	// ===========================

	// variables ==============
	bool exit_screen = false;
	bool play = true;

	ALLEGRO_COLOR color_black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR color_white = al_map_rgb(255, 255, 255);

	int height1 = 560;
	int height2 = 630;
	//======================

	al_play_sample(BGM_mainmenu, volBGM / 3, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	al_start_timer(timer_FPS);

	//=============================
	//GAMELOOP
	//=============================
	while (!exit_program && !exit_screen)
	{
		//=================================
		//UPDATE
		//=================================

		al_wait_for_event(event_queue, &game_event);

		if (game_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit_program = true;
		}

		if(game_event.type == ALLEGRO_EVENT_TIMER)
		{
			if (game_event.timer.source == timer_FPS) {
				redraws++;
			}
		}
		else if (game_event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (game_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				exit_program = true;
			}
			else if (game_event.keyboard.keycode == ALLEGRO_KEY_UP || game_event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
				play = !play;
				al_play_sample(SFX_menusound1, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (game_event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				al_play_sample(SFX_menusound2, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				if (!play)
					exit_program = true;
				else {
					exit_screen = true;
					screenstate = GAMESCREEN;
				}
			}
		}

		//=================================
		//DRAW
		//=================================
		if (redraws > 0 && al_is_event_queue_empty(event_queue))
		{
			//=====================
			// DRAW GAME

			al_draw_bitmap(main_bg, 0, 0, 0);
			al_draw_scaled_bitmap(main_title, 0, 0, width(main_title), height(main_title), 125, 25, 650, 450, 0);

			if (play) {
				al_draw_text(font_menu, color_white, SCREEN_W / 2 + 2, height1, ALLEGRO_ALIGN_CENTER, "PLAY");
				al_draw_text(font_menu, color_black, SCREEN_W / 2 + 2, height2, ALLEGRO_ALIGN_CENTER, "EXIT");
			}
			else {
				al_draw_text(font_menu, color_black, SCREEN_W / 2 + 2, height1, ALLEGRO_ALIGN_CENTER, "PLAY");
				al_draw_text(font_menu, color_white, SCREEN_W / 2 + 2, height2, ALLEGRO_ALIGN_CENTER, "EXIT");
			}
			
			

			redraws = 0;

			//=====================

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	// Exit
	al_stop_timer(timer_FPS);
	UnloadMainmenuContent();
}
