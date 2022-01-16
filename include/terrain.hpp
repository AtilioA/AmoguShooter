#ifndef TERRAIN_H
#define TERRAIN_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "utils.hpp"

class Terrain
{
private:
    Point pos;
    Color color;
    GLfloat width;
    GLfloat height;

public:
    Terrain(Point position, GLfloat width, GLfloat height, Color color)
    {
        this->pos = position;
        this->width = width;
        this->height = height;
        this->color = color;
    }

    void draw_terrain();

    void set_vertex(Point p);
    Point get_pos();
    Color get_color();
    GLfloat get_width();
    GLfloat get_height();
};

#endif /* TERRAIN_H */
