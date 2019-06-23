#ifndef WINSCENE_HPP
#define WINSCENE_HPP

#include "init.hpp"
#include "Animation.hpp"

class WinScene {
private:
	// variables
	Animation anim_yellow;
	Animation anim_green;
	Animation anim_blue;
	Animation anim_orange;

	bool exit_scene;

	// functions
	void update();
	void draw();
	void on_key_down(int keycode);

public:
	WinScene();
	~WinScene();
	void start();
};

#endif // WINSCENE_HPP

