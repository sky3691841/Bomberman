#include "player.hpp"

#include <math.h>
#include <iostream>

player::player(){
}
player::~player(){

}
void player::initial(int x,int y){
    pos_x = x;
    pos_y = y;

    this->dir = DOWN;
    this->anim[UP].Initialize(game_player_up, 4, 0.1, true);
    this->anim[DOWN].Initialize(game_player_down, 4, 0.1, true);
    this->anim[LEFT].Initialize(game_player_left, 4, 0.1, true);
    this->anim[RIGHT].Initialize(game_player_right, 4, 0.1, true);

    speed = 4;
}

void player::walk(Tilemap &map){
    if(key_state[ALLEGRO_KEY_UP]){
        if(!map.IsPathBlocked(pos_x,pos_y))
            pos_y -= speed;
        dir = UP;
    }
    else if(key_state[ALLEGRO_KEY_DOWN]){
        if(!map.IsPathBlocked(pos_x,pos_y)){
            pos_y += speed;
        }
        dir = DOWN;
    }
    else if(key_state[ALLEGRO_KEY_LEFT]){
        if(!map.IsPathBlocked(pos_x,pos_y))
            pos_x -= speed;
        dir = LEFT;
    }
    else if(key_state[ALLEGRO_KEY_RIGHT]){
        if(!map.IsPathBlocked(pos_x,pos_y))
            pos_x += speed;
        dir = RIGHT;
    }
}
void player::update(Tilemap &map){
    cur_tile_i = (pos_y - MAP_Y0) / TILESIZE;
    cur_tile_j = (pos_x - MAP_X0) / TILESIZE;

    walk(map);
    anim[dir].Update();

    //bomb

    //explode effect
}
void player::draw(){
    //pos_x = start_pos_x;
    anim[dir].Draw(pos_x, pos_y-15, 0.9, 0.9, 0, al_map_rgba(255, 255, 255, 255));
}
