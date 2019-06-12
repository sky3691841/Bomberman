#include "GameScene.hpp"

GameScene::GameScene() {
	LoadGameSceneContent();
	al_play_sample(BGM_gamescreen, volBGM / 3, 0, 1, ALLEGRO_PLAYMODE_LOOP, &BGM_gamescreen_id);
	exit_scene = false;
	
	// init tile map
	map.init();

	// init enemy group (read from txt)
	enemy1_txt = fopen("Txt_files/enemy1.txt", "r");
	fscanf(enemy1_txt, "%d", &enemy_num);

	for (int i = 0; i < enemy_num; i++) {
		int enemy_y, enemy_x;
		fscanf(enemy1_txt, "%d %d", &enemy_y, &enemy_x);
		Enemy enemy;
		enemy.init(enemy_y, enemy_x);
		enemy_list.push_back(enemy);
	}
}

GameScene::~GameScene() {
}

// this is the gameloop, no need to modify
void GameScene::start() {
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

	al_stop_sample(&BGM_gamescreen_id);
	al_stop_timer(timer_FPS);
	UnloadGameSceneContent();
}

// this is for single key press, movement should be handled in update
void GameScene::on_key_down(int keycode) {
	if (keycode == ALLEGRO_KEY_ESCAPE) {
		exit_scene = true;
		scenestate = MAINMENU;
	}
	else if (keycode == ALLEGRO_KEY_TAB) {
		debug_mode = !debug_mode;
	}
	// for debug purpose, delete later
	else if (keycode == ALLEGRO_KEY_LCTRL) {
		exit_scene = true;
		scenestate = GAMEOVER;
	}
}

void GameScene::update() {
	// update ememy group
	for (enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++) {
		(*enemy_it).update(map);
	}
}

void GameScene::draw() {
	// draw UI bar
	al_draw_bitmap(UI_bar, 0, 0, 0);
	// draw tilemap
	map.draw();

	// draw enemy group
	for (enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++) {
		(*enemy_it).draw();
	}

	al_flip_display();
}