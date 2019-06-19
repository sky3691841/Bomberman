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
	pos_y = i;
	pos_x = j;

	// real position
	x = MAP_X0 + j * TILESIZE + TILESIZE / 2;
	y = MAP_Y0 + i * TILESIZE + TILESIZE / 2;

	speed = ENEMY_SPEED;
	dir = rand() % 4;
	state = STATE_CHOOSING;
}

void Enemy::update(Tilemap &map) {
	anim[dir].Update();
	Move(map);
}

void Enemy::draw() {
	anim[dir].Draw(x, y - 15, 0.8, 0.8, 0.0, al_map_rgb(255, 255, 255));

	// Debug mode
	if (debug_mode) {
		al_draw_filled_circle(x, y, 3, al_map_rgb(0, 255, 0));
		al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), x + 10, y + 10, ALLEGRO_ALIGN_RIGHT, "State %d", state);
		al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), x + 10, y + 20, ALLEGRO_ALIGN_RIGHT, "Paths %d", paths_available);
	}
}

void Enemy::WalkCurrentDir() {
	if (dir == UP)
		y -= speed;
	else if (dir == DOWN)
		y += speed;
	else if (dir == LEFT)
		x -= speed;
	else if (dir == RIGHT)
		x += speed;
}

bool Enemy::OnTileCenter() {
	return ((x - MAP_X0) % (TILESIZE) == TILESIZE / 2 && (y - MAP_Y0) % (TILESIZE) == TILESIZE / 2);
}

void Enemy::CountPaths(Tilemap &map) {
	// reset
	paths_available = 0;
	for (int i = 0; i < 4; i++) {
		available_dir[i] = 0;
	}

	// check paths
	if (!map.IsPathBlocked(pos_y - 1, pos_x)) {
		paths_available++;
		available_dir[UP] = true;
	}
	if (!map.IsPathBlocked(pos_y + 1, pos_x)) {
		paths_available++;
		available_dir[DOWN] = true;
	}
	if (!map.IsPathBlocked(pos_y, pos_x - 1)) {
		paths_available++;
		available_dir[LEFT] = true;
	}
	if (!map.IsPathBlocked(pos_y, pos_x + 1)) {
		paths_available++;
		available_dir[RIGHT] = true;
	}
}

void Enemy::Move(Tilemap &map) {
	// update enemy map
	map.SetEnemyPos(pos_y, pos_x, false);
	pos_y = (y - MAP_Y0) / TILESIZE;
	pos_x = (x - MAP_X0) / TILESIZE;
	map.SetEnemyPos(pos_y, pos_x, true);

	// count # of available paths
	CountPaths(map);

	// walking
	if (state == STATE_WALKING) {
		WalkCurrentDir();

		if (OnTileCenter()) {
			// if path is blocked or reach crossroad
			if ((dir == UP && map.IsPathBlocked(pos_y - 1, pos_x))
				|| (dir == DOWN && map.IsPathBlocked(pos_y + 1, pos_x))
				|| (dir == LEFT && map.IsPathBlocked(pos_y, pos_x - 1))
				|| (dir == RIGHT && map.IsPathBlocked(pos_y, pos_x + 1))
				|| (paths_available > 2 && rand() % 100 <= 30)) {
				state = STATE_CHOOSING;
			}
		}
	}
	// choosing new path
	else {
		// all paths are blocked, can't move
		if (paths_available == 0) {
		}
		// only one path available
		else if (paths_available == 1) {
			for (int i = 0; i < 4; i++) {
				if (available_dir[i] == true) {
					dir = i;
					break;
				}
			}

			state = STATE_WALKING;
		}
		// two paths or above available
		else {
			// choose random direction instead of original path
			for (int i = rand() % 4; ; i = rand() % 4) {
				if (available_dir[i] == true && i != oposite_direction(dir)) {
					dir = i;
					break;
				}
			}

			state = STATE_WALKING;
		}
	}
}
