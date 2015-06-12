#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
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
    static sf::Clock render_clock;
    if (render_clock.getElapsedTime().asMilliseconds() < 2) {
        return;
    }
    render_clock.restart();
    m_app->clear();
  

    // Update the window
    m_app->display();
}


