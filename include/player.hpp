#ifndef PLAYER_H
#define PLAYER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/character.hpp"

class Player : public Character
{

public:
    Player(Point pos, float radius, Color color)
    {
        this->set_center(pos);
        this->set_radius(radius);
        this->set_color(color);
        this->set_height(radius * 2);
    };

    virtual void f()
    {
        cout << "";
    };

    void draw_player();
    void change_position(Point pos);
    // void move_player(float dx, float dy);

    // Point update_player(bool w, bool s, bool a, bool d, GLdouble time);
};

#endif /* PLAYER_H */
