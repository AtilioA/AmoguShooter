#include <iostream>
#include <stdio.h>
#include <GL/glut.h>

#include "../include/arena.hpp"

ArenaComponent::ArenaComponent(Point position, float width, float height, Color color)
{
    this->pos = position;
    this->width = width;
    this->height = height;
    this->color = c;

public:
    void draw_arena_component(/*float width, float height, Color color*/)
    {
        glColor3f(this->color.r, this->color.g, this->color.b);

        glBegin(GL_QUADS);
        // clang-format off
            glVertex2f(0, 0);
            glVertex2f(this->width, 0);
            glVertex2f(this->width, this->height);
            glVertex2f(0, this->height);
        // clang-format on
        glEnd();
    }
}

using namespace std;
