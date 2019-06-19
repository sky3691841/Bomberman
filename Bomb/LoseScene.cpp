#include "LoseScene.hpp"

LoseScene::LoseScene() {
	LoadGameoverContent();
	al_play_sample(BGM_gameover, volBGM / 3, 0, 1, ALLEGRO_PLAYMODE_LOOP, &BGM_gameover_id);
	exit_scene = false;

	anim_man.Initialize(gameover_animation, 4, ALLEGRO_MSECS_TO_SECS(150), true);
}

LoseScene::~LoseScene() {
}

void LoseScene::start() {
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

	al_stop_sample(&BGM_gameover_id);
	al_stop_timer(timer_FPS);
	UnloadGameoverContent();
}

void LoseScene::update() {
	anim_man.Update();
}

void LoseScene::draw() {
	al_draw_bitmap(gameover_bg, 0, 0, 0);
	al_draw_bitmap(gameover_title, SCREEN_W / 2 - width(gameover_title) / 2, 150, 0);
	anim_man.Draw(SCREEN_W / 2, SCREEN_H / 2 + 50, 1.2, 1.2, 0.0, al_map_rgb(255, 255, 255));
	al_draw_text(font_bomberman, al_map_rgb(255, 255, 255), SCREEN_W / 2, 630, ALLEGRO_ALIGN_CENTER, "PRESS ESC BACK TO MAIN MENU");

	al_flip_display();
}

void LoseScene::on_key_down(int keycode) {
	if (keycode == ALLEGRO_KEY_ESCAPE) {
		exit_scene = true;
		scenestate = MAINMENU;
	}
}
