#include "Glissor.h"

Glissor::Glissor(const Glissor &glissor_get)
    : m_bar(glissor_get.m_app, "resources/bar.png", glissor_get.m_view1)
    , m_cursor_bar(glissor_get.m_app, "resources/cursor_bar.png", glissor_get.m_view1)
{
    m_view1 = glissor_get.m_view1;
    m_app = glissor_get.m_app;
   
    m_x = glissor_get.m_x;
    m_y = glissor_get.m_y;
    m_value = glissor_get.m_value;
    m_window_x = glissor_get.m_window_x;
    m_window_y = glissor_get.m_window_y;
    m_mouse_on = glissor_get.m_mouse_on;
    m_a = glissor_get.m_a;
    m_mouse_vec = glissor_get.m_mouse_vec;
    m_rate = glissor_get.m_rate;
}

Glissor::Glissor(RenderWindow *app, int x, int y, int window_x, int window_y, View *view1)
    : m_bar(app, "resources/bar.png", view1)
    , m_cursor_bar(app, "resources/cursor_bar.png", view1)
{
    m_view1 = view1;
    m_window_x = window_x;
    m_window_y = window_y;
    m_x = x;
    m_y = y;
    
    m_app = app;
    m_rate.init(app, "0", 55, 1);
    m_value = 0;
    m_mouse_on = false;
}

void Glissor::draw(int nbChar)
{
    m_bar.draw(m_x, m_y);
    m_cursor_bar.draw(m_x + m_value * 2 * nbChar, m_y - 13);
    m_rate.draw(m_x + m_window_x - 75, m_y + m_window_y, 25);
}

int Glissor::get_value()
{
    return m_value;
}

void Glissor::update(int x, int y, int nbChar)
{
    m_x = x;
    m_y = y;

    m_mouse_vec = Mouse::getPosition(*m_app);
    m_a = m_app->mapPixelToCoords(m_mouse_vec, *m_view1);
    if (Mouse::isButtonPressed(Mouse::Left) && m_a.x >= m_x + m_value * 2 && m_a.x <= m_x + m_value * 2 + 20
        && m_a.y >= m_y - 13 && m_a.y <= m_y - 13 + 50)
    {
        m_mouse_on = true;
    }
    if (m_mouse_on)
    {
        int cache_value = m_value;
        m_value = (m_a.x - m_x) / 2 / nbChar;
        //cout << (m_a.x - m_x) / 2 / nbChar << endl;
        if (m_value < 0)
        {
            m_value = 0;
        }
        if (m_value > nbChar)
        {
            m_value = nbChar;
        }
        if (m_value != cache_value)
        {
            m_rate.refill(std::to_string(m_value));
        }
    }
    if (!Mouse::isButtonPressed(Mouse::Left))
    {
        m_mouse_on = false;
    }

}
