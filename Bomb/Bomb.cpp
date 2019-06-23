#include "Bomb.hpp"

void Bomb::initial(int x, int y, float countdown, Tilemap &map){
    this->pos_x = x;
    this->pos_y = y;
    this->tile_i = (pos_y - MAP_Y0) / TILESIZE;
    this->tile_j = (pos_x - MAP_X0) / TILESIZE;

    this->anim.Initialize(game_bomb, 4, ALLEGRO_MSECS_TO_SECS(150), true);

    this->appear = true;
    this->time_until_exploded = countdown;
    this->timer = al_get_time();

    map.SetBombPos(tile_i,tile_j,1);
}
void Bomb::update(Tilemap &map){
    map.SetBombPos(tile_i, tile_j, 0);
    tile_i = (pos_y - MAP_Y0) / TILESIZE;
    tile_j = (pos_x - MAP_X0) / TILESIZE;
    map.SetBombPos(tile_i, tile_j, 1);

    anim.Update();
    if(al_get_time() - timer >= time_until_exploded)
        exploded(map);
}

bool Bomb::CheckObstaclesOnTile(Tilemap &map, int i, int j){
    return map.IsPathBlocked(i, j);
}

void Bomb::draw(){
    anim.Draw(pos_x, pos_y, 1.0, 1.0, 0, al_map_rgba(255, 255, 255, 255));

    if(debug_mode){



            al_draw_textf(font_debug, al_map_rgb(0, 0, 0), pos_x, pos_y+25, ALLEGRO_ALIGN_CENTER, "POS I: %d, POS J: %d", tile_i, tile_j);

            al_draw_textf(font_debug, al_map_rgb(0, 0, 0), pos_x, pos_y+35, ALLEGRO_ALIGN_CENTER, "x: %d, y: %d", pos_x, pos_y);



        }
}

void Bomb::exploded(Tilemap &map){
    appear = false;
    map.SetBombPos(tile_i,tile_j,0);
}
