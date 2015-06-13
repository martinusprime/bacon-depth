#include <SFML/Graphics.hpp>
#include "Game_Manager.h"
#include <iostream>

using namespace sf;







int main()
{
    int time;
    try
    {
        int screen_y = 1080;
        int screen_x = 1920;
        RenderWindow app(VideoMode(screen_x, screen_y), "SFML window for the bacon" );
        app.setFramerateLimit(60);
        View view1(FloatRect(0, 0, screen_x, screen_y));
        view1.setViewport(FloatRect(0, 0, 1.0f, 1.0f));

        Game_Manager game_manager1(&app, view1, screen_x, screen_y);
       
        static sf::Clock render_clock;
 

        // Start the game loop
        while (app.isOpen() )
        {
<<<<<<< HEAD
            game_manager1.update(render_clock.getElapsedTime().asSeconds());            
            game_manager1.draw();
            
=======
            game_manager1.update(render_clock.getElapsedTime().asSeconds());
>>>>>>> 87cefd6457b7a402fd3c2c2fc08ebca8371263ae
           // cout << render_clock.getElapsedTime().asSeconds()<<endl;
            render_clock.restart();     
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Terminate program with exception " << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
