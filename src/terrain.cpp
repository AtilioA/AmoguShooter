#include "../include/terrain.hpp"

// #include <iostream>
// using namespace std;

// Import game to check debug options
#include "../include/game.hpp"
extern Game *game;

void Terrain::draw_terrain()
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    glPushMatrix();

    glTranslatef(this->center.x, -this->center.y, 0);

    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(this->width, 0);
    glVertex2f(this->width, -this->height);
    glVertex2f(0, -this->height);
    glEnd();

    glPopMatrix();
}

Point Terrain::get_center()
{
    return this->center;
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
