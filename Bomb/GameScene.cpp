#include "GameScene.hpp"
#include <stdio.h>

GameScene::GameScene() {
	LoadGameSceneContent();
	al_play_sample(BGM_gamescreen, volBGM / 3, 0, 1, ALLEGRO_PLAYMODE_LOOP, &BGM_gamescreen_id);
	exit_scene = false;

	// init player
	player1.initial(MAP_X0 + TILESIZE + TILESIZE/2, MAP_Y0 + TILESIZE + TILESIZE/2);

	// init tile map
	map.init();

	// init enemy group (read from txt)
	stage1_txt = fopen("Txt_files/stage1.txt", "r");
	fscanf(stage1_txt, "%d", &enemy_num);

	for (int i = 0; i < enemy_num; i++) {
		int enemy_y, enemy_x;
		fscanf(stage1_txt, "%d %d", &enemy_y, &enemy_x);
		Enemy enemy;
		enemy.init(enemy_y, enemy_x);
		enemy_list.push_back(enemy);
	}

	// init game time
	fscanf(stage1_txt, "%d %d", &minutes, &seconds);
	time_left = minutes * 60 + seconds;
	get_game_timer = al_get_time();
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
		scenestate = VICTORY;
	}
	else if (keycode == ALLEGRO_KEY_SPACE ) {
        //put a bomb on the ground
        player1.put_bomb(map);
	}
}

void GameScene::update() {
	// update ememy group
	enemy_it = enemy_list.begin();
	while (enemy_it != enemy_list.end()) {
		(*enemy_it).update(map, player1.GetExplosionList());

		if ((*enemy_it).getActive() == false) {
			enemy_it = enemy_list.erase(enemy_it);
		}
		else {
			enemy_it++;
		}
	}

	if (enemy_list.empty()) {
		exit_scene = true;
		scenestate = VICTORY;
	}

    //update player motion
    player1.update(map);

	// update game time
	if (al_get_time() - get_game_timer >= 1.0) {
		time_left--;

		if (time_left <= 0) {
			exit_scene = true;
			scenestate = GAMEOVER;
		}

		get_game_timer = al_get_time();
	}

}

void GameScene::draw() {
	// draw UI bar
	al_draw_bitmap(UI_bar, 0, 0, 0);

	// draw game time
	al_draw_textf(font_bomberman, al_map_rgb(200, 200, 200), SCREEN_W / 2, 30, ALLEGRO_ALIGN_CENTER, "%02d:%02d", time_left / 60, time_left % 60);
	al_draw_textf(font_bomberman, al_map_rgb(255, 255, 255), SCREEN_W / 2 + 2, 32, ALLEGRO_ALIGN_CENTER, "%02d:%02d", time_left / 60, time_left % 60);

	// draw tilemap
	map.draw();

	//player.draw may be change to animation
	player1.draw();


	// draw enemy group
	for (enemy_it = enemy_list.begin(); enemy_it != enemy_list.end(); enemy_it++) {
		(*enemy_it).draw();
	}


	al_flip_display();
}
