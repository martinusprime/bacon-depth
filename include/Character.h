#pragma once

#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "My_window.h"
#include "Tile.h"

using namespace sf;

class Character
{
public:
    Character(RenderWindow *app, View *view);
    void update();
    void draw();
    virtual ~Character();

private:
    View *m_view1;
    RenderWindow *m_app;

    My_Sprite sprite;
    int tile_x, tile_y;
    int life;

};

