#ifndef TIRO_H
#define TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusTiro 5

class Tiro
{
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gDirectionAng;
    GLfloat gVel;

private:
    void DrawCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawTiro(GLfloat x, GLfloat y);

public:
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng)
    {
        gXInit = x;
        gYInit = y;
        gX = x;
        gY = y;
        gDirectionAng = directionAng;
        gVel = 0.1;
    };
    void Draw()
    {
        DrawTiro(gX, gY);
    };
    void Move();
    bool Valido();
    void GetPos(GLfloat &xOut, GLfloat &yOut)
    {
        xOut = gX;
        yOut = gY;
    };
};

#endif /* TIRO_H */
