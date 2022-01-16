#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "character.hpp"

class Enemy : public Character
{

public:
    Enemy(Point pos, GLfloat radius, Color color)
    {
        this->set_center(pos);
        this->set_radius(radius);
        this->set_color(color);
        this->set_height(radius * 2);
    };

    virtual void f()
    {
        std::cout << "";
    };

    void draw_enemy();
    void change_position(Point pos);
    void move_enemy(GLfloat dx, GLfloat dy);
};

#endif /* ENEMY_H */
