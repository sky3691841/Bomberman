#include "player.hpp"

#include <math.h>
#include <iostream>

player::player(){
}
player::~player(){

}
void player::initial(int x,int y){
    std::cout << "in\n";
    //pos_x = start_pos_x;
    std::cout << "in\n";
    //pos_y = start_pos_y;
    //speed = 4;
}
bool haveobstacles(Tilemap map, int x, int y){

    return false;
}
void player::walk(Tilemap &map){
    if(key_state[ALLEGRO_KEY_UP]){

    }
    else if(key_state[ALLEGRO_KEY_DOWN]){

    }
    else if(key_state[ALLEGRO_KEY_LEFT]){

    }
    else if(key_state[ALLEGRO_KEY_RIGHT]){

    }
}
void player::draw(){
    //the number 100 must be substitude by pos_x
    //pos_x = start_pos_x;
    al_draw_bitmap(player_static,round(start_pos_x-al_get_bitmap_width(player_static)/2),round(start_pos_y-al_get_bitmap_height(player_static)/2),0);
}
