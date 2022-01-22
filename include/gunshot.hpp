#ifndef GUNSHOT_H
#define GUNSHOT_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusGunshot 1

class Gunshot
{
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gVel;

private:
    void draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw_gunshot(GLfloat x, GLfloat y);

public:
    Gunshot(GLfloat x, GLfloat y, GLfloat directionAng)
    {
        gXInit = x;
        gYInit = y;
        gX = x;
        gY = y;
        gDirectionAng = directionAng;
        gVel = 2;
    };

    void draw()
    {
        draw_gunshot(gX, gY);
    };

    void move(GLdouble deltaTime);
    bool is_valid();
};

#endif /* GUNSHOT_H */
