#ifndef ARENA_H_
#define ARENA_H_

#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct tPoint
{
    float x;
    float y;
} Point;

typedef struct tColor
{
    float r;
    float g;
    float b;
} Color;

class ArenaComponent
{
    Point pos;
    Color color;
    float width;
    float height;

public:
    ArenaComponent(Point position, float width, float height, Color color);
    void draw_arena_component(/*float width, float height, Color color*/);

    void set_vertex(Point p);
    Point get_pos();
    Color get_color();
    float get_width();
    float get_height();
};

#endif /* ARENA_H_ */
