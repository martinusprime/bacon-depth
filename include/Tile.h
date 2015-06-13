#pragma once
class Tile
{
public:
    Tile();
    ~Tile();
    void setLevel(int y);
    void Tile::setID(int ID);
    int getId();
    void update(int time);

private:
    int m_irradiation, m_level, m_rubble, m_oxygen, m_ID;
    int m_efRubble, m_prod, m_def, m_maxHp, m_Hp;
};

