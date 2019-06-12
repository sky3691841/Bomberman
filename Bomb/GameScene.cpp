#include "GameScene.hpp"

GameScene::GameScene() {
	LoadGameSceneContent();
	exit_scene = false;
	
	// init tile map
	map.init();

	// init enemy group
	for (int i = 0; i < ENEMY_NUM; i++) {
		Enemy enemy;
		switch (i) {
		case(0):
			enemy.init(9, 5);
			break;
		case(1):
			enemy.init(1, 7);
			break;
		case(2):
			enemy.init(8, 11);
			break;
		}
		enemy_list.push_back(enemy);
	}
	
	// play sample
}

GameScene::~GameScene() {
	al_stop_timer(timer_FPS);
}

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

	al_stop_timer(timer_FPS);
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
}

void GameScene::update() {
	// update ememy group
	for (enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++) {
		(*enemy_it).update(map);
	}
}

void GameScene::draw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	// draw tilemap
	map.draw();

	// draw enemy group
	for (enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++) {
		(*enemy_it).draw();
	}

	al_flip_display();
}