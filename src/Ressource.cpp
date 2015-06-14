#include "Ressource.h"


Ressource::Ressource(RenderWindow *app, View *view, int id, int number_in_tile, int tile_x, int tile_y)
    : sprite(app, "resources/iron_icon_", view, 3)
{
    srand(time(0));
    m_app = app;
    m_view1 = view;
    if (id == 0)
    {
        sprite = My_Sprite{ app, "resources/iron_icon_", view, 3};
    }
    if (number_in_tile > 5)
    {
        number_in_tile = 5;
    }
    m_tile_x = tile_x;
    m_tile_y = tile_y;
    tile_size = 384;
    m_id = id;
    m_number_in_tile = number_in_tile;
    quantity = rand()%25 + 5;
   // cout<< "numebr" << quantity<<endl;
}

Ressource::~Ressource()
{

}

int Ressource::get_quantity()
{
    return quantity;
}

void Ressource::draw()
{
    sprite.draw(m_tile_x * tile_size + sprite.get_w() * m_number_in_tile, m_tile_y * tile_size + tile_size - sprite.get_h());
}
