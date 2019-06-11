#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "init.hpp"

#define TILES_H 13
#define TILES_W 19
#define TILESIZE 50

enum TILE_ID {GRASS = 0, BRICK = 1, BLOCK = 2};

class Tilemap {
private:
	// Tilemap background
	FILE* map_txt;
	int map[TILES_H][TILES_W];

public:
	Tilemap();
	~Tilemap();
	void init();
	void draw();

};

#endif // TILEMAP_HPP

