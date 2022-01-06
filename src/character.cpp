#include "character.hpp"
#include <math.h>


void Character::DrawHead(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-width / 2, 0);
        glVertex2f(width / 2, 0);
        glVertex2f(width / 2, height);
        glVertex2f(-width / 2, height);
    // clang-format on
    glEnd();
}

// Draw a sequence of points representing the wheel of the character
void Character::DrawBody(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glPointSize(6);
    glBegin(GL_POINTS);
    // clang-format off
        for (int i = 0; i < 360; i += 10)
        {
            glVertex2f(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180));
        }
    // clang-format on
    glEnd();
}

void Character::DrawLeg(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    // Translate to the given position
    glTranslatef(x, y, 0);

    // Rotate the wheel with the given angle
    glRotatef(thetaWheel, 0, 0, 1);

    DrawCirc(radiusWheel, R, G, B);

    glPopMatrix();
}

void Character::DrawFoot(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    // Translate to the given position
    glTranslatef(x, y, 0);

    // Rotate the wheel with the given angle
    glRotatef(thetaWheel, 0, 0, 1);

    DrawCirc(radiusWheel, R, G, B);

    glPopMatrix();
}

void Character::DrawArm(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    // Save coordinate system
    glPushMatrix();

    // Shift coordinate system to draw on top of base
    glTranslatef(0, baseHeight, 0);
    // Rotate coordinate system to draw paddle
    glRotatef(theta1, 0, 0, 1);
    // Draw paddle with blue color
    Character::DrawRect(paddleHeight, paddleWidth, 0, 0, 1);

    // Draw another paddle on top of the first one
    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta2, 0, 0, 1);
    Character::DrawRect(paddleHeight, paddleWidth, 1, 1, 0);

    // Third and last paddle
    glTranslatef(0, paddleHeight, 0);
    glRotatef(theta3, 0, 0, 1);
    Character::DrawRect(paddleHeight, paddleWidth, 0, 1, 0);

    // Return to original coordinate system
    glPopMatrix();
}

void Character::DrawCharacter(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    Character::DrawRect(baseHeight, baseWidth, 1, 0, 0);
    Character::DrawArm(0, baseHeight, theta1, theta2, theta3);
    Character::DrawWheel(-baseWidth / 2, 0, thetaWheel, 0, 0, 1);
    Character::DrawWheel(baseWidth / 2, 0, thetaWheel, 0, 0, 1);
    glPopMatrix();
}

void Character::RotateArm(GLfloat inc)
{
    Character::gTheta1 += inc;
}

void Character::RotateForearm(GLfloat inc)
{
    Character::gTheta2 += inc;
}

void Character::MoveEmX(GLfloat dx)
{
    // Placeholder
    GLdouble deltaTime = 1;

    Character::gX += dx * deltaTime;
    gThetaWheel -= (180 * dx * deltaTime) / (M_PI * radiusWheel);
}

// Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
}

// Tiro *Character::Atira()
// {
// }
