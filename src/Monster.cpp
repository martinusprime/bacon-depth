#include "Monster.h"
#include "Random.h"

Monster::Monster(RenderWindow *app, View *view, int id)
    : sprite(app, "resources/perso", view, 10)
    , life_bar(app, "resources/life_bar.png", view)
    , life_bar_background(app, "resources/life_bar_background.png", view)
    , life_bar_heart(app, "resources/life_bar_heart.png", view)
    , m_id(id)
    , is_alive(true)
{
    srand(time(0));
    m_goalX = 0;
    m_goalY = 0;
    status = IDLE;

    m_view1 = view;
    m_app = app;
    life = 100;
    tile_x = 0;
    tile_y = 0;
    move_x = 0;
    move_y = 0;
    tile_size = 384;
    //set initial position
    walking_x = m_id * 10;

    if (walking_x < 0)
    {
        direction = RIGHT;
        walking_x = 0;
    }

    if (walking_x + sprite.get_w() > tile_size)
    {
        direction = LEFT;
        walking_x = tile_size - sprite.get_w();
    }

    if (Random::get_int(0, 10) > 5)
    {
        direction = RIGHT;
    }
    else direction = LEFT;

}


Monster::~Monster()
{
}


void Monster::update(Tile my_map[][5], float timeElapsed)
{
    //cout << "JOUEUR" << status << " " << tile_x << ":" << tile_y << " " << move_x << ":" << move_y << " " << m_goalX << ":" << m_goalY << endl;
    //system("PAUSE");


    float new_life = life / 100.0f;
    life_bar.scale(new_life, 1.0f, false);


    if (status == IDLE)
    {
        if (random_clock.getElapsedTime().asSeconds() > 5)
        {
            random_clock.restart();


            int random = rand() % 10 + 0;
            if (random > 7)
            {
                if (direction == RIGHT)
                {
                    direction = LEFT;
                }
                else if (direction == LEFT)
                {
                    direction = RIGHT;
                }
            }
        }


        if (render_clock.getElapsedTime().asSeconds() > 0.1)
        {
            render_clock.restart();


            if (direction == RIGHT)
            {
                walking_x += 2;
            }
            else if (direction == LEFT)
            {
                walking_x -= 2;
            }

            if (walking_x - sprite.get_w() < 0)
            {
                direction = RIGHT;
                walking_x = 0 + sprite.get_w();
            }

            if (walking_x > tile_size)
            {
                direction = LEFT;
                walking_x = tile_size;
            }

        }
    }

    else if (status == DIGING)
    {
        if (my_map[m_digY][m_digX].addProgress(timeElapsed) == 0)
        {
            status == IDLE;
            m_digY = 0;
            m_digX = 0;
        }
    }
    else if (status == BUILDING)
    {
        if (my_map[m_buildY][m_buildX].addProgress(timeElapsed) == 0)
        {
            status == IDLE;
            m_buildY = 0;
            m_buildX = 0;
        }
    }

    if (life <= 0)
    {
        is_alive = false;
    }

    if (direction == RIGHT)
    {
        life_bar_background.flip_x(false);
        life_bar.flip_x(false);
        life_bar_heart.flip_x(false);
        sprite.flip_x(false);
    }
    else if (direction == LEFT)
    {
        life_bar_background.flip_x(true);
        life_bar.flip_x(true);
        life_bar_heart.flip_x(true);
        sprite.flip_x(true);
    }

    if ((tile_x == m_goalX) && (tile_y == m_goalY))
    {
        if (status == MOVING)
        {
            status = IDLE;
        }
    }
    else
    {
        status = MOVING;
        pathFinding(my_map);
        m_moving += timeElapsed;
        cout << " -->" << m_moving << endl;
        //}
        if (m_moving >= 2000)
        {
            (*this).setPosition(move_x, move_y);
        }
    }
}

void Monster::setPosition(int x, int y)
{
    tile_x = x;
    tile_y = y;

    m_moving = 0;
    status = IDLE;
}

