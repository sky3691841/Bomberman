#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "init.hpp"
#include "Tilemap.hpp"
#include "player.hpp"
class player;
class GameScene {
private:
	// variables
	player *player1;
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

