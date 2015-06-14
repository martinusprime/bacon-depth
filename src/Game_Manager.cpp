#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
    : m_view1(view1)
    , radio_icon(app, "resources/radioactive_icon.png", &view1)
    , food_icon(app, "resources/food_icon.png", &view1)
    , metal_icon(app, "resources/metal_icon.png", &view1)
    , radio_bar(app, "resources/radio_bar.png", &view1)
    , radio_bar_background(app, "resources/radio_bar_background.png", &view1)
    , radio_bar_grad(app, "resources/radio_bar_grad.png", &view1)
    , head_icon(app, "resources/head_icon.png", &view1)
    , explosion(app, "resources/explosion.png", &view1)
    , background(app, "resources/background.png", &view1)
    , selection_border(app, "resources/selection_border.png", &view1)
    , bomb(app, "resources/bomb.png", &view1)
    , goal_border(app, "resources/selection_border.png", &view1)
    , resource1(app, &view1, 0, 5)
    , tile_size(384)
    , glissor1(app, 0, 0, 0, 0, &view1)
{


    goal_border.add_color(255, 150, 50, 255);

    citizen_max = 10;
    monster_max = 10;
    citizen_number = citizen_max;
    pause = false;
    clicked = false;
    glissor_on = false;
    cinematic_on = true;
    m_x_offset = 384 * 2 + (384/2);
    m_y_offset =  (384 / 2);

    m_app = app;
    m_app->setView(m_view1);
    
    m_screen_y = 1080;
    m_screen_x = 1920;

    m_view2.reset(FloatRect(0.0f, 0.0f, static_cast<float>(m_screen_x), static_cast<float>(m_screen_y)));
    m_view2.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    //init map
    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            map[x][y].setLevel(x);
                map[x][y].setID(x + (y * 5));
        
        }
    }
    
    //init sprites
    string path = "";
    for (int i = 0; i < 60 ; i++) {
        path = "resources/tile" + std::to_string(i) + ".png";
        sprites.push_back( My_Sprite{ m_app, path, &m_view1 });
  //      std::cout << path << endl;

    }

    //character in first case
    for (int i = 0; i < citizen_max; i++)
    {
        character1.push_back( Character{ m_app, &m_view1, i });
        citizen_state.push_back(true);
    }
    citizen_number_text.init(app, "Still alive: ", 35, 1);
    metal_number_text.init(app, "Metal: ", 35, 1);
    food_number_text.init(app, "Foods: ", 35, 1);

  

    //monsters on surface
    for (int i = 0; i < monster_max; i++)
    {
        monster1.push_back( Monster{ m_app, &m_view1, i });
    }
    citizen_number_text.init(app, "Still alive: ", 35, 1);

    //all the buttons
  
    buttons.push_back( Button{ m_app, "creuser", 0, 0, 0, 0, &m_view1 });
    glissor1 = Glissor{ m_app, 0, 0, 0, 0, &m_view1 };
    //music init

    if (!music.openFromFile("resources/music.ogg"))
    {
        cout << "music init failed" << endl;
    }

    music.play();
    //
    update(0);
    cinematic_init();
}


void Game_Manager::update(int timeElapsed)
{
    handle_input_events();

    if (cinematic_on)
    {
        cinematic_update();
    }

    if (!pause)
    {
        m_view1.setCenter(static_cast<float>(m_x_offset), static_cast<float>(m_y_offset));
        m_app->setView(m_view1);


        buttons[0].update(selected_tile.clicked_x* tile_size, selected_tile.clicked_y * tile_size);
        if (buttons[0].is_activated())
        {
            buttons[0].desactivate();
        }
        
        for (int i = 0; i < citizen_max; i++) {
            if (citizen_state[i])
            { 
                character1[i].update(map);
                    if (!character1[i].alive())
                    {
                        citizen_number--;
                        citizen_state[i] = false;
                    }
            }
        }

        for (int i = 0; i < monster_max; i++) {
            if (citizen_state[i])
            {
                monster1[i].update();
            
            }
        }
        //if the mouse is over the right tile

       // cout << "selec " << selected_tile.x << " " << selected_tile.y << endl;
        selected_tile.x = m_selection_vector.x / tile_size;
        selected_tile.y = m_selection_vector.y / tile_size;
        if (selected_tile.x < 0)
        {
            selected_tile.x = 0;
        }
        if (selected_tile.x > 4)
        {
            selected_tile.x = 4;
        }
        if (selected_tile.y < 0)
        {
            selected_tile.y = 0;
        }
     
        if (clicked)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (selected_tile.goal_x != selected_tile.x
                    || selected_tile.goal_y != selected_tile.y)
                {
                    selected_tile.previous_clicked_x = selected_tile.clicked_x;
                    selected_tile.previous_clicked_y = selected_tile.clicked_y;

                    selected_tile.clicked_x = selected_tile.x;
                    selected_tile.clicked_y = selected_tile.y;
                }
           

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                
                if(selected_tile.x != selected_tile.clicked_x
                    || selected_tile.y != selected_tile.clicked_y)
                {
                    selected_tile.goal_x = selected_tile.x;
                    selected_tile.goal_y = selected_tile.y;
                    glissor_on = true;
                }
            }
        }
      
        citizen_number_text.refill("Still alive: " + std::to_string(citizen_number));
    }
    
    
    for (size_t i = 0; i < character1.size(); i++)
    {
        character1[i].update(map);
    }
}

