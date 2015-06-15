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
    tile_size = 384;
    m_progress = 0;
    srand(time(0));

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

int Tile::get_resources_id()
{
    return resources_id;
}

void Tile::init_resources(RenderWindow *app, View *view, int x, int y)
{

    resources_id = rand()%2 ;
    cout << "random id : " << resources_id << endl;
    int random = Random::get_int(0, 3);
    m_x = x;
    m_y = y;
    for (int i = 0; i < random; i++)
    {
        resource1.push_back(Ressource{ app, view, resources_id, resource_number, x, y });
        resource_number++;
    } 

    life.push_back(My_Sprite{ app, "resources/life_bar.png", view });
    life.push_back(My_Sprite{ app, "resources/life_bar_background.png", view });
    life.push_back(My_Sprite{ app, "resources/life_bar_heart.png", view });
    time_text.init(app, "dfsd", 55, 1);
}

int Tile::get_ressources()
{
    int total;
    total = resource_number;
    resource_number = 0;
    cout << total << endl;
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
    if (ID == 8)
    {
        m_prod = 0;
        m_def = 0;
        m_maxHp = 100;
        m_Hp = 1000;
    }
}

int Tile::getId()
{
    return m_ID;
}
void Tile::draw_tile()
{
    if (isBuilding())
    {
        life[1].draw(m_x * tile_size, m_y * tile_size - 70);
        life[0].draw(m_x * tile_size, m_y * tile_size - 70);
        life[2].draw(m_x * tile_size, m_y * tile_size - 70);
    }
    for (int i = 0; i < resource_number; i++)
    {
        resource1[i].draw();
    }
    if (m_work == DIGING)
    {
        time_text.draw(m_x * tile_size, m_y * tile_size, 50);
    }
}
void Tile::update(float time)
{

    float new_life = (m_Hp / m_maxHp)/10.0f;
    life[0].scale(new_life, 1.0f, false);
    // m_irradiation doit etre comprise entre 0 et 1  a la fin;
    float level = m_level;
    m_irradiation += ((time / 5.0f) + (0.5f / ((level + 1.0f) * 2))) / 100000.0;

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
        /*cout << "CHANGE" << m_ID << " -> " << m_futID;
        system("PAUSE");*/
        m_work = NO;
        setID(m_futID);
        m_futID = 0;
        m_progress = 0;
    }

    if (m_Hp < 0)
    {
        if (m_ID == 8)
        {
            setID(6);
        }
        else
        {
            setID(1);
        }        
        if (m_work == DIGING)
        {
            time_text.refill(std::to_string(m_progress) + "/" + std::to_string(m_progressMax));
        }
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
    /*cout << m_futID << endl;
    system("PAUSE");*/
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

int Tile::addProgress(float pr)
{
    cout << "ADDPROGRESS" << pr << endl;
    if (m_futID == 0)
    {
        return 0;
    }
    m_progress += pr;
    cout << pr << " " << m_progress << endl;
    return 1;
}

bool Tile::isBuilding()
{
    if (((m_ID >= 17) && (m_ID <= 22)) || (m_ID == 8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Tile::get_damage(float damage)
{
    m_Hp -= damage;
    //cout << "mes degats" << damage << endl;
}