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
#include "Tile.h"
#include "Character.h"
#include "Glissor.h"
#include "Monster.h"
#include "Resource.h"
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
        int goal_x;
        int goal_y;
    };

    int m_x_cursor, m_y_cursor, m_x_offset, m_y_offset;
    int m_w, m_h;
    int m_screen_y; //height of the game window height in pixels
    int m_screen_x; //width of the game window in pixels
    int citizen_number, citizen_max, monster_max; //the number of citizen you have
    int tile_size;
    bool clicked, glissor_on;
    Music music;

    Resource resource1;
    Selected_tile selected_tile;
    Tile map[5][10];
    My_Sprite spriteTile0;
    My_Sprite background;
    My_Sprite food_icon;
    My_Sprite metal_icon;
    My_Sprite selection_border, goal_border, radio_icon, radio_bar, radio_bar_background, radio_bar_grad, head_icon;
    My_Text citizen_number_text, food_number_text, metal_number_text;
    Glissor glissor1;
    vector <Character> character1;
    vector <Monster> monster1;
    vector <My_Sprite> sprites;
    vector <Button> buttons;
    vector <bool> citizen_state;
    
};

#endif // GAME_MANAGER_H
