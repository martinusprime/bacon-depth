#include <SFML/Graphics.hpp>
#include "Game_Manager.h"
#include <iostream>

using namespace sf;







int main()
{
<<<<<<< HEAD
    int time;
=======
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
    try
    {
        int screen_y = 1080;
        int screen_x = 1920;
        RenderWindow app(VideoMode(screen_x, screen_y), "SFML window for the bacon" );
        app.setFramerateLimit(60);
        View view1(FloatRect(0, 0, screen_x, screen_y));
        view1.setViewport(FloatRect(0, 0, 1.0f, 1.0f));

        Game_Manager game_manager1(&app, view1, screen_x, screen_y);
<<<<<<< HEAD
        
        //////////////////////////////
        static sf::Clock render_clock;
        ////////////////////////////
=======
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4

        // Start the game loop
        while (app.isOpen() )
        {
<<<<<<< HEAD
            game_manager1.update();
            game_manager1.draw();
=======
<<<<<<< HEAD
            cout << render_clock.getElapsedTime().asSeconds()<<endl;
            render_clock.restart();
            game_manager1.draw();
=======
         
>>>>>>> 85fa15d470118025d890dd26b2b596089fbadae4
>>>>>>> c945af70963bf10b02ac1a7b4d2a438e20ec0958
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Terminate program with exception " << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}