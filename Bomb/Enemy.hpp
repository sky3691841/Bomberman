#ifndef ENEMY_HPP
# define ENEMY_HPP

#include "init.hpp"
#include "Animation.hpp"
#include "Tilemap.hpp"

#define ENEMY_SPEED 1

// enemy walking and choosing new direction
enum ENEMY_STATES {STATE_WALKING, STATE_CHOOSING};

class Enemy {
private:
	Animation anim[4];

	int pos_i;
	int pos_j;
	int x;
	int y;
	int dir;
	int speed;

	int state;
	int paths_available;
	bool available_dir[4];
public:
	Enemy();
	~Enemy();
	void init(int i, int j);
	void update(Tilemap &map); // only movement for now, should handle explosion in the future
	void draw();

	/// functions for enemy movement ==============
	void WalkCurrentDir(); // handle basic walking
	bool OnTileCenter(); // check if enemy is on the center of tile map
	void CountPaths(Tilemap &map); // count paths availabe
	void Move(Tilemap &map); // handle enemy movement
	/// ===========================================
};


#endif // ENEMY_HPP

