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

    speed = start_speed;
}

void player::walk(Tilemap &map){
    pre_pos_x = pos_x;
    pre_pos_y = pos_y;
    std::cout<<pos_x<<" "<<pos_y <<'\n';
    if(key_state[ALLEGRO_KEY_UP]){
        pos_y -= speed;
        dir = UP;
        if(map.IsPathBlocked(cur_tile_i-1,cur_tile_j)){
            pos_y = pre_pos_y;
        }
    }
    else if(key_state[ALLEGRO_KEY_DOWN]){
        pos_y += speed;
        dir = DOWN;
        if(map.IsPathBlocked(cur_tile_i+1,cur_tile_j)){
            pos_y = pre_pos_y;
        }
    }
    else if(key_state[ALLEGRO_KEY_LEFT]){
        pos_x -= speed;
        dir = LEFT;
        if(map.IsPathBlocked(cur_tile_i,cur_tile_j-1)){
            pos_x = pre_pos_x;
        }
    }
    else if(key_state[ALLEGRO_KEY_RIGHT]){
        pos_x += speed;
        dir = RIGHT;
        if(map.IsPathBlocked(cur_tile_i,cur_tile_j+1)){
            pos_x = pre_pos_x;
        }
    }
    std::cout<<pos_x<<" "<<pos_y <<'\n';
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
