#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "character.hpp"

class Enemy : public Character
{

public:
    using Character::Character;

    virtual void f()
    {
        std::cout << "";
    };
};

#endif /* ENEMY_H */
