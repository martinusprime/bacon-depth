#include "..\include\Resource.h"
#include <random>


Resource::Resource(RenderWindow *app, View *view, int id, int number_in_tile)
    : sprite(app, "resources/food", view, 2)
{
    srand(time(0));
    m_app = app;
    m_view1 = view;
    if (id == 0)
    {
       
    }
    if (number_in_tile > 5)
    {
        number_in_tile = 5;
    }
    tile_x = 0;
    tile_y = 0;
    tile_size = 384;
    m_id = id;
    m_number_in_tile = number_in_tile;
    quantity = rand()%25 + 5;
    cout<< "numebr" << quantity<<endl;
}

Resource::~Resource()
{

}

int Resource::get_quantity()
{
    return quantity;
}

void Resource::draw()
{
    sprite.draw(tile_x * tile_size + sprite.get_w() * m_number_in_tile, tile_y * tile_size + tile_size - sprite.get_h());
}
