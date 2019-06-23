#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "init.hpp"
#include "Tilemap.hpp"
#include "Collision.hpp"
#include "Animation.hpp"
#include "Bomb.hpp"

#define unit 45
#define THICKNESS 42
#define during_explode 0.5

class Explosion{
protected:
    int x,y;
    int posI, posJ;
    bool appear;
    int size;
    //boundaries
    int boundup;
    int bounddown;
    int boundleft;
    int boundright;

    float timer;
    float time_until_end;

    BoundingBox box[2];
    typedef struct brick_info{
        int i;
        int j;
    }BRICK_INFO;
    Animation brick_anim;
    std::list<BRICK_INFO> brick_list;
    std::list<BRICK_INFO>::iterator it;

public:
    Explosion() { };
    ~Explosion() { };
    void Initialize(std::list<Bomb> &bomb_list, Tilemap &map, int size, int i, int j, float time_until_end);
    void FindBounds(Tilemap &map);
    void Update(Tilemap &map);
    void Draw();
    bool get_appear() { return appear; }
    int GetX() { return x; }
    int GetY() { return y; }
	BoundingBox GetBoxY() { return box[0]; }
	BoundingBox GetBoxX() { return box[1]; }

};

#endif
