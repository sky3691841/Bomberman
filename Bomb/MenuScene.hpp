#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "init.hpp"
#include "Animation.hpp"

class MenuScene {
private:
	// variables
	bool exit_scene;
	bool play;

	ALLEGRO_COLOR color_white;
	ALLEGRO_COLOR color_black;

	int height1;
	int height2;

	// functions
	void update();
	void draw();
	void on_key_down(int key_state);

	// for animation
	Animation anim_bomb;
	Animation anim_airship;
	float balloon_x, balloon_y;
	float balloon_speed;
	float airship1_x;
	float airship1_speed;
	float airship2_x;
	float airship2_speed;
	int dir_y;

public:
	MenuScene();
	~MenuScene();
	void start();
};

#endif

