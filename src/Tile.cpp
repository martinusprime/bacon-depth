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

    resources_id = Random::get_int(0, 5)-4;

    int random = Random::get_int(0, 3);
    m_x = x;
    m_y = y;
    for (int i = 0; i < random; i++)
    {
        cout << "it: " << i << "randomommo :" << random << endl;
        resource1.push_back(Ressource{ app, view, resources_id, resource_number, x, y });
        resource_number++;
    } srand(time(0));

    life_bar = My_Sprite{ app, "resources/life_bar.png", view };
    life_bar_background = My_Sprite{ app, "resources/life_bar_background.png", view };
    life_bar_heart = My_Sprite{ app, "resources/life_bar_heart.png", view };
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
}

int Tile::getId()
{
    return m_ID;
}
void Tile::draw_tile()
{
    if (isBuilding())
    {
        life_bar_background.draw(m_x * tile_size, m_y * tile_size);
        life_bar.draw(m_x * tile_size, m_y * tile_size);
        life_bar_heart.draw(m_x * tile_size, m_y * tile_size);
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
    // m_irradiation doit etre comprise entre 0 et 1  a la fin;

    m_irradiation += ((time / 5.0) + (1 / (m_level + 2))) / 100000.0;

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
        m_futID = 0;
        m_progress = 0;
    }

    if (m_Hp < 0)
    {
        setID(1);
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

void Tile::get_damage(int damage)
{
    m_Hp -= damage;
}