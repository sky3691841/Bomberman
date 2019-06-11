#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "init.hpp"

class MenuScene {
private:
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

public:
	MenuScene();
	~MenuScene();
	void start();
};

#endif

