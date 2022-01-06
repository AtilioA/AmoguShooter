#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
// #include "tiro.hpp"

// Dimensions
// #define paddleHeight 80
// #define paddleWidth 10
// #define baseHeight 40
// #define baseWidth 100
// #define radiusWheel 30
#define M_PI 3.14159265358979323846

class Character
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gTheta1;
    GLfloat gTheta2;
    GLfloat gTheta3;
    GLfloat gThetaWheel;
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
        gY = -200;
        gTheta1 = 0;
        gTheta2 = 0;
        gTheta3 = 0;
        gThetaWheel = 0;
    };
    void Draw()
    {
        DrawCharacter(gX, gY, gThetaWheel, gTheta1,
                  gTheta2, gTheta3);
    };

    void RotateArm(GLfloat inc);
    void RotateForearm(GLfloat inc);
    void MoveEmX(GLfloat dx);

    // Tiro *Atira();
    GLfloat ObtemX()
    {
        return gX;
    };

    GLfloat ObtemY()
    {
        return gY;
    };
};

#endif /* CHARACTER_H */
