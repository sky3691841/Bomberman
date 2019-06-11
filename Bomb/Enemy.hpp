#ifndef ENEMY_HPP
# define ENEMY_HPP

#include "init.hpp"
#include "Animation.hpp"
#include "Tilemap.hpp"

#define ENEMY_SPEED 1

class Enemy {
private:
	Animation anim[4];

	int pos_x;
	int pos_y;
	int x;
	int y;
	int dir;
	int speed;
public:
	Enemy();
	~Enemy();
	void init(int i, int j);
	void update();
	void draw();
};


#endif // ENEMY_HPP

