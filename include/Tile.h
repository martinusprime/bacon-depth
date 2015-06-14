#include <vector>

#pragma once
class Tile
{
public:
    Tile();
    ~Tile();
    void setLevel(int y);
    void setID(int ID);
    int getId();
    void update(int time);
    void setNode(int node);
    int getNode();
    int isWalkable();
    void constru(int newID, int progressMax);

private:
    int m_irradiation, m_level, m_rubble, m_oxygen, m_ID;
    int m_efRubble, m_prod, m_def, m_maxHp, m_Hp;
    int walkable;
    int m_node;
    int m_progress, m_progressMax, m_futID;
    enum Work { NO, DIGING, BUILDING };
    Work m_work;
};

