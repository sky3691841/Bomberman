#include "Enemy.hpp"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::init(int i, int j) {
	anim[UP].Initialize(game_enemy_up, 4, 0.1, true);
	anim[DOWN].Initialize(game_enemy_down, 4, 0.1, true);
	anim[LEFT].Initialize(game_enemy_left, 4, 0.1, true);
	anim[RIGHT].Initialize(game_enemy_right, 4, 0.1, true);

	// track tile count
	pos_x = i;
	pos_y = j;

	// real position
	x = MAP_X0 + j * TILESIZE + TILESIZE / 2;
	y = MAP_Y0 + i * TILESIZE + TILESIZE / 2;

	speed = ENEMY_SPEED;
	dir = rand() % 4;
}

void Enemy::update() {
}

void Enemy::draw() {
	anim[dir].Draw(x, y - 15, 0.8, 0.8, 0.0, al_map_rgb(255, 255, 255));
}