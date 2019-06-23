#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "init.hpp"

#define TILES_H 13
#define TILES_W 19
#define TILESIZE 50

#define MAP_X0 0
#define MAP_Y0 100

// Grass is to walk on, Brick can be destroyed by bomb, Block can't be destroyed
enum TILE_ID {GRASS = 0, BRICK = 1, BLOCK = 2};

class Tilemap {
private:
	// Tilemap background
	FILE* map_txt;
	int map[TILES_H][TILES_W];

	bool enemy_map[TILES_H][TILES_W];
	bool bomb_map[TILES_H][TILES_W];

public:
	// basic functions
	Tilemap();
	~Tilemap();
	void init();
	void draw();

	// other functions
	int GetTileID(int i, int j); // get status of tile
	void SetTileID(int i, int j, int ID) { map[i][j] = ID; }
	int GetEnemyPos(int i, int j);
	void SetEnemyPos(int i, int j, bool value);
	int GetBombPos(int i, int j);
	void SetBombPos(int i, int j, bool value);
	bool IsPathBlocked(int i, int j);
};

#endif // TILEMAP_HPP

