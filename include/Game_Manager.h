#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>

#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "My_window.h"

using namespace sf;



class Game_Manager
{
public:
    Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y);
    void draw();
    void update();
    virtual ~Game_Manager() = default;

private:


    Key_event_handler key_event;
    RenderWindow *m_app;
    View m_view1;
    View m_view2;
    Vector2u window_vec;
    //mouse related stuff:
    Vector2f m_selection_vector;
    int m_x_cursor, m_y_cursor;



    int m_w, m_h;
    int m_screen_y; //height of the game window height in pixels
    int m_screen_x; //width of the game window in pixels

    

};

#endif // GAME_MANAGER_H
