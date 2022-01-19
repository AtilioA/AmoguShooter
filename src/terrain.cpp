#include "../include/terrain.hpp"

// #include <iostream>
// using namespace std;

void Terrain::draw_terrain()
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    glPushMatrix();

    glTranslatef(this->pos.x, -this->pos.y, 0);

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(this->width, 0);
    glVertex2f(this->width, -this->height);
    glVertex2f(0, -this->height);
    glEnd();

    glPopMatrix();
}

Point Terrain::get_pos()
{
    return this->pos;
}

Color Terrain::get_color()
{
    return this->color;
}

GLfloat Terrain::get_width()
{
    return this->width;
}

GLfloat Terrain::get_height()
{
    return this->height;
}

void Terrain::set_color(Color c)
{
    this->color = c;
}
