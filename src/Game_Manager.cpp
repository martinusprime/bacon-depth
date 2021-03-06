#include "Game_Manager.h"

#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
    : m_view1(view1)
    , radio_icon(app, "resources/radioactive_icon.png", &view1)
    , food_icon(app, "resources/food_icon0.png", &view1)
    , metal_icon(app, "resources/iron_icon0.png", &view1)
    , radio_bar(app, "resources/radio_bar.png", &view1)
    , radio_bar_background(app, "resources/radio_bar_background.png", &view1)
    , radio_bar_grad(app, "resources/radio_bar_grad.png", &view1)
    , oxygen_bar(app, "resources/oxygen_bar.png", &view1)
    , oxygen_bar_background(app, "resources/oxygen_bar_background.png", &view1)
    , oxygen_bar_grad(app, "resources/oxygen_bar_grad.png", &view1)
    , head_icon(app, "resources/head_icon.png", &view1)
    , explosion(app, "resources/explosion.png", &view1)
    , background(app, "resources/background.png", &view1)
    , selection_border(app, "resources/selection_border.png", &view1)
    , goal_border(app, "resources/selection_border.png", &view1)
    , end_sprite(app, "resources/end.png", &view1)
    , bomb(app, "resources/bomb.png", &view1)
    , pause_sprite(app, "resources/pause.png", &view1)
    , info_sprite(app, "resources/info.png", &view1)
    , spriteTile0(app, "resources/invisible.png", &view1)
    , tile_size(384)
{

    //sounds
    buffer.loadFromFile("resources/explosion.ogg");

    sound.setBuffer(buffer);

    buffer_combat.loadFromFile("resources/combat.ogg");

    sound_combat.setBuffer(buffer_combat);

    monster_time.restart();

    //

    zoom = 1;
    zoom_rate = 10;
    zoom_change = ZOOM_NO_CHANGE;




    goal_border.add_color(255, 150, 50, 255);

    citizen_max = 10;
    monster_max = 10;
    citizen_number = citizen_max;
    food_number = 0;
    metal_number = 0;
    pause = false;
    clicked = false;
    glissor_on = false;
    info = true;
    cinematic_on = true;
    m_x_offset = tile_size * 2 + (tile_size / 2);
    m_y_offset = (tile_size / 2);
    oxygen_number = 1.0f;
    fail = false;

    m_app = app;
    m_app->setView(m_view1);

    m_screen_y = 1080;
    m_screen_x = 1920;

    m_view2.reset(FloatRect(0.0f, 0.0f, static_cast<float>(m_screen_x), static_cast<float>(m_screen_y)));
    m_view2.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    //init map
    for (size_t y = 0; y < 10; y++)
    {
        for (size_t x = 0; x < 5; x++)
        {

            my_map[y][x].setLevel(y);
            my_map[y][x].init_resources(m_app, &view1, x, y);

            if (y == 0)
            {            //surface

                my_map[y][x].setID(6 + x);
            }            
            else if(x >= 2 && x <5 && y == 4)
            {            //metro 3, 4, 5
                my_map[y][x].setID(1 + x);
            }
             else if(x >= 1 && x <4 && y == 6)
            {            //soutterrain

                my_map[y][x].setID(10 + x);
            }
             else if(x >= 2 && x <5 && y == 2)
            {            //egouts

                my_map[y][x].setID(12 + x);
            }
             else if (x >= 1 && x <4 && y == 5)
             {           

                 my_map[y][x].setID(24);
             }
             else if (x >= 0 && x <4 && y == 6)
             {

                 my_map[y][x].setID(24);
             }
             else if (x >= 0 && x <3 && y == 4)
             {            

                 my_map[y][x].setID(23);
             }
             else
            {
                my_map[y][x].setID(0);

            }
            // cout << my_map[y][x].isWalkable() << " ";
        }
     //   cout << endl;
    }

    //init sprites
    string path = "";
    for (int i = 0; i < 27; i++) {
        path = "resources/tile" + std::to_string(i) + ".png";
        sprites.push_back(My_Sprite{ m_app, path, &m_view1 });
        //      std::cout << path << endl;

    }

    //character in first case
    for (int i = 0; i < citizen_max; i++)
    {
        character1.push_back(Character{ m_app, &m_view1, i });
        citizen_state.push_back(true);
        character1[i].setPosition(2, 0);
    }
    citizen_number_text.init(app, "Still alive: ", 35, 1);
    metal_number_text.init(app, "Metal: ", 35, 1);
    food_number_text.init(app, "Foods: ", 35, 1);



    //monsters on surface
    for (int i = 0; i < monster_max; i++)
    {
        monster_state.push_back(true);
        monster1.push_back(Monster{ m_app, &m_view1, i });
    }
    citizen_number_text.init(app, "Still alive: ", 35, 1);

    //all the buttons

    buttons.push_back(Button{ m_app, "Dig", 0, 0, 0, 0, &m_view1 });
    buttons.push_back(Button{ m_app, "Move", 0, 0, 0, 0, &m_view1 });//button of the glissor
    buttons.push_back(Button{ m_app, 0, 0, 0, 0, &m_view1 });
    buttons.push_back(Button{ m_app, "Take resources", 0, 0, 0, 0, &m_view1 });//button of the ressources

    //buttons of buildings
    buttons.push_back(Button{ m_app, "resources/workshop_icon.png", true, 0, 0, 0, 0, &m_view2 });//button of the ressources
    buttons.push_back(Button{ m_app, "resources/electricity_icon.png", true, 0, 0, 0, 0, &m_view2 });//button of the ressources
    buttons.push_back(Button{ m_app, "resources/farm_icon.png", true, 0, 0, 0, 0, &m_view2 });//button of the ressources
    buttons.push_back(Button{ m_app, "resources/armory_icon.png", true, 0, 0, 0, 0, &m_view2 });//button of the ressources
    buttons.push_back(Button{ m_app, "resources/oxygen_icon.png", true, 0, 0, 0, 0, &m_view2 });//button of the ressources
    buttons.push_back(Button{ m_app, "resources/bunker_icon.png", true, 0, 0, 0, 0, &m_view2 });//button of the ressources


    glissor1.push_back(Glissor{ m_app, 0, 0, 0, 0, &m_view1 });
 
    update(0);
    cinematic_init();
    oxygen_clock.restart();
}

