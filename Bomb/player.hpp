#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tilemap.hpp"
#include "init.hpp"
#include "Animation.hpp"
//to be revised
#define start_pos_x 75
#define start_pos_y 150
#define start_speed 4

class player{
protected:
    int pos_x, pos_y;
    int pre_pos_x, pre_pos_y;
    int cur_tile_i, cur_tile_j;
    int speed;
    int dir;
    Animation anim[4];

public:

    player();
    ~player();
    void initial(int ,int);
    void walk(Tilemap &map);
    void draw();
    void update(Tilemap &map);
    void put_bomb(Tilemap &map);
    //bool haveobstacles(Tilemap map, int x, int y);

};


#endif
