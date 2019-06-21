#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Tilemap.hpp"
#include "init.hpp"

//to be revised
#define start_pos_x 75
#define start_pos_y 150

class player{
protected:
    int pos_x, pos_y;
    int speed;

public:

    player();
    ~player();
    void initial(int ,int);
    void walk(Tilemap &map);
    void draw();
    bool haveobstacles(Tilemap map, int x, int y);

};


#endif
