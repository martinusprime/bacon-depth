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