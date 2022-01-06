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

class Arena
{
    Point pos;
    Color color;
    float width;
    float height;

public:
    Arena(float x, float y, float width, float height, Color c);
    void draw_arena(float width, float height, Color c);

    void set_vertex(Point p);
    Point get_pos();
    Color get_color();
    float get_width();
    float get_height();
};

#endif /* ARENA_H_ */
