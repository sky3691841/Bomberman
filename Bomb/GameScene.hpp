#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "init.hpp"
#include "Tilemap.hpp"
#include "Enemy.hpp"

class GameScene {
private:
	// objects
	FILE* enemy1_txt;
	Tilemap map;

	// groups
	std::list<Enemy> enemy_list;
	std::list<Enemy>::iterator enemy_it;

	// variables
	bool exit_scene;
	int enemy_num;

	// functions
	void update();
	void draw();
	void on_key_down(int keycode);

public:
	GameScene();
	~GameScene();
	void start(); // the game loop, no need to modify

};

#endif // GAMESCENE_HPP

