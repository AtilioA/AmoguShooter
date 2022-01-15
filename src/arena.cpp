#include <iostream>
#include <stdio.h>
#include <GL/glut.h>

#include "../include/arena.hpp"

using namespace std;

ArenaComponent::ArenaComponent(Point position, float width, float height, Color color)
{
    this->pos = position;
    this->width = width;
    this->height = height;
    this->color = color;
}

void ArenaComponent::draw_arena_component(/*float width, float height, Color color*/)
{
    glColor3f(this->color.r, this->color.g, this->color.b);

    cout << "this->pos.x: " << this->pos.x << " this->pos.y: " << this->pos.y << " this->width: " << this->width << " this->height: " << this->height << /*" this->color.r: " << this->color.r << " this->color.g: " << this->color.g << " this->color.b: " << this->color.b << */ endl;

    glPushMatrix();

    glBegin(GL_POLYGON);
    glVertex2f(this->pos.x, -this->pos.y);
    glVertex2f(this->pos.x + this->width, -this->pos.y);
    glVertex2f(this->pos.x + this->width, -this->pos.y - this->height);
    glVertex2f(this->pos.x, -this->pos.y - this->height);
    glEnd();

    glPopMatrix();
}
