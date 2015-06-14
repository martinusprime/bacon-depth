#include "Monster.h"

Monster::Monster(RenderWindow *app, View *view, int id)
    : sprite(app, "resources/monster", view, 10)
    , m_id(id)
{
  
    status = IDLE;

    m_view1 = view;
    m_app = app;
    life = 100;
    tile_x = 1;
    tile_y = 0;
    tile_size = 384;
    //set initial position
    walking_x = m_id * 10 ;

    if (walking_x < 0)
    {
        direction = RIGHT;
        walking_x = 0;
    }

    if (walking_x + sprite.get_w() > tile_size)
    {
        direction = LEFT;
        walking_x = tile_size - sprite.get_w();
    }

    if (Random::get_int(0, 10) > 5)
    { 
        direction = RIGHT;
    }
    else direction = LEFT;
}


Monster::~Monster()
{
}


void Monster::update()
{

    if (status == IDLE)
    {
        if (random_clock.getElapsedTime().asSeconds() > 5)
        {
            random_clock.restart();


            int random = Random::get_int(0, 10);
            cout << random << endl;
            if (random > 7)
            {
                if (direction == RIGHT)
                {
                    direction = LEFT;
                }
                else if (direction == LEFT)
                {
                    direction = RIGHT;
                }
            }
        }


        if (render_clock.getElapsedTime().asSeconds() > 0.1)
        {
            render_clock.restart();


            if (direction == RIGHT)
            {
                walking_x += 2;
            }
            else if (direction == LEFT)
            {
                walking_x -= 2;
            }

            if (walking_x < 0)
            {
                direction = RIGHT;
                walking_x = 0;
            }

            if (walking_x + sprite.get_w() > tile_size)
            {
                direction = LEFT;
                walking_x = tile_size - sprite.get_w();
            }

        }
    }

}


void Monster::draw()
{
    sprite.draw(tile_x * tile_size + walking_x, tile_y * tile_size + tile_size - sprite.get_h());
}