#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "init.hpp"
#include "Tilemap.hpp"

class GameScene {
private:
	// variables
	Tilemap map;
	bool exit_scene;

	// functions
	void update();
	void draw();
	void on_key_down(int keycode);

public:
	GameScene();
	~GameScene();
	void start();

};

#endif // GAMESCENE_HPP

