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
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gVel;
    GLfloat gRadiusGunshot;

private:
    void draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw_gunshot(GLfloat x, GLfloat y);

public:
    Gunshot(GLfloat x, GLfloat y, GLfloat deltaX, GLfloat deltaY, GLfloat directionAng)
    {
        gXInit = x;
        gYInit = y;
        gX = x + deltaX;
        gY = y + deltaY;
        gDirectionAng = directionAng;
        gVel = 2;
        gRadiusGunshot = 1;
    };

    void draw()
    {
        draw_gunshot(gX, gY);
    };

    bool is_inside_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);

    GLfloat get_radius();
    Point get_center();

    void move(GLdouble deltaTime);
    bool is_valid();
};

#endif /* GUNSHOT_H */
