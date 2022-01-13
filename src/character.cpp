#include <math.h>
#include <GL/glut.h>

#include "../include/character.hpp"

void Character::draw_head(GLint radius)
{
    glColor3f(color.r, color.g, color.b);

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
void Character::draw_body()
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 2, 0);
        glVertex2f(this->radius / 2, 0);
        glVertex2f(this->radius / 2, height);
        glVertex2f(-this->radius / 2, height);
    // clang-format on
    glEnd();
}

void Character::draw_leg(/*, GLfloat theta */)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 2, 0);
        glVertex2f(this->radius / 2, 0);
        glVertex2f(this->radius / 2, height);
        glVertex2f(-this->radius / 2, height);
    // clang-format on
    glEnd();
}

void Character::draw_foot(/*, GLfloat theta */)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 2, 0);
        glVertex2f(this->radius / 2, 0);
        glVertex2f(this->radius / 2, height);
        glVertex2f(-this->radius / 2, height);
    // clang-format on
    glEnd();
}

void Character::draw_arm(/*, GLfloat theta */)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 2, 0);
        glVertex2f(this->radius / 2, 0);
        glVertex2f(this->radius / 2, height);
        glVertex2f(-this->radius / 2, height);
    // clang-format on
    glEnd();
}

void Character::draw_character(/*, GLfloat thetaFoot,
                              GLfloat thetaLeg, GLfloat thetaArm*/
)
{
    // Cada perna e pé
    glPushMatrix();
    glTranslatef(this->center.x, this->center.y, 0);

    Character::draw_foot();
    Character::draw_leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->center.x, this->center.y, 0);
    Character::draw_foot();
    Character::draw_leg();
    glPopMatrix();

    // Parte superior do personagem
    glPushMatrix();
    Character::draw_body();
    glPopMatrix();
    // Ou transladar braço
    Character::draw_arm();

    // Constrói cabeça acima do tronco/this->radius, height);
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
void RotatePoint(Point position, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
}

// Tiro *Character::Shoot()
// {
// }
