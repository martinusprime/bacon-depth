
#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <iostream>
#include "random.h"
#include <cstdlib>
#include <string>
#include "Ressource.h"
class Ressource;
class Tile
{
public:
    Tile();
    ~Tile();
    void setLevel(int y);
    void setID(int ID);
    int getId();
    void update(float time);
    void setNode(int node);
    void init_resources(RenderWindow *app, View *view, int x, int y);
    int getNode();
    int get_resources_id();
    int get_ressources();
    void draw_tile();
    float get_radiation();
    int isWalkable();
    void constru(int newID, int progressMax);
    int addProgress(float pr);
    bool isBuilding();
    void get_damage(float damage);

private:
    int m_level, m_rubble, m_oxygen, m_ID, resource_number;
    float m_irradiation;
    int m_efRubble, m_prod, m_def;
    float m_maxHp, m_Hp;
    int walkable;
    int m_node, m_x, m_y, tile_size;
    float m_progress, m_progressMax;
    int m_futID, resources_id;
    enum Work { NO, DIGING, BUILDING };
    Work m_work;
    vector <Ressource> resource1;
    vector <My_Sprite> life;
    My_Text time_text;
};

