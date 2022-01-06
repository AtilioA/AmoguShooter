#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/arena.hpp"

// Dimensions
// #define paddleHeight 80
// #define paddleWidth 10
// #define baseHeight 40
// #define baseWidth 100
// #define radiusWheel 30
#define M_PI 3.14159265358979323846

class Character
{
    Point center;
    Color color;
    float radius;
    GLfloat gX;
    GLfloat gTheta1;
    GLfloat direction;
    GLfloat speed;

private:
    void DrawHead(GLint height, GLint width,
                  GLfloat R, GLfloat G, GLfloat B);
    void DrawBody(GLint radius, GLfloat R,
                  GLfloat G, GLfloat B);
    void DrawLeg(GLfloat x, GLfloat y, GLfloat thetaWheel,
                 GLfloat R, GLfloat G, GLfloat B);
    void DrawFoot(GLfloat x, GLfloat y, GLfloat thetaWheel,
                  GLfloat R, GLfloat G, GLfloat B);
    void DrawArm(GLfloat x, GLfloat y, GLfloat theta1,
                 GLfloat theta2, GLfloat theta3);
    void DrawCharacter(GLfloat x, GLfloat y, GLfloat thetaWheel,
                       GLfloat theta1, GLfloat theta2, GLfloat theta3);

public:
    Character()
    {
        gX = 0;
        gTheta1 = 0;
    };
    // void Draw()
    // {
    //   gTheta2, gTheta3);
    // };

    void RotateArm(GLfloat inc);
    void RotateForearm(GLfloat inc);
    void MoveX(GLfloat dx);

    // Tiro *Atira();
    
    GLfloat GetX()
    {
        return gX;
    };

    GLfloat GetY(){};
};

#endif /* CHARACTER_H */
