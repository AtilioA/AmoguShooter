#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "character.hpp"

class Player : public Character
{

public:
     using Character::Character;

    virtual void f()
    {
        std::cout << "";
    };
};

#endif /* PLAYER_H */
