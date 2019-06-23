#include "Explosion.hpp"

void Explosion::Initialize(std::list<Bomb> &bomb_list, Tilemap &map, int size, int i, int j, float time_until_end){
    this->posI = i;
    this->posJ = j;
    this->x = MAP_X0 + TILESIZE*j + TILESIZE/2;
    this->y = MAP_Y0 + TILESIZE*i + TILESIZE/2;
    this->appear = true;
    this->time_until_end = time_until_end;
    this->timer = al_get_time();
    this->size = size;

    FindBounds(map);

    //up+down
    this->box[0].Initialize2(x - THICKNESS/2, y - boundup - THICKNESS/2, THICKNESS, boundup + bounddown + THICKNESS);
    //l+r
    this->box[1].Initialize2(x - boundleft - THICKNESS/2, y - THICKNESS/2, boundleft + boundright + THICKNESS, THICKNESS);

    brick_anim.Initialize(game_brick_explosion, 6, ALLEGRO_MSECS_TO_SECS(80), false);
    for(std::list<Bomb>::iterator its = bomb_list.begin(); its != bomb_list.end(); its++ ){
        if( (*its).GetBox().CheckCollision( box[0] )|| (*its).GetBox().CheckCollision( box[1] ) )
          (*its).exploded(map);
    }

    al_play_sample(SFX_explosion, volSFX, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void Explosion::FindBounds(Tilemap &map){
    int maxbound = 0;
    //square
    boundup = size;
    bounddown = size;
    boundleft = size;
    boundright = size;

    for(int i = posI-1, j = posJ; maxbound < size; i--){
        if(map.GetTileID(i, j) == GRASS){
            maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK){
            maxbound++;
            BRICK_INFO add;
            add.i = i;
            add.j = j;
            brick_list.push_back(add);
        }
        else
            break;
    }
    boundup = maxbound*unit;
    //
    maxbound = 0;
    for(int i = posI+1, j = posJ; maxbound < size; i++){
        if(map.GetTileID(i, j) == GRASS){
            maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK){
            maxbound++;
            BRICK_INFO add;
            add.i = i;
            add.j = j;
            brick_list.push_back(add);
        }
        else
            break;
    }
    bounddown = maxbound*unit;
    //
    maxbound = 0;
    for(int i = posI, j = posJ-1; maxbound < size; j--){
        if(map.GetTileID(i, j) == GRASS){
            maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK){
            maxbound++;
            BRICK_INFO add;
            add.i = i;
            add.j = j;
            brick_list.push_back(add);
        }
        else
            break;
    }
    boundleft = maxbound*unit;
    //
    maxbound = 0;
    for(int i = posI, j = posJ+1; maxbound < size; j++){
        if(map.GetTileID(i, j) == GRASS){
            maxbound++;
        }
        else if(map.GetTileID(i, j) == BRICK){
            maxbound++;
            BRICK_INFO add;
            add.i = i;
            add.j = j;
            brick_list.push_back(add);
        }
        else
            break;
    }
    boundright = maxbound*unit;
}
bool Explosion::inexplosion(int playerI, int playerJ){
    if((playerI >= posI-1 && playerI <= posI+1 && playerJ == posJ)
        ||(playerJ >= posJ-1 && playerJ <= posJ+1 && playerI == posI))
            return true;
    return false;
}
void Explosion::Update(Tilemap &map){
    if(al_get_time() - timer >= time_until_end) {
        appear = false;
    }
    brick_anim.Update();

    if(brick_anim.Finish()){
        while(!brick_list.empty()){
            it = brick_list.begin();
            map.SetTileID((*it).i, (*it).j, GRASS);
            brick_list.pop_front();
        }
    }
}

void Explosion::Draw(){
    //yellow
    al_draw_filled_rounded_rectangle(x - boundleft - THICKNESS/2, y - THICKNESS/2, x + boundright + THICKNESS/2, y + THICKNESS/2, 15, 15, al_map_rgb(255, 127, 39));
    al_draw_filled_rounded_rectangle(x - THICKNESS/2, y - boundup - THICKNESS/2, x + THICKNESS/2, y + bounddown + THICKNESS/2, 10, 10, al_map_rgb(255, 127, 39));
    //red
    al_draw_filled_rounded_rectangle(x - boundleft - THICKNESS/2 +8, y - THICKNESS/2 +8, x + boundright + THICKNESS/2 -8, y + THICKNESS/2 -8, 15, 15, al_map_rgb(238, 228, 176));
    al_draw_filled_rounded_rectangle(x - THICKNESS/2 +8, y - boundup - THICKNESS/2 +8, x + THICKNESS/2 -8, y + bounddown + THICKNESS/2 -8, 10, 10, al_map_rgb(238, 228, 176));

    for(it = brick_list.begin(); it != brick_list.end(); it++){
        brick_anim.Draw((*it).j * TILESIZE + TILESIZE/2 + MAP_X0, (*it).i * TILESIZE + TILESIZE/2 + MAP_Y0, 1.0, 1.0, 0.0, al_map_rgb(255,255,255));
    }


    if(debug_mode){

       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 20, ALLEGRO_ALIGN_RIGHT, "BOUNDUP: %d", boundup);

       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 30, ALLEGRO_ALIGN_RIGHT, "BOUNDDOWN: %d", bounddown);

       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 40, ALLEGRO_ALIGN_RIGHT, "BOUNDLEFT: %d", boundleft);

       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 50, ALLEGRO_ALIGN_RIGHT, "BOUNDRIGHT: %d", boundright);

       al_draw_textf(font_debug, al_map_rgba(255, 255, 255, 255), SCREEN_W - 150, 60, ALLEGRO_ALIGN_RIGHT, "SIZE: %d", size);

       al_draw_filled_circle(x, y, 2, al_map_rgb(255, 0, 0));

       box[0].Draw();

       box[1].Draw();

       }

}
