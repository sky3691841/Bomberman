#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "init.hpp"

#define TILES_H 13
#define TILES_W 19
#define TILESIZE 50

#define MAP_X0 0
#define MAP_Y0 100

enum TILE_ID {GRASS = 0, BRICK = 1, BLOCK = 2};

class Tilemap {
private:
	// Tilemap background
	FILE* map_txt;
	int map[TILES_H][TILES_W];

	bool enemy_map[TILES_H][TILES_W];
	
public:
	// basic functions
	Tilemap();
	~Tilemap();
	void init();
	void draw();

	// other functions
	int GetTileID(int i, int j); // get status of tile
	int GetEnemyPos(int i, int j);
	void SetEnemyPos(int i, int j, bool value);

	bool IsPathBlocked(int i, int j);
};

#endif // TILEMAP_HPP

