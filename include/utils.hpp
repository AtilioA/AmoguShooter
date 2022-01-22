#ifndef UTILS_H
#define UTILS_H

#define M_PI 3.14159265358979323846
#include <GL/glut.h>

typedef struct tDimensions
{
    GLfloat width;
    GLfloat height;
} Dimensions;

typedef struct tPoint
{
    GLfloat x;
    GLfloat y;
} Point;

typedef struct tColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
} Color;

typedef struct tCrewmateColors
{
    tColor upperBody;
    tColor lowerBody;
} CrewmateColors;

CrewmateColors get_player_colors();
CrewmateColors get_random_enemy_colors();
GLfloat smallest_dimension(Dimensions dimensions);

#endif /* UTILS_H */
