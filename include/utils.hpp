// Library for utilitary functions and structs

#ifndef UTILS_H
#define UTILS_H

#define M_PI 3.14159265358979323846

#include <GL/glut.h>

// Stores the size of a 2D window
typedef struct tDimensions
{
    GLfloat width;
    GLfloat height;
} Dimensions;

// Stores the coordinates of a point
typedef struct tPoint
{
    GLfloat x;
    GLfloat y;
} Point;

// Stores the RGB values of a color
typedef struct tColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
} Color;

// Stores the color for a Character (crewmate): upper body and lower body.
typedef struct tCrewmateColors
{
    tColor upperBody;
    tColor lowerBody;
} CrewmateColors;

// Picks the player color, which is RED in this case
CrewmateColors get_player_colors();

// Picks an color from the enemy colors at random, defaults to black color.
CrewmateColors get_random_enemy_colors();

// Determine the smallest dimension of a Dimensions instance
GLfloat smallest_dimension(Dimensions dimensions);

#endif /* UTILS_H */
