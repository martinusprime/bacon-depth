#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
<<<<<<< HEAD
    : m_view1(view1)
{
    m_app = app;
    m_app->setView(m_view1);
    
    //init map
    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            map[x][y].setLevel(x);
            if (y == 0)/////////////////////////
            {
                map[x][y].setID(1);
            }
            else
            {
                map[x][y].setID(2);
            }
        }
    }
    for (int i = 0; i <4; i++) {
        sprites.push_back(My_Sprite{ m_app, "resources/tile0.png", &m_view1 });
    }
}

///////////////////////////////////////////////
void Game_Manager::update(int timeElapsed)
{
    for (size_t y = 0; y < 10; y++)
    {
        for (size_t x = 0; x < 5; x++)
        {
            //map[x][y].
        }
    }
}
/////////////////////////////////////////////////

void Game_Manager::draw()
{
    int Id;

=======
: m_view1(view1)
{
 
    m_app = app;
    m_app->setView(m_view1);

   
}



void Game_Manager::update()
{


   
}


void Game_Manager::draw()
{
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
    static sf::Clock render_clock;
    if (render_clock.getElapsedTime().asMilliseconds() < 2) {
        return;
    }
    render_clock.restart();
    m_app->clear();
<<<<<<< HEAD

    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            sprites[map[x][y].getId()].draw(384 * x, 384 * y);
        }
    }
    system("PAUSE");
=======
  

>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
    // Update the window
    m_app->display();
}


