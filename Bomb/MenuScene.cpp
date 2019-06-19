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

	// for animation
	anim_bomb.Initialize(game_bomb, 4, ALLEGRO_MSECS_TO_SECS(150), true);
	anim_airship.Initialize(main_airship2, 16, ALLEGRO_MSECS_TO_SECS(80), true);
	balloon_x = 100;
	balloon_y = 100;
	balloon_speed = 0.8;
	airship1_x = 225;
	airship1_speed = 0.6;
	airship2_x = 675;
	airship2_speed = 0.7;
	dir_y = 1;
}

MenuScene::~MenuScene() {
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

	al_stop_sample(&BGM_mainmenu_id);
	al_stop_timer(timer_FPS);

	UnloadMainmenuContent();
}

void MenuScene::update() {
	// for animation
	anim_bomb.Update();
	anim_airship.Update();

	balloon_y += dir_y * 0.2;
	if (balloon_y <= 95 || balloon_y >= 105)
		dir_y *= -1;

	balloon_x += balloon_speed;
	airship1_x += airship1_speed;
	airship2_x -= airship2_speed;

	if (balloon_x > SCREEN_W + 300)
		balloon_x = -width(main_balloon);
	if (airship1_x > SCREEN_W + 200)
		airship1_x = -width(main_airship1);
	if (airship2_x + anim_airship.Width() < -100)
		airship2_x = SCREEN_W;
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
			scenestate = GAMESCENE;
		}
	}
}

void MenuScene::draw() {
	al_draw_bitmap(main_bg, 0, 0, 0);
	// for animation ============
	al_draw_bitmap(main_balloon, balloon_x, balloon_y, 0);
	al_draw_bitmap(main_airship1, airship1_x, 475, 0);
	anim_airship.Draw(airship2_x, 275);
	// ===========================
	al_draw_scaled_bitmap(main_title, 0, 0, width(main_title), height(main_title), 125, 25, 650, 450, 0);

	al_draw_text(font_menu, color_black, SCREEN_W / 2, height1, ALLEGRO_ALIGN_CENTER, "PLAY");
	al_draw_text(font_menu, color_white, SCREEN_W / 2 + 2, height1 + 2, ALLEGRO_ALIGN_CENTER, "PLAY");
	al_draw_text(font_menu, color_black, SCREEN_W / 2, height2, ALLEGRO_ALIGN_CENTER, "EXIT");
	al_draw_text(font_menu, color_white, SCREEN_W / 2 + 2, height2 + 2, ALLEGRO_ALIGN_CENTER, "EXIT");

	if (play)
		anim_bomb.Draw(360, height1 + 10, 1.0, 1.0, 0.0, al_map_rgb(255, 255, 255));
	else
		anim_bomb.Draw(360, height2 + 10, 1.0, 1.0, 0.0, al_map_rgb(255, 255, 255));

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

