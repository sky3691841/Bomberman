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
}
bool player::PathBlocked(Tilemap &map,int i, int j) {
	if(map.GetTileID(i, j) != GRASS || map.GetBombPos(i, j) == 1){
        return box[dir].CollisionWithTiles( j*TILESIZE + MAP_X0, i*TILESIZE + MAP_Y0, TILESIZE, TILESIZE);
	}
	return false;
}
bool player::Blocked(Tilemap &map,int i, int j){
    if(map.GetTileID(i, j) != GRASS) return true;
    return false;
}
void player::put_bomb(Tilemap &map){
    if(bomb_list.size() < (unsigned)bomb_num && map.GetBombPos(posI, posJ) == 0){
        al_play_sample(SFX_put_bomb, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        Bomb add;
        add.initial(((x-MAP_X0)/TILESIZE)*TILESIZE + MAP_X0 + TILESIZE/2, ((y-MAP_Y0)/TILESIZE)*TILESIZE + TILESIZE/2 + MAP_Y0, 2.5, map);
        bomb_list.push_back(add);
    }
}

void player::walk(Tilemap &map){
    int tmp_j2;
    int tmp_j1;
    int pre_x = x;
    int pre_y = y;


    //std::cout<<pos_x<<" "<<pos_y <<'\n';
    if(key_state[ALLEGRO_KEY_UP]){
        //this->w = al_get_bitmap_width(game_player_up);
        y -= speed;
        dir = UP;
        //tmp_j1 = (x - 0.1*w - MAP_X0) / TILESIZE;//left
        //tmp_j2 = (x + 0.1*w - MAP_X0) / TILESIZE;//right
        posI = (y - MAP_Y0) / TILESIZE;
        posJ = (x - MAP_X0) / TILESIZE;
        if(Blocked(map, posI, posJ)//||Blocked(map, posI-1, tmp_j1)
            //||Blocked(map, posI-1, tmp_j2)
       //|| PathBlocked(map, posI-1, posJ-1)

       /*|| PathBlocked(map, posI-1, posJ+1)  */){
            y = pre_y;
            x = pre_x;
        }
    }
    else if(key_state[ALLEGRO_KEY_DOWN]){
        //this->w = al_get_bitmap_width(game_player_up);
        y += speed;
        dir = DOWN;
        //tmp_j1 = (x - 0.1*w - MAP_X0) / TILESIZE;
        //tmp_j2 = (x + 0.1*w - MAP_X0) / TILESIZE;
        posI = (y - MAP_Y0 +15) / TILESIZE;
        posJ = (x - MAP_X0) / TILESIZE;
        if(Blocked(map, posI, posJ)//||Blocked(map, posI+1, tmp_j1)
            //||Blocked(map, posI+1, tmp_j2)
       //|| PathBlocked(map, posI+1, posJ-1)

       /*|| PathBlocked(map, posI+1, posJ+1) */ ){
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
        if(Blocked(map, posI, posJ)||Blocked(map, posI, tmp_j1)

       //|| PathBlocked(map, posI-1, posJ-1)

      /* || PathBlocked(map, posI+1, posJ-1) */ ){
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
        if(Blocked(map, posI, posJ)||Blocked(map, posI, tmp_j2)

       //|| PathBlocked(map, posI-1, posJ+1)

       /*|| PathBlocked(map, posI+1, posJ+1) */ ){
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
    for(it = bomb_list.begin(); it != bomb_list.end(); it++){
        (*it).update(map);

        if((*it).get_appear()==false){
            //set explosion
            it = bomb_list.erase(it);
        }
    }

    //explode effect
}

void player::draw(){
    //bomb
    for(it = bomb_list.begin(); it != bomb_list.end(); it++){
        (*it).draw();
    }
    //explode

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
