#include "player.hpp"

#include <math.h>
#include <iostream>

player::player(){
}
player::~player(){

}
void player::initial(int x,int y){
    this->x = x;
    this->y = y;
    this->dead = false;

    this->dir = DOWN;
    this->anim[UP].Initialize(game_player_up, 4, 0.1, true);
    this->anim[DOWN].Initialize(game_player_down, 4, 0.1, true);
    this->anim[LEFT].Initialize(game_player_left, 4, 0.1, true);
    this->anim[RIGHT].Initialize(game_player_right, 4, 0.1, true);

    this->box[UP].Initialize(-13, -18, 29, 30);
    this->box[DOWN].Initialize(-13, -18, 29, 32);
    this->box[LEFT].Initialize(-17, -15, 25, 25);
    this->box[RIGHT].Initialize(-9, -15, 28, 25);

    this->speed = start_speed;
    this->bomb_num = max_bomb_num;
    this->walkout = false;
}

void player::die(){
    this->dead = true;
}

void player::put_bomb(Tilemap &map){
    if(bomb_list.size() < (unsigned)bomb_num && map.GetBombPos(posI, posJ) == 0){
        al_play_sample(SFX_put_bomb, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        Bomb add;
        add.initial(((x-MAP_X0)/TILESIZE)*TILESIZE + MAP_X0 + TILESIZE/2, ((y-MAP_Y0)/TILESIZE)*TILESIZE + TILESIZE/2 + MAP_Y0, 2.5, map);
        bomb_list.push_back(add);
    }
    bomb_timer = al_get_time();
    walkout = false;
}

//PATH BLOCKED SERIES
bool player::Blocked(Tilemap &map,int i, int j){
    if(map.GetTileID(i, j) != GRASS) return true;
    return false;
}
bool player::vertical_block(Tilemap &map,int dir){
    if(dir == UP || dir == DOWN){
        int tmp_j1 = (x + 15  - MAP_X0) / TILESIZE; //right
        int tmp_j2 = (x - 15  - MAP_X0) / TILESIZE; //left
        if((tmp_j1 == posJ + 1) && map.GetTileID(posI, posJ+1) != GRASS){
            return true;
        }
        else if((tmp_j2 == posJ - 1) && map.GetTileID(posI, posJ-1) != GRASS){
            return true;
        }
    }
    return false;
}
bool player::horizon_block(Tilemap &map){
    int tmp_i =(y + 15 - MAP_Y0) / TILESIZE;
    if((tmp_i == posI + 1)&& map.GetTileID(posI + 1, posJ) != GRASS ){
        return true;
    }
    return false;
}
bool player::Bomb_Block(Tilemap &map, int i,int j){
    if(al_get_time() - bomb_timer >= leave_timer){
        if(map.GetBombPos(i, j) == 1)
            return true;
        else return false;
    }
    return false;
}

void player::walk(Tilemap &map){
    int tmp_j2;
    int tmp_j1;
    int pre_x = x;
    int pre_y = y;


    //std::cout<<pos_x<<" "<<pos_y <<'\n';
    if(key_state[ALLEGRO_KEY_UP]){
        y -= speed;
        dir = UP;
        posI = (y - MAP_Y0) / TILESIZE;
        posJ = (x - MAP_X0) / TILESIZE;
        if(Blocked(map, posI, posJ)
           ||Bomb_Block(map, posI, posJ)
           ||vertical_block(map,dir)
           //||Blocked(map, posI-1, tmp_j1)
            //||Blocked(map, posI-1, tmp_j2)
                                            ){
            y = pre_y;
            x = pre_x;
        }
    }
    else if(key_state[ALLEGRO_KEY_DOWN]){
        y += speed;
        dir = DOWN;
        posI = (y - MAP_Y0 ) / TILESIZE;
        posJ = (x - MAP_X0) / TILESIZE;
        if(Blocked(map, posI, posJ)
           ||Bomb_Block(map, posI, posJ)
           ||vertical_block(map,dir)
           ||horizon_block(map)
           //||Blocked(map, posI+1, tmp_j1)
            //||Blocked(map, posI+1, tmp_j2)
                                        ){
            y = pre_y;
            x = pre_x;
        }
    }
    else if(key_state[ALLEGRO_KEY_LEFT]){
        this->w = al_get_bitmap_width(game_player_left);
        x -= speed;
        dir = LEFT;
        tmp_j1 = (x - 0.118*w - MAP_X0) / TILESIZE;
        posI = (y - MAP_Y0) / TILESIZE;
        posJ = (x - MAP_X0) / TILESIZE;
        if(Blocked(map, posI, posJ)
           ||Bomb_Block(map, posI, posJ)
           ||Blocked(map, posI, tmp_j1)
           ||horizon_block(map)){
            y = pre_y;
            x = pre_x;
        }
    }
    else if(key_state[ALLEGRO_KEY_RIGHT]){
        this->w = al_get_bitmap_width(game_player_left);
        x += speed;
        dir = RIGHT;
        tmp_j2 = (x + 0.12*w - MAP_X0) / TILESIZE;
        posI = (y - MAP_Y0) / TILESIZE;
        posJ = (x - MAP_X0) / TILESIZE;
        if(Blocked(map, posI, posJ)
           ||Bomb_Block(map, posI, posJ)
           ||Blocked(map, posI, tmp_j2)
           ||horizon_block(map)){
            y = pre_y;
            x = pre_x;
        }
    }
    else{
        anim[dir].Reset();
    }

}
void player::update(Tilemap &map){
    posI = (y - MAP_Y0) / TILESIZE;
    posJ = (x - MAP_X0) / TILESIZE;

    walk(map);
    anim[dir].Update();

    //bomb
    /*if(!walkout && (map.GetBombPos(posI, posJ) == 0)){
        walkout = true;
    }*/

    it = bomb_list.begin();
    while(it != bomb_list.end()){
        (*it).update(map);

        if((*it).get_appear()==false){
            //set explosion
            Explosion create;
            create.Initialize(bomb_list, map, 1, (*it).get_tile_i(), (*it).get_tile_j(), during_explode);
            explosion_list.push_back(create);

            it = bomb_list.erase(it);
        }
        else{
            it++;
        }
    }

    //explode effect
    ex_it = explosion_list.begin();
    while(ex_it != explosion_list.end()){
        ex_it->Update(map);
        if(ex_it->inexplosion(posI, posJ))
            die();

        if(ex_it->get_appear()==false){
            ex_it = explosion_list.erase(ex_it);
        }
        else{
            ex_it++;
        }

    }
}

void player::draw(){
    //bomb
    if(bomb_list.size()!=0)
    for(it = bomb_list.begin(); it != bomb_list.end(); it++){
        (*it).draw();
    }
    //explode
    for(ex_it = explosion_list.begin(); ex_it != explosion_list.end(); ex_it++){
        (*ex_it).Draw();
    }
    //player
    anim[dir].Draw(x, y-15, 0.9, 0.9, 0, al_map_rgba(255, 255, 255, 255));

    //debug
    if(debug_mode){

		box[dir].Draw();
		al_draw_filled_circle(x, y, 3, al_map_rgba(255,0,0,255));

        //posJ = cur_tile_j;
        //posI = cur_tile_i;

        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ-1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ-1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI-1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI-1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);
        al_draw_rectangle((posJ+1)*TILESIZE + MAP_X0, (posI+1)*TILESIZE + MAP_Y0, (posJ+1)*TILESIZE + MAP_X0 + TILESIZE, (posI+1)*TILESIZE + MAP_Y0 + TILESIZE, al_map_rgba(0,0,255,255), 1);

        al_draw_textf(font_debug, al_map_rgb(0, 0, 0), x, y+15, ALLEGRO_ALIGN_CENTER, "Pos I: %d, Pos J: %d", posI, posJ);
        al_draw_textf(font_debug, al_map_rgb(0, 0, 0), x, y+25, ALLEGRO_ALIGN_CENTER, "x: %d, y: %d", x, y);

    }
}
