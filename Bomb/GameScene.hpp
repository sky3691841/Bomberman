#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "init.hpp"
#include "Tilemap.hpp"
#include "Enemy.hpp"

class GameScene {
private:
	// objects
	Tilemap map;
	Enemy enemy;

	// groups
	std::list<Enemy> enemy_list;
	std::list<Enemy> enemy_it;

	// variables
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

