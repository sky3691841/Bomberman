#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tilemap.hpp"
#include "init.hpp"
#include "Animation.hpp"
#include "Bomb.hpp"
#include "Collision.hpp"
#include "content.hpp"
//to be revised
#define start_pos_x 75
#define start_pos_y 150
#define start_speed 4
#define max_bomb_num 2

class player{
protected:
    int x,y;
    int w,h;
    //int pre_x, pre_y;
    //int cur_tile_i, cur_tile_j;
    int posJ, posI;
    int speed;
    int dir;
    int bomb_num;
    Animation anim[4];
    BoundingBox box[4];
    std::list<Bomb> bomb_list;
    std::list<Bomb>::iterator it;

public:

    player();
    ~player();
    void initial(int ,int);
    void walk(Tilemap &map);
    void draw();
    void update(Tilemap &map);
    void put_bomb(Tilemap &map);
    bool PathBlocked(Tilemap &map,int i, int j) ;
    bool Blocked(Tilemap &map,int i, int j);
    //bool haveobstacles(Tilemap map, int x, int y);

};


#endif
