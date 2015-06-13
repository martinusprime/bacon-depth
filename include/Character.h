#pragma once

#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "Tile.h"
#include "Random.h"

using namespace sf;

class Character
{
public:
    Character(RenderWindow *app, View *view, int id);
    void update();
    void draw();
    bool alive();
    virtual ~Character();

private:
    View *m_view1;
    RenderWindow *m_app;
    enum Direction { UP, DOWN, LEFT, RIGHT };
    enum Status { IDLE, BATTLE, MOVING };
    Direction direction;
    Status status;
    My_Sprite sprite;
    My_Sprite life_bar, life_bar_background, life_bar_heart;
    int m_id, tile_x, tile_y, walking_x, tile_size;
    int life;
    Clock render_clock, random_clock;
    bool is_alive;

};

