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
<<<<<<< HEAD
    m_work = NO;
=======
>>>>>>> 176b3e45dc458937956efef00ced334401d42fbf
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
}

int Tile::getId()
{
    return m_ID;
}

void Tile::update(int time)
{
    m_irradiation += time / 5 * (10 - m_level);
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
<<<<<<< HEAD
}

void Tile::constru(int newID, int progressMax)
{
    m_progress = 0;
    m_progressMax = progressMax;
    m_futID = newID;
}

void Tile::update()
{
    if (m_progress >= m_progressMax)
    {
        m_work = NO;
        m_ID = m_futID;
        m_progress = 0;
    }
=======
>>>>>>> 176b3e45dc458937956efef00ced334401d42fbf
}