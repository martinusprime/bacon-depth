#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include "My_Sprite.h"
#include "My_Text.h"
#include "Character.h"



class Glissor
{
public:
    Glissor(RenderWindow *app, int x, int y, int window_x, int window_y, View *view1);
    /* copy-constructor */
    Glissor(const Glissor &glissor_get);
    virtual ~Glissor() = default;
    void draw(int nbChar);
    void init();
    void update(int x, int y, int nbChar);
    int get_value();

private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite m_bar, m_cursor_bar;
    int m_x, m_y, m_value, m_w, m_h, m_window_x, m_window_y;
    bool m_mouse_on;
    Vector2f m_a;
    Vector2i m_mouse_vec;
    My_Text m_rate;
};

