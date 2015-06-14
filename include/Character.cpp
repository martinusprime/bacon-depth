#include "Character.h"
#include "Random.h"

Character::Character(RenderWindow *app, View *view, int id)
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


Character::~Character()
{
}


void Character::update(Tile map[][10], float timeElapsed)
{
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

            if (walking_x  > tile_size)
            {
                direction = LEFT;
                walking_x = tile_size;
            }

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

    if (status == MOVING)
    {
        if ((tile_x == m_goalX) && (tile_y == m_goalY))
        {
            status = IDLE;
        }
        else
        {
            if (pathFinding(map) == 0)
            {
                status == IDLE;
            }
            else
            {
                m_moving += timeElapsed;
                cout << " -->" << m_moving << endl;
            }
            if (m_moving >= 1)
            {
                (*this).setPosition(move_x, move_y);
            }
        }
    }
}

bool Character::alive()
{
    return is_alive;
}

void Character::draw()
{
    sprite.draw(tile_x * tile_size + walking_x, tile_y * tile_size + tile_size - sprite.get_h());
    life_bar_background.draw(tile_x * tile_size + walking_x, tile_y * tile_size + (tile_size - sprite.get_h()) - 50);
    life_bar.draw(tile_x * tile_size + walking_x, tile_y * tile_size + (tile_size - sprite.get_h()) - 50);
    life_bar_heart.draw(tile_x * tile_size + walking_x, tile_y * tile_size + (tile_size - sprite.get_h()) - 50);
}

void Character::newGoal(int x, int y)
{
    status = MOVING;

    m_goalX = x;
    m_goalY = y;
}

int Character::pathFinding(Tile map[][10])
{
    if (map[m_goalX][m_goalY].isWalkable() == 0)
    {
        cout << "ERROR CASE ISNT WALKABLE" << endl;
        return 0;
    }
    //cout << "ENTRER PATHFINDING" << endl;
    int contin = 1;
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            map[i][j].setNode(0);
        }
    }

    int x = tile_x;
    int y = tile_y;
    map[x][y].setNode(1);
    int node = 1;
    int compteur = 0;
    for (size_t i = 0; i < 50; i++)
    {
        compteur++;
        node++;
        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                if ((map[i][j].getNode() == (node - 1)) && (map[i][j].isWalkable()))
                {
                    if (i > 0)
                    {
                        if (map[i - 1][j].getNode() == 0)
                        {
                            map[i - 1][j].setNode(node);
                            if ((i == m_goalY) && (j == m_goalX))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                    if (i < 9)
                    {

                        if ((map[i + 1][j].getNode() == 0) && (map[i + 1][j].getId() == 2))/////////VERIFICATION OF THE ELEVATOR
                        {
                            map[i + 1][j].setNode(node);
                            if ((i == m_goalY) && (j == m_goalX))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                    if (j > 0)
                    {
                        if (map[i][j - 1].getNode() == 0)
                        {
                            map[i][j - 1].setNode(node);
                            if ((i == m_goalY) && (j == m_goalX))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                    if (j < 4)
                    {
                        if (map[i][j + 1].getNode() == 0)
                        {
                            map[i][j + 1].setNode(node);
                            if ((i == m_goalY) && (j == m_goalX))
                            {
                                contin = 0;
                                //cout << "FIN";
                            }
                        }
                    }
                }
            }
            //cout << endl;
        }
        //cout << endl << node << endl;
    }
    node--;
    int meilleur = node;
    coord node1;
    node1.x = m_goalX;
    node1.y = m_goalY;
    coord node2;
    contin = 1;
    compteur = 0;

    while (compteur < 1000)
    {
        //cout << "debug1" << endl;
        compteur++;
        if (node1.y > 1)
        {
            /*cout << "Node" << node1.x << node1.y << endl;
            system("PAUSE");*/
            if ((map[node1.x][node1.y - 1].getNode() < meilleur) && (map[node1.x][node1.y - 1].getNode() != 0))
            {
                //cout << "BINGO" << endl;
                meilleur = map[node1.x][node1.y - 1].getNode();
                node2.x = node1.x;
                node2.y = node1.y - 1;
            }
        }
        if (node1.y < 9)
        {
            if ((map[node1.x][node1.y + 1].getNode() < meilleur) && (map[node1.x][node1.y + 1].getNode() != 0))
            {
                //cout << "BINGO" << endl;
                meilleur = map[node1.x][node1.y + 1].getNode();
                node2.x = node1.x;
                node2.y = node1.y + 1;
            }
        }
        if (node1.x > 1)
        {
            if ((map[node1.x - 1][node1.y].getNode() < meilleur) && (map[node1.x - 1][node1.y].getNode() != 0))
            {
                //cout << "BINGO" << endl;
                meilleur = map[node1.x - 1][node1.y].getNode();
                node2.x = node1.x - 1;
                node2.y = node1.y;
            }
        }
        if (node1.x < 4)
        {
            if ((map[node1.x + 1][node1.y].getNode() < meilleur) && (map[node1.x + 1][node1.y].getNode() != 0))
            {
                //cout << "BINGO" << endl;
                meilleur = map[node1.x + 1][node1.y].getNode();
                node2.x = node1.x + 1;
                node2.y = node1.y;
            }
        }
        //cout << endl << "test:" << node2.x << m_goal << endl;
        if ((node2.x == tile_x) && (node2.y == tile_y))
        {

            //cout << "TROUVE:!!!!!" << endl;
            //////////////APPEL FONCTION DEPLACEMENT (node1.y, node1.x)
            (*this).moving(node1.x, node1.y);
            //cout << "NODE:" << node1.x << node1.y << endl;
            return 1;
        }
        else
        {
            node1 = node2;
            //cout << endl << "NODE:"<< node1.x << node1.y << endl;
        }
        node == meilleur;
    }
    return 0;
}

void Character::setPosition(int x, int y)
{
    tile_x = x;
    tile_y = y;
}

void Character::moving(int x, int y)
{
    if ((x != move_x) || (y != move_y))
    {
        //cout << "REINI" << endl;
        move_x = x;
        move_y = y;
        m_moving = 0;
    }
}

int Character::getX()
{
    return tile_x;
}

int Character::getY()
{
    return tile_y;
}

int Character::isIdle()
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

int Character::isOnPos(int x, int y)
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

void Character::stop()
{
    status = IDLE;
    m_goalX = 0;
    m_goalY = 0;
    m_moving = 0;
    move_x = 0;
    move_y = 0;
}
