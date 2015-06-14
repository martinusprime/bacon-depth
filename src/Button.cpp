#include "Button.h"

Button::Button(RenderWindow *app, string name, int x, int y, int window_x, int window_y, View *view1)
    : button_sprite(app, "resources/button.png", view1)
{
    m_x = x;
    m_y = y;
    m_w = button_sprite.get_w();
    m_h = button_sprite.get_h();
    m_app = app;
    m_view1 = view1;
    m_window_x = window_x;
    m_window_y = window_y;

    m_name.init(m_app, name, 75, 1);
    cross = false;
    mouse_on = false;
    mouse_click = false;
    activation = false;

}

Button::Button(RenderWindow *app_get, string name_get, bool a_file, int x_get, int y_get, int window_x_get, int window_y_get, View *view1_get)
    : button_sprite(app_get, name_get, view1_get)
{
    m_x = x_get;
    m_y = y_get;
    m_w = button_sprite.get_w();
    m_h = button_sprite.get_h();
    m_app = app_get;
    m_view1 = view1_get;
    cross = true;

    m_name.init(m_app, name_get, 75, 1);
    mouse_on = false;
    mouse_click = false;
    activation = false;

}
Button::Button(RenderWindow *app,  int x, int y, int window_x, int window_y, View *view1)
    : button_sprite(app, "resources/button_stop.png", view1)
{
    m_x = x;
    m_y = y;
    m_w = button_sprite.get_w();
    m_h = button_sprite.get_h();
    m_app = app;
    m_view1 = view1;
    m_window_x = window_x;
    m_window_y = window_y;

    cross = true;
    mouse_on = false;
    mouse_click = false;
    activation = false;

}
void Button::draw()
{
    button_sprite.draw(m_x, m_y);
    if (!cross)
    {
        m_name.draw(m_x + (m_w / 3), m_y, 40);
    }
}
int Button::get_w()
{
    return m_w;
}
int Button::get_h()
{
    return m_h;
}
void Button::update(int x_get, int y_get)
{
    m_x = x_get;
    m_y = y_get;

    mouse_vec = Mouse::getPosition(*m_app);
    m_a = m_app->mapPixelToCoords(mouse_vec, *m_view1);

    if (m_a.x >= m_x &&  m_a.x <= m_x + m_w
        && m_a.y >= m_y   && m_a.y <= m_y + m_h)
    {

        mouse_on = true;
    }
    else
    {
        mouse_on = false;
        button_sprite.add_color(50, 50, 50, 255);
    }
    if (mouse_on)
    {
        button_sprite.add_color(120, 120, 120, 255);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            mouse_click = true;
        }
    }
    if (mouse_click)
    {
        button_sprite.add_color(220, 220, 220, 255);

    }
    if (!Mouse::isButtonPressed(Mouse::Left))
    {
        if (mouse_click && mouse_on)
        {
            activation = true;
        }
        mouse_click = false;

    }

}

bool Button::is_activated()
{
    return activation;
}


void  Button::desactivate()
{
    activation = false;
}