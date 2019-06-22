#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

#include "init.hpp"
#include "Animation.hpp"
#include "Tilemap.hpp"

#define start_countdown 2.5

class Bomb{
protected:
    Animation anim;
    int pos_x, pos_y;
    int tile_i, tile_j;

    float timer;
    float time_until_exploded;
    bool appear;

public:
    Bomb(){ }
    ~Bomb(){ }
    void initial(int x, int y, float countdown, Tilemap &map);
    void update(Tilemap &map);
    void draw();
    void exploded(Tilemap &map);
    bool CheckObstaclesOnTile(Tilemap &map, int i, int j);
    int getx(){return pos_x;}
    int gety(){return pos_y;}
    int get_tile_i(){return tile_i;}
    int get_tile_j(){return tile_j;}
    bool get_appear(){return appear;}
};

#endif
