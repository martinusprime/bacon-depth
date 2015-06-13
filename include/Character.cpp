#include "Character.h"


Character::Character(RenderWindow *app, View *view, int id)
    : sprite(app, "resources/perso", view, 10)
    , life_bar(app, "resources/life_bar.png", view)
    , life_bar_background(app, "resources/life_bar_background.png", view)
    , life_bar_heart(app, "resources/life_bar_heart.png", view)
    , m_id(id)
    , is_alive(true)
{
  
    status = IDLE;

    m_view1 = view;
    m_app = app;
    life = 100;
    tile_x = 0;
    tile_y = 0; 
    tile_size = 384;
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

    //
}


Character::~Character()
{
}


void Character::update()
{
    float new_life =life / 100.0f;
    life_bar.scale(new_life, 1.0f);

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
    if (life <= 0)
    {
        is_alive = false;
    }
}

bool Character::alive()
{
    return is_alive;
}

void Character::draw()
{
    sprite.draw(tile_x * 384 + walking_x, tile_y * 384 + 384 - sprite.get_h());
    life_bar_background.draw(tile_x * 384 + walking_x, tile_y * 384 + ( 384 - sprite.get_h() )- 50);
    life_bar.draw(tile_x * 384 + walking_x, tile_y * 384 + (384 - sprite.get_h()) - 50);
    life_bar_heart.draw(tile_x * 384 + walking_x, tile_y * 384 + (384 - sprite.get_h()) - 50);
}
