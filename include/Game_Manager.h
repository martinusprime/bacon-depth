#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <vector>
#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "My_window.h"
#include "Tile.h"
#include "Character.h"

#include "Tile.h"


using namespace sf;



class Game_Manager
{
public:
    Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y);
    void execute_action(Action action);
    void draw();
    void update(int timeElapsed);

    void hud();
    virtual ~Game_Manager() = default;

private:
    bool handle_input_events();
    bool pause;

    Key_event_handler key_event;
    RenderWindow *m_app;
    View m_view1;
    View m_view2;
    Vector2u window_vec;
    //mouse related stuff:
    Vector2f m_selection_vector;
    Vector2i mouse_vec;

    struct Selected_tile
    {
        int x;
        int y;
        int previous_clicked_x;
        int previous_clicked_y;
        int clicked_x;
        int clicked_y;
    };

    int m_x_cursor, m_y_cursor, m_x_offset, m_y_offset;
    int m_w, m_h;
    int m_screen_y; //height of the game window height in pixels
    int m_screen_x; //width of the game window in pixels
    int citizen_number; //the number of citizen you have
    bool clicked;
    Music music;

    Selected_tile selected_tile;
    Tile map[5][10];
    My_Sprite spriteTile0;
    My_Sprite background;
    My_Sprite radio_icon, radio_bar, radio_bar_background, radio_bar_grad, head_icon;
    My_Text citizen_number_text;
    vector <Character> character1;
    vector <My_Sprite> sprites;
    
    
};

#endif // GAME_MANAGER_H
