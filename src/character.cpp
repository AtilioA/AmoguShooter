#include <math.h>
#include <GL/glut.h>

#include "../include/character.hpp"

void Character::DrawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);

    glPointSize(6);

    glBegin(GL_POINTS);
    // clang-format off
        for (int i = 0; i < 360; i += 5)
        {
            glVertex2f(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180));
        }
    // clang-format on
    glEnd();
}

// Draw a sequence of points representing the wheel of the character
void Character::DrawBody(GLint width, GLint height, GLfloat R, GLfloat G, GLfloat B)
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

void Character::DrawLeg(GLint width, GLint height, GLfloat R, GLfloat G, GLfloat B /*, GLfloat theta */)
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

void Character::DrawFoot(GLint width, GLint height, GLfloat R, GLfloat G, GLfloat B /*, GLfloat theta */)
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

void Character::DrawArm(GLint width, GLint height, GLfloat R, GLfloat G, GLfloat B /*, GLfloat theta */)
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

void Character::DrawCharacter(GLfloat x, GLfloat y, GLfloat R, GLfloat G, GLfloat B, GLfloat thetaFoot,
                              GLfloat thetaLeg, GLfloat thetaArm)
{
    // Cada perna e pé
    glPushMatrix();
    glTranslatef(x, y, 0);
    Character::DrawFoot(x, y, R, G, B);
    Character::DrawLeg(x, y, R, G, B);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y, 0);
    Character::DrawFoot(x, y, R, G, B);
    Character::DrawLeg(x, y, R, G, B);
    glPopMatrix();

    // Parte superior do personagem
    glPushMatrix();
    Character::DrawBody(x, y, R, G, B);
    glPopMatrix();
    // Ou transladar braço
    Character::DrawArm(x, y, R, G, B);

    // Constrói cabeça acima do tronco/corpo e termina
    Character::DrawHead(radius, R, G, B);
}

void Character::RotateFoot(GLfloat inc)
{
    Character::gThetaFoot += inc;
}

void Character::RotateLeg(GLfloat inc)
{
    Character::gThetaLeg += inc;
}

void Character::RotateArm(GLfloat inc)
{
    Character::gThetaArm += inc;
}

void Character::MoveEmX(GLfloat dx)
{
    // Placeholder
    // GLdouble deltaTime = 1;

    // Character::gX += dx * deltaTime;
    // gThetaWheel -= (180 * dx * deltaTime) / (M_PI * radiusWheel);
}

// Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
}

// Tiro *Character::Shoot()
// {
// }
