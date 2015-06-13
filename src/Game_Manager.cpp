#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
    : m_view1(view1)
    , radio_icon(app, "resources/radioactive_icon.png", &view1)
    , radio_bar(app, "resources/radio_bar.png", &view1)
{
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
        sprites.push_back(My_Sprite{ m_app, path, &m_view1 });
        std::cout << path << endl;

    }
}


void Game_Manager::update()
{
    handle_input_events();

    m_view1.setCenter(static_cast<float>(m_x_offset), static_cast<float>(m_y_offset));
    m_app->setView(m_view1);

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

    
   
    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            sprites[map[x][y].getId()].draw(384 * x, 384 * y);
        }
    }

    hud();
    // Update the window
    m_app->display();
}
void Game_Manager::hud()
{
    m_app->setView(m_view2);
    radio_icon.draw(0, 0);
    radio_bar.draw(0, 0);
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
    Vector2i mouse_vec;

    key_event.get_mouse_position(m_app, mouse_vec);



    bool ret = false;
    if (isEvent)
    {
        if (key_event.manage_key_event(event, action))
        {
            execute_action(action);
            ret = true;
        }
        if (key_event.manage_mouse_click(event, click)) {
          
            ret = true;
        }
    }
    return ret;
}