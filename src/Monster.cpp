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
    //set initial position
    walking_x = m_id * 10 ;

    if (walking_x < 0)
    {
        direction = RIGHT;
        walking_x = 0;
    }

    if (walking_x + sprite.get_w() > 384)
    {
        direction = LEFT;
        walking_x = 384 - sprite.get_w();
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

            if (walking_x + sprite.get_w() > 384)
            {
                direction = LEFT;
                walking_x = 384 - sprite.get_w();
            }

        }
    }

}


void Monster::draw()
{
    sprite.draw(tile_x * 384 + walking_x, tile_y * 384 + 384 - sprite.get_h());
}