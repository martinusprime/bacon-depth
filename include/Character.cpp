#include "Character.h"


Character::Character(RenderWindow *app, View *view)
    : sprite(app, "resources/projet0.png", view)
{
    m_view1 = view;
    m_app = app;
}


Character::~Character()
{
}


void Character::update()
{
}


void Character::draw()
{
    sprite.draw(500, 500);
}
