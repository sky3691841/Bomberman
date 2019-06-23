#ifndef ENEMY_HPP
# define ENEMY_HPP

#include "init.hpp"
#include "Animation.hpp"
#include "Tilemap.hpp"
#include "Collision.hpp"
#include "Explosion.hpp"

#define ENEMY_SPEED 1

// enemy walking and choosing new direction
enum ENEMY_STATES {STATE_WALKING, STATE_CHOOSING};

class Enemy {
private:
	Animation anim[4];
	BoundingBox box[4];

	int pos_i;
	int pos_j;
	int x;
	int y;
	int dir;
	int speed;

	int state;
	int paths_available;
	bool available_dir[4];

	bool active;
public:
	Enemy();
	~Enemy();
	void init(int i, int j);
	void update(Tilemap &map, std::list<Explosion> explosion_list);
	void draw();

	/// functions for enemy movement ==============
	void WalkCurrentDir(); // handle basic walking
	bool OnTileCenter(); // check if enemy is on the center of tile map
	void CountPaths(Tilemap &map); // count paths availabe
	void Move(Tilemap &map); // handle enemy movement
	/// ===========================================

	bool CollisionWith(Tilemap &map, int i, int j);
	bool getActive() { return active; }
	int get_posi(){return pos_i;}
	int get_posj(){return pos_j;}
	BoundingBox GetBox() { return box[dir]; }
};


#endif // ENEMY_HPP

