#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>
<<<<<<< HEAD
#include <vector>
=======
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4

#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "My_window.h"
<<<<<<< HEAD
#include "Tile.h"

=======
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4

using namespace sf;



class Game_Manager
{
public:
    Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y);
    void draw();
<<<<<<< HEAD
    void update(int timeElapsed);
=======
    void update();
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
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

<<<<<<< HEAD
=======


>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
    int m_w, m_h;
    int m_screen_y; //height of the game window height in pixels
    int m_screen_x; //width of the game window in pixels

<<<<<<< HEAD
    Tile map[5][10];
    vector <My_Sprite> sprites;
=======
    

>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
};

#endif // GAME_MANAGER_H
