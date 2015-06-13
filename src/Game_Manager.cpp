#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
    : m_view1(view1)
    , radio_icon(app, "resources/radioactive_icon.png", &view1)
    , radio_bar(app, "resources/radio_bar.png", &view1)
    , radio_bar_background(app, "resources/radio_bar_background.png", &view1)
    , radio_bar_grad(app, "resources/radio_bar_grad.png", &view1)
    , head_icon(app, "resources/head_icon.png", &view1)
    , background(app, "resources/background.png", &view1)
    , selection_border(app, "resources/selection_border.png", &view1)
    , tile_size(384)
{




    citizen_max = 10;
    monster_max = 10;
    citizen_number = citizen_max;
    pause = false;
    clicked = false;


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
            if (x == 0)
            {
                map[x][y].setID(1);
            }
            else
            {
                map[x][y].setID(2);
            }
        }
    }
    
    //init sprites
    string path = "";
    for (int i = 0; i < 10 ; i++) {
        path = "resources/tile" + std::to_string(i) + ".png";
        sprites.push_back( My_Sprite{ m_app, path, &m_view1 });
        std::cout << path << endl;

    }

    //character in first case
    for (int i = 0; i < citizen_max; i++)
    {
        character1.push_back( Character{ m_app, &m_view1, i });
        citizen_state.push_back(true);
    }
    citizen_number_text.init(app, "Still alive: ", 35, 1);

    //monsters on surface
    for (int i = 0; i < monster_max; i++)
    {
        monster1.push_back( Monster{ m_app, &m_view1, i });
    }
    citizen_number_text.init(app, "Still alive: ", 35, 1);

    //all the buttons
  
        buttons.push_back( Button{ m_app, "creuser", 0, 0, 0, 0, &m_view1 });

    //music init

    if (!music.openFromFile("resources/music.ogg"))
    {
        cout << "music init failed" << endl;
    }

    music.play();
}


void Game_Manager::update(int timeElapsed)
{
    handle_input_events();

    if (!pause)
    {
        m_view1.setCenter(static_cast<float>(m_x_offset), static_cast<float>(m_y_offset));
        m_app->setView(m_view1);


        buttons[0].update(selected_tile.clicked_x* tile_size, selected_tile.clicked_y * tile_size);

        for (int i = 0; i < citizen_max; i++) {
            if (citizen_state[i])
            { 
                character1[i].update();
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
        if (clicked)
        {
            selected_tile.previous_clicked_x = selected_tile.clicked_x;
            selected_tile.previous_clicked_y = selected_tile.clicked_y;

            selected_tile.clicked_x = selected_tile.x;
            selected_tile.clicked_y = selected_tile.y;

            //map[selected_tile.x][selected_tile.y].
        }

        citizen_number_text.refill("Still alive: " + std::to_string(citizen_number));
    }
}


void Game_Manager::draw()
{
    int Id;

    static sf::Clock render_clock;
    if (render_clock.getElapsedTime().asMilliseconds() < 2) {
        return;
    }
    render_clock.restart();
    m_app->clear();

    background.draw(0,0  - background.get_h() );
   
    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            sprites[map[x][y].getId()].draw(tile_size * x, tile_size * y);
        }
    }
  

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
    selection_border.draw(selected_tile.clicked_x * tile_size, selected_tile.clicked_y * tile_size);
    buttons[0].draw();

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

    head_icon.draw(1920 - head_icon.get_w(), 0 );



    citizen_number_text.draw(1920 -( head_icon.get_w() * 2.5) , 0, 35);

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
