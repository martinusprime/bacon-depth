#pragma once

#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "My_window.h"
#include "Tile.h"
#include "Random.h"

using namespace sf;

class Monster
{
public:
    Monster(RenderWindow *app, View *view, int id);
    void update();
    void draw();
    virtual ~Monster();

private:
    View *m_view1;
    RenderWindow *m_app;
    enum Direction { UP, DOWN, LEFT, RIGHT };
    enum Status { IDLE, BATTLE, MOVING };
    Direction direction;
    Status status;
    My_Sprite sprite;
    int m_id, tile_x, tile_y, walking_x;
    int life;
    Clock render_clock, random_clock;

};

