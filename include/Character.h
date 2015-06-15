#pragma once

#include "Button.h"
#include "Key_event.h"
#include "My_Sprite.h"
#include "Tile.h"
#include "Random.h"

using namespace sf;
class Tile;
class Character
{
public:
    Character(RenderWindow *app, View *view, int id);
    void update(Tile my_map[][5], float timeElapsed);
    void draw();
    bool alive();
    void get_damage(float damage);
    virtual ~Character();
    void newGoal(int x, int y);
    struct coord
    {
        int x;
        int y;
    };
    int pathFinding(Tile my_map[][5]);
    void setPosition(int x, int y);
    void moving(int x, int y);
    int getX();
    int getY();
    int isIdle();
    int isOnPos(int x, int y);
    void stop();
    void dig(int x, int y);
    void build(int x, int y);
    void setBattle();

private:
    View *m_view1;
    RenderWindow *m_app;
    enum Direction { UP, DOWN, LEFT, RIGHT };
    enum Status { IDLE, BATTLE, MOVING, DIGING, BUILDING};
    Direction direction;
    Status status;
    My_Sprite sprite, pike, hammer, sword;
    My_Sprite life_bar, life_bar_background, life_bar_heart;
    int m_id, tile_x, tile_y, walking_x, tile_size;
    float life;
    Clock render_clock, random_clock;
    bool is_alive;
    int m_goalX, m_goalY;
    float m_moving;
    int move_x, move_y;
    int m_digX, m_digY;
    int m_buildX, m_buildY;
};

