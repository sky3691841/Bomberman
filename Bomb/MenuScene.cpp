#include "MenuScene.hpp"

// try to write by class

MenuScene::MenuScene() {
	LoadMainmenuContent();
	al_play_sample(BGM_mainmenu, volBGM / 3, 0, 1, ALLEGRO_PLAYMODE_LOOP, &BGM_mainmenu_id);
	exit_scene = false;
	play = true;
	color_black = al_map_rgb(0, 0, 0);
	color_white = al_map_rgb(255, 255, 255);
	height1 = 560;
	height2 = 630;
}

MenuScene::~MenuScene() {
	al_stop_sample(&BGM_mainmenu_id);
	al_stop_timer(timer_FPS);

	UnloadMainmenuContent();
}

void MenuScene::start() {
	redraws = 0;
	al_start_timer(timer_FPS);

	//=============================
	//GAMELOOP
	//=============================
	while (!exit_program && !exit_scene) {
		al_wait_for_event(event_queue, &game_event);
		if (game_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit_program = true;
		}
		if (game_event.type == ALLEGRO_EVENT_TIMER) {
			if (game_event.timer.source == timer_FPS) {
				redraws++;
			}
		}
		else if (game_event.type == ALLEGRO_EVENT_KEY_DOWN) {
			key_state[game_event.keyboard.keycode] = true;
			on_key_down(game_event.keyboard.keycode);
		}
		else if (game_event.type == ALLEGRO_EVENT_KEY_UP) {
			key_state[game_event.keyboard.keycode] = false;
		}

		// Redraw
		if (redraws > 0 && al_is_event_queue_empty(event_queue))
		{
			// UPDATE GAME
			update();
			// DRAW GAME
			draw();

			redraws = 0;
		}
	}
}

void MenuScene::update() {
	
}

void MenuScene::on_key_down(int keycode) {
	if (keycode == ALLEGRO_KEY_ESCAPE) {
		exit_program = true;
	}
	else if (keycode == ALLEGRO_KEY_UP || keycode == ALLEGRO_KEY_DOWN) {
		play = !play;
		al_play_sample(SFX_menusound1, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else if (keycode == ALLEGRO_KEY_ENTER) {
		al_play_sample(SFX_menusound2, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		if (!play)
			exit_program = true;
		else {
			exit_scene = true;
			screenstate = GAMESCENE;
		}
	}
}

void MenuScene::draw() {
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

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

