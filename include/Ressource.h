#pragma once
#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"

using namespace sf;
class Ressource
{
public:
    Ressource(RenderWindow *app, View *view, int id, int number_in_tile, int tile_x, int tile_y);
    void draw();
    int get_quantity();
    virtual ~Ressource();
private:
    View *m_view1;
    RenderWindow *m_app;
    int m_id, m_number_in_tile, m_tile_x, m_tile_y, tile_size, quantity;
    My_Sprite sprite;
};