void Monster::moving(int x, int y)
{
    //cout << "IS MOVING to :" << x << " " << y << endl;
    //system("PAUSE");
    //if ((x != move_x) || (y != move_y) || (status != MOVING))
    //{
    status = MOVING;
    move_x = x;
    move_y = y;
    //m_moving = 0;
    //}
}

bool Monster::alive()
{
    return is_alive;
}

void Monster::draw()
{
    sprite.draw(tile_x * tile_size + walking_x, tile_y * tile_size + tile_size - sprite.get_h());
    life_bar_background.draw(tile_x * tile_size + walking_x, tile_y * tile_size + (tile_size - sprite.get_h()) - 50);
    life_bar.draw(tile_x * tile_size + walking_x, tile_y * tile_size + (tile_size - sprite.get_h()) - 50);
    life_bar_heart.draw(tile_x * tile_size + walking_x, tile_y * tile_size + (tile_size - sprite.get_h()) - 50);
}

void Monster::newGoal(int x, int y)
{
    status = MOVING;

    m_goalX = x;
    m_goalY = y;
}

int Monster::pathFinding(Tile my_map[][5])
{
    if (my_map[m_goalY][m_goalX].isWalkable() == 0)
    {
        std::cout << "ERROR CASE ISNT WALKABLE" << endl;
        return 0;
    }
    //cout << "ENTRER PATHFINDING" << endl;
    int contin = 1;
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            my_map[i][j].setNode(0);
        }
    }
    //std::cout << "Start case:" << tile_x << tile_y << endl;
    //std::cout << "Goal case:" << m_goalX << m_goalY << endl;
    int y = tile_y;
    int x = tile_x;
    my_map[y][x].setNode(1);
    int node = 1;
    int compteur = 0;
    for (size_t t = 0; t < 50; t++)
    {
        node++;
        //std::cout << endl << "node:" << node << endl;
        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                //std::cout << my_map[i][j].getNode() << " ";
                if ((my_map[i][j].getNode() == (node - 1)) && (my_map[i][j].isWalkable()))
                {
                    //std::cout << endl << "IN " << i << j << endl;
                    if (i > 0)
                    {
                        //std::cout << "Haut" << endl;
                        if ((my_map[i - 1][j].getNode() == 0) && (my_map[i - 1][j].isWalkable())) //&& ((my_map[i - 1][j].getNode() == 8) || (my_map[i - 1][j].getNode() == 2)))*/
                        {
                            my_map[i - 1][j].setNode(node);
                            if ((i == m_goalY) && (j == m_goalX))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                    if (i < 9)
                    {
                        if ((my_map[i + 1][j].getNode() == 0) && (my_map[i + 1][j].isWalkable()))// && ((my_map[i][j].getNode() == 8) || (my_map[i][j].getNode() == 2)))
                        {
                            //std::cout << "BAS" << endl;
                            my_map[i + 1][j].setNode(node);
                            if (((i == m_goalY) && (j == m_goalX)) && (my_map[i + 1][j].isWalkable()))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                    if (j > 0)
                    {
                        //std::cout << "Gauche" << endl;
                        if ((my_map[i][j - 1].getNode() == 0) && (my_map[i][j - 1].isWalkable()))
                        {
                            my_map[i][j - 1].setNode(node);
                            if (((i == m_goalY) && (j == m_goalX)) && (my_map[i][j - 1].isWalkable()))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                    if (j < 4)
                    {
                        //std::cout << "Droite" << endl;
                        if ((my_map[i][j + 1].getNode() == 0) && (my_map[i][j + 1].isWalkable()))
                        {
                            my_map[i][j + 1].setNode(node);
                            if (((i == m_goalY) && (j == m_goalX)) && (my_map[i][j + 1].isWalkable()))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                }
            }
            //std :: cout << endl;
        }
        //std::system("PAUSE");
    }
    node = my_map[m_goalY][m_goalX].getNode();
    //cout << "Start:" << node << endl;
    //system("PAUSE");
    int meilleur = node;

    coord node1;
    node1.x = m_goalX;
    node1.y = m_goalY;

    //std::cout << "Node1 " << node << "  " << m_goalY;
    //std::system("PAUSE");
    coord node2;
    node2.x = m_goalX;
    node2.y = m_goalY;
    contin = 1;
    compteur = 0;

    for (compteur = 0; compteur < 1000; compteur++)
    {
        //cout << "debug1" << endl;
        //compteur++;
        if (node1.y > 0)
        {
            //std::cout << "Node2 " << my_map[node1.y - 1][node1.x].getNode() << " " << meilleur << endl;
            //std::system("PAUSE");
            if ((my_map[node1.y - 1][node1.x].getNode() <= meilleur) && (my_map[node1.y - 1][node1.x].getNode() != 0))
            {
                //std::cout << "BINGO" << node1.x << " " << node1.y - 1 << endl;
                meilleur = my_map[node1.y - 1][node1.x].getNode();
                node2.x = node1.x;
                node2.y = node1.y - 1;
            }
        }
        if (node1.y < 9)
        {
            //std::cout << "Node3 " << my_map[node1.y + 1][node1.x].getNode() << " " << meilleur << endl;
            //std::system("PAUSE");
            if ((my_map[node1.y + 1][node1.x].getNode() <= meilleur) && (my_map[node1.y + 1][node1.x].getNode() != 0))
            {
                //std::cout << "BINGO" << node1.x << " " << node1.y + 1 << endl;
                meilleur = my_map[node1.y + 1][node1.x].getNode();
                node2.x = node1.x;
                node2.y = node1.y + 1;
            }
        }
        if (node1.x > 0)
        {
            //std::cout << "Node4 " << my_map[node1.y][node1.x - 1].getNode() << " " << meilleur << endl;
            //std::system("PAUSE");
            if ((my_map[node1.y][node1.x - 1].getNode() <= meilleur) && (my_map[node1.y][node1.x - 1].getNode() != 0))
            {
                //std::cout << "BINGO" << node1.x - 1 << " " << node1.y << endl;
                meilleur = my_map[node1.y][node1.x - 1].getNode();
                node2.x = node1.x - 1;
                node2.y = node1.y;
            }
        }
        if (node1.x < 4)
        {
            //std::cout << "Node5 " << my_map[node1.y][node1.x + 1].getNode() << " " << meilleur << endl;
            //std::system("PAUSE");
            if ((my_map[node1.y][node1.x + 1].getNode() <= meilleur) && (my_map[node1.y][node1.x + 1].getNode() != 0))
            {
                //std::cout << "BINGO" << node1.x + 1 << " " << node1.y << endl;
                meilleur = my_map[node1.y][node1.x + 1].getNode();
                node2.x = node1.x + 1;
                node2.y = node1.y;
            }
        }
        //cout << endl << "test:" << node2.x << m_goal << endl;
        //if ((((node1.x) - (tile_x) == 1) || ((node1.x) - (tile_x) == -1)) && (((node1.y) - (tile_y == 1)) || ((node1.y) - (tile_y) == -1)))
        if ((node2.x == tile_x) && (node2.y == tile_y))
        {

            //cout << "TROUVE:!!!!!" << endl;
            //////////////APPEL FONCTION DEPLACEMENT (node1.y, node1.x)
            //cout << "NODE:" << node1.x << node1.y << endl;
            //system("PAUSE");
            (*this).moving(node1.x, node1.y);

            return 1;
        }
        else
        {
            node1 = node2;
            //std::cout << "Transfert" << node2.x << " " << node2.y;
            //cout << endl << "NODE:"<< node1.x << node1.y << endl;
        }
        node = meilleur;
    }
    return 0;
}
int Monster::getX()
{
    return tile_x;
}

int Monster::getY()
{
    return tile_y;
}

int Monster::isIdle()
{
    if (status == IDLE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Monster::isOnPos(int x, int y)
{
    if ((tile_x == x) && (tile_y == y))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Monster::stop()
{
    status = IDLE;
    m_goalX = 0;
    m_goalY = 0;
    m_moving = 0;
    move_x = 0;
    move_y = 0;
}

void Monster::dig(int x, int y)
{
    status = DIGING;
    m_digX = x;
    m_digY = y;
}

void Monster::build(int x, int y)
{
    status = BUILDING;
    m_buildX = x;
    m_buildY = y;
}