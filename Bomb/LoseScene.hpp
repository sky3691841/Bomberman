#ifndef LOSESCENE_HPP
#define LOSESCENE_HPP

#include "init.hpp"
#include "Animation.hpp"

class LoseScene {
private:
	// variables
	Animation anim_man;
	bool exit_scene;

	// functions
	void update();
	void draw();
	void on_key_down(int keycode);

public:
	LoseScene();
	~LoseScene();
	void start();
};

#endif // LOSESCENE_HPP