void Game_Manager::cinematic_update()
{
    if (cinematic_clock.getElapsedTime().asSeconds() > 0.5)
    {
        cinematic_time+= 0.3;
        bomb_y+= cinematic_time;
        if (explosing)
        {
            explosion.scale(1.0f + cinematic_time, 1.0f + cinematic_time);
        }

        if (explosion_flash == true)
        {
            explosion_flash = false;
        }
        else 
        {
            explosion_flash = true;
        }
    }
    if (bomb_y >= 384 - bomb.get_h() && !explosing)
    {
        cinematic_time = 1.0f;
        explosing = true;
    }
    if (explosing && cinematic_time >= 6.5f)
    {
        pause = false;
        cinematic_on = false;
    }
   
}
void Game_Manager::cinematic_draw()
{
   
    if (explosing)
    {
        if (!explosion_flash)
        {
            explosion.draw(0, -384);
        }
    }
    else
    {
            bomb.draw(0, bomb_y - 364);
            bomb.draw(354, bomb_y);
            bomb.draw(645, bomb_y);
            bomb.draw(888, bomb_y);
    }
}

void Game_Manager::cinematic_init()
{
    explosing = false;
    pause = true;
    explosion_flash = true;
    bomb_y = -384;
    cinematic_time = 5.0f;
    cinematic_clock.restart();
}

void Game_Manager::draw()
{
    int Id;

    static sf::Clock render_clock;
  
    render_clock.restart();
    m_app->clear();

    background.draw(0,0  - tile_size );
   
    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            sprites[map[x][y].getId()].draw(tile_size * x, tile_size * y);
        }
    }
    //ressources display
    resource1.draw();

    for (int i = 0; i < citizen_max; i++)
    {
        if (citizen_state[i])
        {
            character1[i].draw();
        }

    }
    
    for (int i = 0; i < monster_max; i++)
    {
       
        monster1[i].draw();

    }
    goal_border.draw(selected_tile.goal_x* tile_size, selected_tile.goal_y * tile_size);
    selection_border.draw(selected_tile.clicked_x * tile_size, selected_tile.clicked_y * tile_size);
    buttons[0].draw();

    if (cinematic_on)
    {
        cinematic_draw();
    }

    
    if (glissor_on)
    {
        glissor1.update(selected_tile.goal_x* tile_size, selected_tile.goal_y * tile_size);
        glissor1.draw();
    }
    //pause handling

    if (!pause)
    {
        hud();
    }
    // Update the window
    m_app->display();


}
void Game_Manager::hud()
{
    m_app->setView(m_view2);
 
    radio_icon.draw(0, 0);

    radio_bar_background.draw(0, radio_icon.get_h());
    radio_bar.draw(0, radio_icon.get_h());
    radio_bar_grad.draw(0, radio_icon.get_h());

    head_icon.draw(1920 - head_icon.get_w(), 0);
    food_icon.draw(1920 - food_icon.get_w(), 200);
    metal_icon.draw(1920 - metal_icon.get_w(), 400);



    citizen_number_text.draw(1920 - (head_icon.get_w() * 2.5), 0, 35);
    metal_number_text.draw(1920 - (head_icon.get_w() * 2.5), 400, 35);
    food_number_text.draw(1920 - (head_icon.get_w() * 2.5), 200, 35);

    m_app->setView(m_view1);
}

void Game_Manager::execute_action(Action action)
{
    switch (action)
    {
    case ACT_GO_UP:
          m_y_offset -= 384;
        break;
    case ACT_GO_RIGHT:
        m_x_offset += 384;

        break;
    case ACT_GO_DOWN:
        m_y_offset += 384;
        break;
    case ACT_GO_LEFT:
        m_x_offset -= 384;
        break;  
    case ACT_PAUSE:
        if (!pause)
        {
            pause = true;
        }
        else
        {
            pause = false;
        }
            break;
    case ACT_CLOSE_APP:
        cout << "close app\n";
        m_app->close();
        break;
    case ACT_VALIDATION:
        ///////DEBUG
        character1[1].newGoal(0, 2);
    default:
        break;
    }
}

bool Game_Manager::handle_input_events()
{
    Event event;
    bool isEvent = m_app->pollEvent(event);
    Action action;
    sf::Mouse::Button click = {};
    clicked = false;

    key_event.get_mouse_position(m_app, mouse_vec);
    m_selection_vector = m_app->mapPixelToCoords(mouse_vec);

    bool ret = false;
    if (isEvent)
    {
        if (key_event.manage_key_event(event, action))
        {
            execute_action(action);
            ret = true;
        }
        if (key_event.manage_mouse_click(event, click)) {
            clicked = true;
            ret = true;
        }
    }
    return ret;
}
