#include "WinScene.hpp"

WinScene::WinScene() {
	LoadVictoryContent();
	al_play_sample(BGM_victory, volBGM / 3, 0, 1, ALLEGRO_PLAYMODE_LOOP, &BGM_victory_id);
	exit_scene = false;

	anim_yellow.Initialize(victory_yellow, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	anim_green.Initialize(victory_green, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	anim_blue.Initialize(victory_blue, 2, ALLEGRO_MSECS_TO_SECS(500), true);
	anim_orange.Initialize(victory_orange, 2, ALLEGRO_MSECS_TO_SECS(500), true);
}

WinScene::~WinScene() {
}

void WinScene::start() {
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

	al_stop_sample(&BGM_victory_id);
	al_stop_timer(timer_FPS);
	UnloadVictoryContent();
}

void WinScene::update() {
	anim_yellow.Update();
	anim_green.Update();
	anim_blue.Update();
	anim_orange.Update();
}

void WinScene::draw() {
	anim_yellow.Draw(0, 0);
	anim_green.Draw(anim_green.Width() + 10, 0);
	anim_blue.Draw(2 * anim_blue.Width() + 13, 0);
	anim_orange.Draw(3 * anim_orange.Width() + 16, 0);
	anim_yellow.Draw(4 * anim_yellow.Width() + 19, 0);
	anim_green.Draw(5 * anim_green.Width() + 22, 0);
	anim_blue.Draw(6 * anim_blue.Width() + 25, 0);
	anim_orange.Draw(7 * anim_orange.Width() + 28, 0);
	al_draw_bitmap(victory_floor, 0, SCREEN_H - height(victory_floor), 0);
	al_draw_bitmap(victory_bomberman, SCREEN_W / 2 - width(victory_bomberman) / 2, 75, 0);
	al_draw_text(font_bomberman, al_map_rgb(255, 255, 255), SCREEN_W / 2, 630, ALLEGRO_ALIGN_CENTER, "PRESS ESC BACK TO MAIN MENU");

	al_flip_display();
}

void WinScene::on_key_down(int keycode) {
	if (keycode == ALLEGRO_KEY_ESCAPE) {
		exit_scene = true;
		scenestate = MAINMENU;
	}
}