void Game_Manager::reset()
{

    citizen_max = 10;
    monster_max = 10;
    citizen_number = citizen_max;
    food_number = 0;
    metal_number = 0;
    pause = false;
    clicked = false;
    glissor_on = false;
    info = true;
    cinematic_on = true;
    m_x_offset = tile_size * 2 + (tile_size / 2);
    m_y_offset = (tile_size / 2);
    oxygen_number = 1.0f;
    fail = false;


    //init map
    for (size_t y = 0; y < 10; y++)
    {
        for (size_t x = 0; x < 5; x++)
        {

            my_map[y][x].setLevel(x);
            my_map[y][x].init_resources(m_app, &m_view1, x, y);

            if (y == 0)
            {            //surface

                my_map[y][x].setID(6 + x);
            }            
            else if(x >= 2 && x <5 && y == 4)
            {            //metro 3, 4, 5
                my_map[y][x].setID(1 + x);
            }
             else if(x >= 1 && x <4 && y == 6)
            {            //soutterrain

                my_map[y][x].setID(10 + x);
            }
             else if(x >= 2 && x <5 && y == 2)
            {            //egouts

                my_map[y][x].setID(12 + x);
            }
             else if (x >= 1 && x <4 && y == 5)
             {           

                 my_map[y][x].setID(24);
             }
             else if (x >= 0 && x <4 && y == 6)
             {

                 my_map[y][x].setID(24);
             }
             else if (x >= 0 && x <3 && y == 4)
             {            

                 my_map[y][x].setID(23);
             }
             else
            {
                my_map[y][x].setID(0);

            }
            // cout << my_map[y][x].isWalkable() << " ";
        }
        //   cout << endl;
    }

    for (int i = 0; i < monster_max; i++)
    {
        monster_state[i] = true;
    }
    for (int i = 0; i < citizen_max; i++)
    {
        citizen_state[i] = true;
    }
    update(0);
    cinematic_init();
    monster_time.restart();
    oxygen_clock.restart();
}

