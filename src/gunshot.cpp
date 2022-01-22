#include "../include/gunshot.hpp"
#include <math.h>
#define MAX_DISTANCE 500

void Gunshot::draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 20)
    {
        glVertex2f(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180));
    }
    glEnd();
}

void Gunshot::draw_gunshot(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, -y, 0);
    draw_circ(radiusGunshot, 1, 1, 1);
    glPopMatrix();
}

void Gunshot::move(GLdouble deltaTime)
{
    this->gX += this->gVel * sin(this->gDirectionAng * M_PI / 180) * 1;
    this->gY += this->gVel * cos(this->gDirectionAng * M_PI / 180) * 1;
}

bool Gunshot::is_valid()
{
    return MAX_DISTANCE > sqrt(pow(this->gX, 2) + pow(this->gY, 2));
}
