#include <math.h>
#include <GL/glut.h>

#include "../include/character.hpp"

void Character::draw_head()
{
    glColor3f(172.0 / 255, 66.0 / 255, 85.0 / 255); // rgb(172,66,85)

    glPointSize(4);

    glBegin(GL_POINTS);
    // clang-format off
        for (int i = 0; i < 360; i += 90)
        {
            glVertex2f(this->radius / 2 * cos(i * M_PI / 180), this->radius / 2 * sin(i * M_PI / 180));
        }
    // clang-format on
    glEnd();
}

// Draw a sequence of points representing the wheel of the character
void Character::draw_body()
{
    glColor3f(56.0 / 255, 76.0 / 255, 92.0 / 255); // rgb(56,76,92)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 4, 0);
        glVertex2f(this->radius / 4, 0);
        glVertex2f(this->radius / 4, this->height / 1.5);
        glVertex2f(-this->radius / 4, this->height / 1.5);
    // clang-format on
    glEnd();
}

void Character::draw_leg(/*, GLfloat theta */)
{
    glColor3f(228.0 / 255, 170.0 / 255, 141.0 / 255); // rgb(228, 170, 141)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 4, 0);
        glVertex2f(this->radius / 4, 0);
        glVertex2f(this->radius / 4, this->height / 2);
        glVertex2f(-this->radius / 4, this->height / 2);
    // clang-format on
    glEnd();
}

void Character::draw_foot(/*, GLfloat theta */)
{
    glColor3f(121.0 / 255, 200.0 / 255, 226.0 / 255); // rgb(121, 200, 255)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 4, 0);
        glVertex2f(this->radius / 4, 0);
        glVertex2f(this->radius / 4, this->height / 2);
        glVertex2f(-this->radius / 4, this->height / 2);
    // clang-format on
    glEnd();
}

void Character::draw_arm(/*, GLfloat theta */)
{
    glColor3f(151.0 / 255, 220.0 / 255, 226.0 / 255); // rgb(151, 220, 255)

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 6, 0);
        glVertex2f(this->radius / 6, 0);
        glVertex2f(this->radius / 6, this->height / 2);
        glVertex2f(-this->radius / 6, this->height / 2);
    // clang-format on
    glEnd();
}

void Character::draw_character(/*, GLfloat thetaFoot,
                              GLfloat thetaLeg, GLfloat thetaArm*/
)
{
    glPushMatrix();

    // glTranslatef(0, -this->center.y, 0);
    // glRotatef(180, 0, 0, 1);

    // Cada perna e pé
    glPushMatrix();
    glTranslatef(this->center.x + 2, this->center.y - this->radius, 0);
    glRotatef(-170, 0, 0, 1);
    Character::draw_foot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->center.x, this->center.y - this->radius, 0);
    glTranslatef(0, this->height / 2, 0);
    glRotatef(-160, 0, 0, 1);
    Character::draw_leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->center.x - 2, this->center.y - this->radius, 0);
    glRotatef(170, 0, 0, 1);
    Character::draw_foot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->center.x, this->center.y - this->radius, 0);
    glTranslatef(0, this->height / 2, 0);
    glRotatef(160, 0, 0, 1);
    Character::draw_leg();
    glPopMatrix();

    // Parte superior do personagem
    glPushMatrix();
    glTranslatef(this->center.x, this->center.y - this->radius, 0);
    glTranslatef(0, this->height / 2, 0);
    glTranslatef(0, this->height / 2, 0);
    glRotatef(-90, 0, 0, 1);
    Character::draw_arm();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->center.x, this->center.y - this->radius, 0);
    glTranslatef(0, this->height / 2, 0);
    Character::draw_body();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(this->center.x, this->center.y, 0);
    glTranslatef(0, this->height, 0);
    Character::draw_head();
    glPopMatrix();

    // glEnd();

    glPopMatrix();

    // Constrói cabeça acima do tronco/this->radius, this->height / 2);
}

void Character::rotate_foot(GLfloat inc)
{
    Character::gThetaFoot += inc;
}

void Character::rotate_leg(GLfloat inc)
{
    Character::gThetaLeg += inc;
}

void Character::rotate_arm(GLfloat inc)
{
    Character::gThetaArm += inc;
}

void Character::move_character(GLfloat dx, GLfloat deltaTime)
{
    // Placeholder
    // GLdouble deltaTime = 1;

    Character::center.x += dx * deltaTime;
    // gThetaWheel -= (180 * dx * deltaTime) / (M_PI * radiusWheel);
}

// Funcao auxiliar de rotacao
void RotatePoint(Point position, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
}

// Tiro *Character::Shoot()
// {
// }
