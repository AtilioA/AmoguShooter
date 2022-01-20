#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "character.hpp"

class Player : public Character
{

public:
    Player(Point pos, GLfloat radius, Color color, GLint id)
    {
        this->set_center(pos);
        this->set_radius(radius);
        this->set_color(color);
        this->set_height(radius * 2);
        this->id = id;
    };

    virtual void f()
    {
        std::cout << "";
    };

    void draw_player();
    void change_position(Point pos);
    // void move_player(GLfloat dx, GLfloat dy);

    Point update_player(GLfloat inc, bool w, bool s, bool a, bool d, GLdouble time);
    // Point update_player(bool w, bool s, bool a, bool d, GLdouble time);
};

#endif /* PLAYER_H */
