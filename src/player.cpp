#include <iostream>
#include <stdio.h>
#include "../include/player.hpp"

using namespace std;

Point Player::update_player(GLfloat inc, bool w, bool s, bool a, bool d, GLdouble time)
{
    float dx = 0, dy = 0;
    // float velocidadeLutador = 0.1 * time;

    if (w)
    {
        this->center.y -= inc;
    }
    if (a)
    {
        this->center.x -= inc;
    }
    if (s)
    {
        this->center.y += inc;
    }
    if (d)
    {
        this->center.x += inc;
    }

    // Point p = {dx, dy};
    // return p;
}
