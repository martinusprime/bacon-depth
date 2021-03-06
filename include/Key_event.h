#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include <SFML/Graphics.hpp>
#include <map>

enum Action
{
    ACT_ZOOM_IN,
    ACT_ZOOM_OUT,
    ACT_GO_UP,
    ACT_GO_DOWN,
    ACT_GO_RIGHT,
    ACT_GO_LEFT,
    ACT_PAUSE,
    ACT_CLOSE_APP,
    ACT_MOVE,
    ACT_STOP,
    ACT_DIGING,
    ACT_BUILD_GENERATOR,
    ACT_BUILD_AERATION,
    ACT_BUILD_FARM,
    ACT_BUILD_ARMORY,
    ACT_BUILD_WORKBENCH,
    ACT_BUILD_BUNKER
};


class Key_event_handler
{
public:
    Key_event_handler();
    virtual ~Key_event_handler();
    /* return true if an event was handled
    action is an "out" parameter. */
    bool manage_key_event(const sf::Event &event, Action &action);
    void get_mouse_position(const sf::RenderWindow *app, sf::Vector2i &mouse_vec);
    /* return true if an event was handled (=if the user clicked) */
    bool manage_mouse_click(const sf::Event &event, enum sf::Mouse::Button &click);

private:
    std::map<sf::Keyboard::Key, Action> key_action;
};

#endif // KEY_EVENT_H
