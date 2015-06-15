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
#include "Character.h"
#include "Glissor.h"
#include "Monster.h"
#include "Tile.h"


using namespace sf;



class Game_Manager
{
public:
    Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y);
    void execute_action(Action action);
    void draw();
    void update(float timeElapsed);
    bool Game_Manager::isOccupied(int x, int y);
    void hud();
    virtual ~Game_Manager() = default;
    void combat(float time);

private:
    bool handle_input_events();
    bool handle_input_events_key();
    bool pause;
    void reset();
    void cinematic_update();
    void cinematic_draw();
    void cinematic_init();

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
    int metal_number, food_number;
    bool clicked, glissor_on, cinematic_on;
    float oxygen_number;
    Music music;

    Selected_tile selected_tile;
    Tile my_map[10][5];
    Tile mapCon[5][10];
    My_Sprite spriteTile0;
    My_Sprite background;
    My_Sprite food_icon;
    My_Sprite metal_icon;
    My_Sprite selection_border, goal_border, radio_icon, radio_bar, radio_bar_background, radio_bar_grad, oxygen_bar, oxygen_bar_background, oxygen_bar_grad, head_icon;
    My_Text citizen_number_text, food_number_text, metal_number_text;
    vector <Glissor> glissor1;
    vector <Character> character1;
    vector <Monster> monster1;
    vector <My_Sprite> sprites;
    vector <Button> buttons;
    vector <bool> citizen_state;
    vector <bool> monster_state;
    enum Zoom_change { ZOOM_NO_CHANGE, ZOOM_ADD, ZOOM_LESS };
    Clock cinematic_clock, radiation_time, oxygen_clock;
    float cinematic_time;

    Zoom_change zoom_change;
    float zoom;
    float zoom_rate;


    Clock clock_zoom, monster_time;
    sf::Time zoom_time;

    int bomb_y;
    My_Sprite bomb;
    My_Sprite end_sprite;
    My_Sprite explosion;
    My_Sprite info_sprite, pause_sprite;
    bool explosing, info, explosion_flash;

    bool fail;

    sf::SoundBuffer buffer;
    sf::Sound sound;

    sf::SoundBuffer buffer_combat;
    sf::Sound sound_combat;

};

#endif // GAME_MANAGER_H
