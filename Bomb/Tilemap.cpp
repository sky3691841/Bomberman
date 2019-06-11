#include "Tilemap.hpp"
#include <iostream>

using namespace std;

Tilemap::Tilemap() {
}

Tilemap::~Tilemap() {
}

void Tilemap::init() {
	map_txt = fopen("Txt_files/map.txt", "r");
	if (!map_txt) {
		cout << "map.txt failed loading" << endl;
	}

	if (map_txt) {
		for (int i = 0; i < TILES_H; i++) {
			for (int j = 0; j < TILES_W; j++) {
				fscanf(map_txt, "%d", &map[i][j]);
			}
		}
	}
}

void Tilemap::draw() {
	for (int i = 0; i < TILES_H; i++) {
		for (int j = 0;j < TILES_W; j++) {
			al_draw_bitmap(game_tile[map[i][j]], MAP_X0 + j * TILESIZE, MAP_Y0 + i * TILESIZE, 0);
		}
	}
}
