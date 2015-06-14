
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
    int get_ressources();
    void draw_tile();
    float get_radiation();
    int isWalkable();
    void constru(int newID, int progressMax);
    void addProgress(float pr);

private:
    int m_level, m_rubble, m_oxygen, m_ID, resource_number;
    float m_irradiation;
    int m_efRubble, m_prod, m_def, m_maxHp, m_Hp;
    int walkable;
    int m_node;
    int m_progress, m_progressMax, m_futID;
    enum Work { NO, DIGING, BUILDING };
    Work m_work;
    vector <Ressource> resource1;
};