void Game_Manager::update(float timeElapsed)
{
    handle_input_events();
    m_view1.zoom(zoom);


    
    if (monster_time.getElapsedTime().asSeconds() >= 45)
    {
        monster_time.restart();
        int a = rand() % 5 + 1;
        for (int i = 0; i <= a; i++)
        {
            monster_max++;
            monster1.push_back(Monster{ m_app, &m_view1, i });
            monster_state.push_back(true);
        }
    }



    zoom_time = clock_zoom.getElapsedTime();
    if (zoom_time.asSeconds() >  0.05  && zoom_change != ZOOM_NO_CHANGE)
    {
        clock_zoom.restart();
        if (zoom_change == ZOOM_ADD && zoom_rate >= -30)
        {
            zoom = 0.90f;
            zoom_rate--;
        }
        if (zoom_change == ZOOM_LESS  && zoom_rate <= 50)
        {
            zoom = 1.1f;
            zoom_rate++;
        }
        zoom_change = ZOOM_NO_CHANGE;
    }
    else
    {
        zoom = 1;
    }


    if (citizen_number == 0 || oxygen_number == 0.0f)
    {
        fail = true;
        reset();
    }

    if (cinematic_on)
    {
        cinematic_update();
    }

    if (!pause)
    {
        m_view1.setCenter(static_cast<float>(m_x_offset), static_cast<float>(m_y_offset));
        m_app->setView(m_view1);

        //radiation haldling
        radio_bar.scale(1.0f, my_map[selected_tile.clicked_y][selected_tile.clicked_x].get_radiation(), true);
        //oxygen_handling
        if (oxygen_clock.getElapsedTime().asSeconds() > 0.5f)
        {
            oxygen_clock.restart();
            oxygen_number -= 0.0008;
        }
        oxygen_bar.scale(oxygen_number, 1.0f, false);

        buttons[0].update(selected_tile.clicked_x* tile_size, selected_tile.clicked_y * tile_size);
        if (buttons[0].is_activated())
        {
            buttons[0].desactivate();
            execute_action(ACT_DIGING);
        }

        buttons[1].update(selected_tile.goal_x* tile_size, selected_tile.goal_y * tile_size + buttons[1].get_h());

        if (buttons[1].is_activated())
        {
            buttons[1].desactivate();
            execute_action(ACT_MOVE);
        }

        buttons[2].update((selected_tile.clicked_x + 1)* tile_size - buttons[2].get_h(), selected_tile.clicked_y * tile_size + buttons[2].get_h());
        if (buttons[2].is_activated())
        {
            buttons[2].desactivate();
            execute_action(ACT_STOP);
        }

        buttons[3].update(selected_tile.clicked_x* tile_size, selected_tile.clicked_y * tile_size + buttons[3].get_h());
        if (buttons[3].is_activated())
        {
            buttons[3].desactivate();
                if (isOccupied(selected_tile.clicked_x ,selected_tile.clicked_y) )
              {
               if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].get_resources_id() == 0)
             {
            metal_number += my_map[selected_tile.clicked_y][selected_tile.clicked_x].get_ressources();
            }
            if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].get_resources_id() == 1)
            {
                food_number += my_map[selected_tile.clicked_y][selected_tile.clicked_x].get_ressources();
            }
            }
        }

        buttons[4].update(m_screen_x - buttons[4].get_w() - 30, m_screen_y / 2 + buttons[4].get_h());
        if (buttons[4].is_activated())
        {
            buttons[4].desactivate();
            if (isOccupied(selected_tile.clicked_x, selected_tile.clicked_y))
            {
                execute_action(ACT_BUILD_WORKBENCH);
            }
        }

        buttons[5].update(m_screen_x - buttons[5].get_w() - 30, (m_screen_y / 2) + (buttons[5].get_h() + 80));
        if (buttons[5].is_activated())
        {
            buttons[5].desactivate();
            execute_action(ACT_BUILD_GENERATOR);

        }

        buttons[6].update(m_screen_x - buttons[5].get_w() - 30, (m_screen_y / 2) + (buttons[6].get_h() + 80 * 2));
        if (buttons[6].is_activated())
        {
            buttons[6].desactivate();
            execute_action(ACT_BUILD_FARM);
        }

        buttons[7].update(m_screen_x - buttons[7].get_w() - 30, (m_screen_y / 2) + (buttons[7].get_h() + 80 * 3));
        if (buttons[7].is_activated())
        {
            buttons[7].desactivate();

            execute_action(ACT_BUILD_ARMORY);
        }

        buttons[8].update(m_screen_x - buttons[8].get_w() - 30, (m_screen_y / 2) + (buttons[8].get_h() + 80 * 4));
        if (buttons[8].is_activated())
        {
            buttons[8].desactivate();

            execute_action(ACT_BUILD_AERATION);
        }

        buttons[9].update(m_screen_x - buttons[9].get_w() - 30, (m_screen_y / 2) + (buttons[9].get_h() + 80 * 5));
        if (buttons[9].is_activated())
        {
            buttons[9].desactivate();

            execute_action(ACT_BUILD_BUNKER);
        }

        for (int i = 0; i < citizen_max; i++) {
            if (citizen_state[i])
            {
                character1[i].update(my_map, timeElapsed);

                //my_map[character1[i].getY][character1[i].getX].addCharacter(*character1[i]);

                if (!character1[i].alive())
                {
                    citizen_number--;
                    citizen_state[i] = false;
                }
            }
        }

        for (int i = 0; i < monster_max; i++) {
            if (monster_state[i])
            {
                monster1[i].newGoal(character1[1].getX(), character1[1].getY());
                monster1[i].update(my_map, timeElapsed);
                if (!monster1[i].alive())
                {
                    monster_state[i] = false;
                }
            }
        }

        for (size_t x = 0; x < 5; x++)
        {
            for (size_t y = 0; y < 10; y++)
            {
                my_map[x][y].update(timeElapsed);
            }
        }
        //if the mouse is over the right tile

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

        if (mouse_vec.x < m_screen_x - buttons[6].get_w() - 30)
        {
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

                    if (selected_tile.x != selected_tile.clicked_x
                        || selected_tile.y != selected_tile.clicked_y)
                    {
                        selected_tile.goal_x = selected_tile.x;
                        selected_tile.goal_y = selected_tile.y;
                        glissor_on = true;
                    }
                }
            }
        }

        citizen_number_text.refill("Still alive: " + std::to_string(citizen_number));
         food_number_text.refill("Food: " + std::to_string(food_number));
        metal_number_text.refill("Metal: " + std::to_string(metal_number));
    }
    combat(timeElapsed);
}

