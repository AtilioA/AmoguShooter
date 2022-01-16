#include "../include/terrain.hpp"

void Terrain::draw_terrain()
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    // cout << "this->pos.x: " << this->pos.x << " this->pos.y: " << this->pos.y << " this->width: " << this->width << " this->height: " << this->height << /*" this->color.r: " << this->color.r << " this->color.g: " << this->color.g << " this->color.b: " << this->color.b << */ endl;

    glPushMatrix();

    glBegin(GL_POLYGON);
    glVertex2f(this->pos.x, -this->pos.y);
    glVertex2f(this->pos.x + this->width, -this->pos.y);
    glVertex2f(this->pos.x + this->width, -this->pos.y - this->height);
    glVertex2f(this->pos.x, -this->pos.y - this->height);
    glEnd();

    glPopMatrix();
}
