#ifndef ENEMY_HPP
# define ENEMY_HPP

#include "init.hpp"
#include "Animation.hpp"
#include "Tilemap.hpp"

#define ENEMY_NUM 3
#define ENEMY_SPEED 1

// enemy walking and choosing new direction
enum ENEMY_STATES {STATE_WALKING, STATE_CHOOSING};

class Enemy {
private:
	Animation anim[4];

	int pos_y;
	int pos_x;
	int x;
	int y;
	int dir;
	int speed;

	int state;
	int paths_available;
	bool available_dir[4];
public:
	// basic functions
	Enemy();
	~Enemy();
	void init(int i, int j);
	void update(Tilemap &map);
	void draw();

	// other functions
	void WalkCurrentDir(); // handle basic walking
	bool OnTileCenter(); // check if enemy is on the center of tile map
	void CountPaths(Tilemap &map); // count paths availabe
	void Move(Tilemap &map); // handle enemy movement
};


#endif // ENEMY_HPP

