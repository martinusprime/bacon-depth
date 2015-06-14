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
    resource_number = 0;
    srand(time(0));
    m_progress = 0;
}

Tile::~Tile()
{
}

void Tile::setLevel(int y)
{
    m_level = y;
}

float Tile::get_radiation()
{
    return m_irradiation;
}
void Tile::init_resources(RenderWindow *app, View *view, int x, int y)
{
    int random = Random::get_int(0, 4);
    
    for (int i = 0; i < random; i++)
    {
        cout << "it: "<< i<< "randomommo :" << random << endl;
        resource1.push_back(Ressource{ app, view, 0, resource_number, x, y });
        resource_number++;
    } srand(time(0));
}

int Tile::get_ressources()
{
    int total;
    total = resource_number;
    resource_number = 0;
    return total;
}
void Tile::setID(int ID)
{
    m_progress = 0;
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
void Tile::draw_tile()
{
    for (int i = 0; i < resource_number; i++)
    {
        resource1[i].draw();
    }
}
void Tile::update(float time)
{
    // m_irradiation doit etre comprise entre 0 et 1  a la fin;

    m_irradiation += (time / 5.0) / 100000.0 - m_level * 0.1;

    if (m_irradiation > 1.0f)
    {
        m_irradiation = 1.0f;
    }
    else if (m_irradiation < 0.0f)
    {
        m_irradiation = 0.0f;
    }
    
    if ((m_progress >= m_progressMax) && (m_work != NO))
    {
        m_work = NO;
        setID(m_futID);
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
    m_progressMax = progressMax;
    m_futID = newID;
    if (m_futID == 1)
    {
        m_work = DIGING;
    }
    else
    {
        m_work = BUILDING;
    }
}

void Tile::addProgress(float pr)
{
    m_progress += pr;
}