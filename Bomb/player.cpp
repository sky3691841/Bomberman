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

    this->speed = start_speed;
    this->bomb_num = max_bomb_num;
}

void player::walk(Tilemap &map){
    pre_pos_x = pos_x;
    pre_pos_y = pos_y;
    //std::cout<<pos_x<<" "<<pos_y <<'\n';
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
    //std::cout<<pos_x<<" "<<pos_y <<'\n';
}
void player::update(Tilemap &map){
    cur_tile_i = (pos_y - MAP_Y0) / TILESIZE;
    cur_tile_j = (pos_x - MAP_X0) / TILESIZE;

    walk(map);
    anim[dir].Update();

    //bomb
    for(it = bomb_list.begin(); it != bomb_list.end(); it++){
        it->update(map);

        if(it->get_appear()){
            //set explosion

            it = bomb_list.erase(it);
        }
    }

    //explode effect
}

void player::put_bomb(Tilemap &map){
    if(bomb_list.size() < (unsigned)bomb_num && map.GetBombPos(cur_tile_i, cur_tile_j) == 0){
        al_play_sample(SFX_put_bomb, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        Bomb add;
        add.initial(((pos_x-MAP_X0)/TILESIZE)*TILESIZE + MAP_X0 + TILESIZE/2, ((pos_y-MAP_Y0)/TILESIZE)*TILESIZE + TILESIZE/2 + MAP_Y0, start_countdown, map);
        bomb_list.push_back(add);

    }
}

void player::draw(){
    //bomb
    for(it = bomb_list.begin(); it != bomb_list.end(); it++){
        it->draw();
    }
    //explode

    //player
    anim[dir].Draw(pos_x, pos_y-15, 0.9, 0.9, 0, al_map_rgba(255, 255, 255, 255));
}
