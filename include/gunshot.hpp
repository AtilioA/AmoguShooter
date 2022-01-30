#ifndef GUNSHOT_H
#define GUNSHOT_H

#define MAX_DISTANCE 500

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../include/utils.hpp"
#include "../include/character.hpp"
#include "../include/terrain.hpp"

class Character;
class Gunshot
{
    GLdouble gXInit;
    GLdouble gYInit;
    GLdouble gX;
    GLdouble gY;
    GLfloat gDirectionAng;
    GLdouble gVel;
    GLdouble gRadiusGunshot;
    GLint facingDirection;

private:
    void draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw_gunshot(GLdouble x, GLdouble y, Color crewmateUpperBodyColor);

public:
    Gunshot(GLdouble x, GLdouble y, GLdouble deltaX, GLdouble deltaY, GLdouble charSpeed, GLdouble charRadius, GLfloat directionAng, GLint facingDirection)
    {
        gXInit = x;
        gYInit = y;
        gX = x + deltaX;
        gY = y + deltaY;
        gDirectionAng = directionAng;
        gVel = charSpeed * 2;
        gRadiusGunshot = charRadius / 4;
        facingDirection = facingDirection;
    };

    void draw(Color crewmateUpperBodyColor)
    {
        draw_gunshot(this->gX, this->gY, crewmateUpperBodyColor);
    };

    bool is_inside_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);

    GLfloat get_radius();
    Point get_center();

    void move(GLdouble frameTime);
    bool is_valid();
};

#endif /* GUNSHOT_H */
