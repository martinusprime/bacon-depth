#include "Tile.h"


Tile::Tile()
{
    m_irradiation = 0;
    m_level = 0;
    m_rubble = 100;
    m_oxygen = 100;
    m_ID = 0;
    m_efRubble = 10;
    m_prod = 0;
    m_def = 0;
    m_maxHp = 0;
    m_Hp = 0;
    walkable = 1;
    m_work = NO;
}

Tile::~Tile()
{
}

void Tile::setLevel(int y)
{
    m_level = y;
}

void Tile::setID(int ID)
{
    m_ID = ID;
    if (ID == 0)
    {
        walkable = 0;
    }
    else
    {
        walkable = 1;
    }
    if ((ID >= 17) && (ID <= 21))
    {
        m_prod = 10;
        m_def = 0;
        m_maxHp = 100;
        m_Hp = 100;
    }
    else if (ID == 22)
    {
        m_prod = 0;
        m_def = 10;
        m_maxHp = 1000;
        m_Hp = 1000;
    }
    else
    {
        m_prod = 0;
        m_def = 0;
        m_maxHp = 0;
        m_Hp = 0;
    }
}

int Tile::getId()
{
    return m_ID;
}

void Tile::update(int time)
{
    m_irradiation += time / 5 * (10 - m_level);

    if ((m_progress >= m_progressMax) && (m_work != NO))
    {
        m_work = NO;
        m_ID = m_futID;
        m_progress = 0;
    }
}

void Tile::setNode(int node)
{
    m_node = node;
}

int Tile::getNode()
{
    return m_node;
}

int Tile::isWalkable()
{
    return walkable;
}

void Tile::constru(int newID, int progressMax)
{
    m_progress = 0;
    m_progressMax = progressMax;
    m_futID = newID;
}