bool Game_Manager::isOccupied(int x, int y)
{
    for (size_t i = 0; i < character1.size(); i++)
    {
        if ((character1[i].getX() == x) && (character1[i].getY() == y))
        {
            return 1;
        }
    }
    return 0;
}

void Game_Manager::cinematic_update()
{
    if (cinematic_clock.getElapsedTime().asSeconds() > 0.5)
    {
        cinematic_time += 0.3;
        bomb_y += cinematic_time;
        if (explosing)
        {
            explosion.scale(1.0f + cinematic_time, 1.0f + cinematic_time, false);
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
    if (bomb_y >= tile_size - bomb.get_h() && !explosing)
    {
        cinematic_time = 1.0f;
        explosing = true;
        sound.play();

    }
    if (explosing && cinematic_time >= 6.5f)
    {
        pause = false;
        cinematic_on = false;
        //music init

        if (!music.openFromFile("resources/nostalgia.ogg"))
        {
            cout << "music init failed" << endl;
        }
        music.setLoop(true);

        music.play();
        //
    }

}
void Game_Manager::cinematic_draw()
{

    if (explosing)
    {
        if (!explosion_flash)
        {
            explosion.draw(0, -tile_size);
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
    bomb_y = -tile_size;
    cinematic_time = 5.0f;
    while (info)
    {
        draw();
        if (handle_input_events_key())
        {
            info = false;
        }
    }

    cinematic_clock.restart();
}


void Game_Manager::draw()
{
    int Id;

    static sf::Clock render_clock;

    render_clock.restart();
    m_app->clear();

    background.draw(0, 0 - tile_size);

    for (size_t x = 0; x < 5; x++)
    {
        for (size_t y = 0; y < 10; y++)
        {
            sprites[my_map[y][x].getId()].draw(tile_size * x, tile_size * y);
            my_map[y][x].draw_tile();
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
        if (monster_state[i])
        {
            monster1[i].draw();
        }
    }
    goal_border.draw(selected_tile.goal_x* tile_size, selected_tile.goal_y * tile_size);/////////////////////////////////////////////////////
    selection_border.draw(selected_tile.clicked_x * tile_size, selected_tile.clicked_y * tile_size);
    buttons[0].draw();
    buttons[1].draw();
    buttons[2].draw();
    buttons[3].draw();

    int compteur = 0;
    for (int i = 0; i < character1.size(); i++)
    {
        if ((character1[i].getX() == selected_tile.clicked_x) && (character1[i].getY() == selected_tile.clicked_y) && (character1[i].isIdle()))
        {
            compteur++;
        }
    }


    if (cinematic_on)
    {
        cinematic_draw();
    }
    if (info)
    {
        info_sprite.draw(0, 0 - tile_size);
    }


    if (glissor_on)
    {
        glissor1[0].update(selected_tile.goal_x* tile_size, selected_tile.goal_y * tile_size, compteur);
        glissor1[0].draw(character1.size());
    }
    //pause handling

    if (!pause)
    {
        hud();
    }
    if (pause && !cinematic_on)
    {
        pause_sprite.draw(tile_size,  0);
    }// Update the window
    m_app->display();


}
void Game_Manager::hud()
{
    m_app->setView(m_view2);

    radio_icon.draw(0, 0);

    radio_bar_background.draw(0, radio_icon.get_h());
    radio_bar.draw(0 + 28, radio_icon.get_h() + 40);
    radio_bar_grad.draw(0, radio_icon.get_h());

    oxygen_bar_background.draw(0 + 150, m_screen_y - oxygen_bar_background.get_h() - 20);
    oxygen_bar.draw(0 + 150, m_screen_y - oxygen_bar_background.get_h() - 20);
    oxygen_bar_grad.draw(0 + 150, m_screen_y - oxygen_bar_background.get_h() - 20);

    head_icon.draw(m_screen_x - head_icon.get_w(), 0);
    food_icon.draw(m_screen_x - food_icon.get_w(), 200);
    metal_icon.draw(m_screen_x - metal_icon.get_w(), 400);

    buttons[4].draw();
    buttons[5].draw();
    buttons[6].draw();
    buttons[7].draw();
    buttons[8].draw();
    buttons[9].draw();


    citizen_number_text.draw(m_screen_x - (head_icon.get_w() * 2.5), 0, 35);
    metal_number_text.draw(m_screen_x - (head_icon.get_w() * 2.5), 400, 35);
    food_number_text.draw(m_screen_x - (head_icon.get_w() * 2.5), 200, 35);

    m_app->setView(m_view1);
}

void Game_Manager::execute_action(Action action)
{
    int compteur = 0;
    switch (action)
    {
    case ACT_GO_UP:
        m_y_offset -= tile_size / 4;
        break;
    case ACT_GO_RIGHT:
        m_x_offset += tile_size/4;

        break;
    case ACT_GO_DOWN:
        m_y_offset += tile_size / 4;
        break;
    case ACT_GO_LEFT:
        m_x_offset -= tile_size / 4;
        break;
    case ACT_ZOOM_IN:
        zoom_change = ZOOM_ADD;
        break;
    case ACT_ZOOM_OUT:
        zoom_change = ZOOM_LESS;
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
    case ACT_MOVE:       
        for (size_t i = 0; i < character1.size(); i++)
        {
            if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)) &&
                (my_map[selected_tile.goal_y][selected_tile.goal_x].isWalkable()))
            {               
                character1[i].newGoal(selected_tile.goal_x, selected_tile.goal_y);
            //    cout << "GOAL" << selected_tile.goal_x << " " << selected_tile.goal_y << endl;
                compteur++;
            }
        }
        break;
    case ACT_STOP:
        for (size_t i = 0; i < character1.size(); i++)
        {
            if ((character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
            {
                character1[i].stop();
            }
        }
        break;
    case ACT_DIGING:
        if (((selected_tile.goal_y == selected_tile.clicked_y) && (selected_tile.goal_x == (selected_tile.clicked_x) + 1)) ||
            ((selected_tile.goal_y == selected_tile.clicked_y) && (selected_tile.goal_x == (selected_tile.clicked_x) - 1)) ||
            ((selected_tile.goal_y == (selected_tile.clicked_y) + 1) && (selected_tile.goal_x == selected_tile.clicked_x)) ||
            ((selected_tile.goal_y == (selected_tile.clicked_y) - 1) && (selected_tile.goal_x == selected_tile.clicked_x)))
        {
            if (my_map[selected_tile.goal_y][selected_tile.goal_x].isWalkable() == 0)
            {
                my_map[selected_tile.goal_y][selected_tile.goal_x].constru(1, 1000000);
                for (size_t i = 0; i < character1.size(); i++)
                {
                    if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                    {
                        character1[i].dig(selected_tile.goal_x, selected_tile.goal_y);
                        compteur++;
                    }
                }
            }
        }
        break;
    case ACT_BUILD_GENERATOR:
        if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].getId() != 0)
        {    
            my_map[selected_tile.clicked_y][selected_tile.clicked_x].constru(17, 100000);            
            for (size_t i = 0; i < character1.size(); i++)
            {
                if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                {
                    character1[i].build(selected_tile.clicked_x, selected_tile.clicked_y);
                    compteur++;
                }
            }
        }
        break;
    case ACT_BUILD_AERATION:
        if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].getId() != 0)
        {
            my_map[selected_tile.clicked_y][selected_tile.clicked_x].constru(18, 100000);
            for (size_t i = 0; i < character1.size(); i++)
            {
                if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                {
                    character1[i].build(selected_tile.clicked_x, selected_tile.clicked_y);
                    compteur++;
                }
            }
        }
        break;
    case ACT_BUILD_FARM:
        if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].getId() != 0)
        {
            my_map[selected_tile.clicked_y][selected_tile.clicked_x].constru(19, 100000);
            for (size_t i = 0; i < character1.size(); i++)
            {
                if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                {
                    character1[i].build(selected_tile.clicked_x, selected_tile.clicked_y);
                    compteur++;
                }
            }
        }
        break;
    case ACT_BUILD_ARMORY:
        if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].getId() != 0)
        {
            my_map[selected_tile.clicked_y][selected_tile.clicked_x].constru(20, 100000);
            for (size_t i = 0; i < character1.size(); i++)
            {
                if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                {
                    character1[i].build(selected_tile.clicked_x, selected_tile.clicked_y);
                    compteur++;
                }
            }
        }
        break;
    case ACT_BUILD_WORKBENCH:
        if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].getId() != 0)
        {
            my_map[selected_tile.clicked_y][selected_tile.clicked_x].constru(21, 100000);
            for (size_t i = 0; i < character1.size(); i++)
            {
                if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                {
                    character1[i].build(selected_tile.clicked_x, selected_tile.clicked_y);
                    compteur++;
                }
            }
        }
        break;
    case ACT_BUILD_BUNKER:
        if (my_map[selected_tile.clicked_y][selected_tile.clicked_x].getId() != 0)
        {
            my_map[selected_tile.clicked_y][selected_tile.clicked_x].constru(22, 1000000);
            for (size_t i = 0; i < character1.size(); i++)
            {
                if ((compteur < glissor1[0].get_value()) && (character1[i].isOnPos(selected_tile.clicked_x, selected_tile.clicked_y)))
                {
                    character1[i].build(selected_tile.clicked_x, selected_tile.clicked_y);
                    compteur++;
                }
            }
        }
        break;
    default:
        break;
    }
    
    if (m_y_offset < (tile_size / 2))
    {
        m_y_offset = (tile_size / 2);
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

bool Game_Manager::handle_input_events_key()
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
        
    }
    return ret;
}

void Game_Manager::combat(float time)
{
    int combat = 0;
    for (size_t i = 0; i <= character1.size(); i++)
    {
        for (size_t j = 0; j <= monster1.size(); j++)
        {
            if (monster_state[j])
            {
                //cout << "BASTON" << endl;
                if (my_map[monster1[j].getY()][monster1[j].getX()].isBuilding())
                {
                    my_map[monster1[j].getY()][monster1[j].getX()].get_damage(0.001*time);
                }
                if ((monster1[j].getY() == character1[i].getY()) && (monster1[j].getX() == character1[i].getX()))
                {
                    combat = 1;
                    //cout << "BASTON2" << endl;
                    character1[i].setBattle();
                    if (my_map[monster1[j].getY()][monster1[j].getX()].isBuilding() == 0)
                    {
                        character1[i].get_damage(0.001*time);
                    }
                    monster1[j].get_damage(0.001*time);
                }
            }

        }




    }

    for (size_t i = 0; i <= character1.size(); i++)
    {
        if ((combat == 0) && (character1[i].isBattle()))
        {
            cout << "IDLE" << endl;
            character1[i].setIdle();
        }
    }
}
