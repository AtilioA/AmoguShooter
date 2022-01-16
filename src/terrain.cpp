#include "../include/terrain.hpp"

void Terrain::draw_terrain()
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glVertex2f(this->pos.x, -this->pos.y);
    glVertex2f(this->pos.x + this->width, -this->pos.y);
    glVertex2f(this->pos.x + this->width, -this->pos.y - this->height);
    glVertex2f(this->pos.x, -this->pos.y - this->height);
    glEnd();

    glPopMatrix();
}
