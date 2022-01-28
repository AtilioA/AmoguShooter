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
    GLint facingDirection;

private:
    void draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw_gunshot(GLfloat x, GLfloat y, Color crewmateUpperBodyColor);

public:
    Gunshot(GLfloat x, GLfloat y, GLfloat deltaX, GLfloat deltaY, GLfloat directionAng, GLint facingDirection)
    {
        gXInit = x;
        gYInit = y;
        gX = x + deltaX;
        gY = y + deltaY;
        gDirectionAng = directionAng;
        gVel = INC_KEYIDLE * 2;
        gRadiusGunshot = 1;
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
