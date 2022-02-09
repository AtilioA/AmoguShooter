#ifndef GUNSHOT_H
#define GUNSHOT_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../include/utils.hpp"
#include "../include/character.hpp"
#include "../include/terrain.hpp"

class Character;
class Gunshot
{
    GLint shooterID;
    GLdouble gXInit;
    GLdouble gYInit;
    GLdouble gX;
    GLdouble gY;
    GLfloat gDirectionAng;
    GLdouble gVel;
    GLdouble gRadiusGunshot;
    GLint facingDirection;
    Color color;

private:
    void draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw_bullet(GLdouble x, GLdouble y);

public:
    Gunshot(GLint shooterID, GLdouble x, GLdouble y, GLdouble deltaX, GLdouble deltaY, GLdouble charSpeed, GLdouble charRadius, GLfloat directionAng, GLint facingDirection, Color crewmateUpperBody)
    {
        this->shooterID = shooterID;
        this->gXInit = x;
        this->gYInit = y;
        this->gX = x + deltaX;
        this->gY = y + deltaY;
        this->gDirectionAng = directionAng;
        this->gVel = charSpeed * 2;
        this->gRadiusGunshot = charRadius / 4;
        this->facingDirection = facingDirection;
        this->color = crewmateUpperBody;
    };

    void draw_gunshot();
    void move_gunshot(GLdouble frameTime);

    bool is_inside_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);

    GLint get_shooter_id();

    GLfloat get_radius();
    Point get_center();
};

#endif /* GUNSHOT_H */
