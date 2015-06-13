#pragma once
#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"

class Resource
{
public:
    Resource(RenderWindow *app, View *view, int id, int number_in_tile);
    void draw();
    int get_quantity();
    virtual ~Resource();
private:
    View *m_view1;
    RenderWindow *m_app;

    int m_id, m_number_in_tile, tile_x, tile_y, tile_size, quantity;

    My_Sprite sprite;
};

