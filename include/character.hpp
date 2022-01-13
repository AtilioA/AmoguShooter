#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/arena.hpp"

// Dimensions
// #define paddleHeight 80
// #define paddleWidth 10
// #define baseHeight 40
// #define baseWidth 100
// #define radiusWheel 30
#define M_PI 3.14159265358979323846

class Character // abstract class
{
private:
    Point center;
    Color color;
    float radius;
    float height;

    // Angle of each joint
    GLfloat gThetaFoot;
    GLfloat gThetaLeg;
    GLfloat gThetaArm;

    GLfloat direction;
    GLfloat speed;

public:
    virtual void f() = 0;

    void set_center(Point p)
    {
        this->center = p;
    }

    Point get_center()
    {
        return this->center;
    }

    void set_color(Color c)
    {
        this->color = c;
    }

    Color get_color()
    {
        return this->color;
    }

    void set_radius(float r)
    {
        this->radius = r;
    }

    float get_radius()
    {
        return this->radius;
    }

    void set_height(float h)
    {
        this->height = h;
    }

    float get_height()
    {
        return this->height;
    }

    Character()
    {
        // gX = 0;
        gThetaFoot = 0;
        gThetaLeg = 0;
        gThetaArm = 0;
    };

    // void draw()
    // {
    //   gTheta2, gTheta3);
    // };

    void RotateArm(GLfloat inc);
    void RotateLeg(GLfloat inc);
    void RotateFoot(GLfloat inc);
    void MoveEmX(GLfloat dx);

    // Tiro *Shoot();

    // GLfloat GetX()
    // {
    //     return 0;
    // };

    // GLfloat GetY()
    // {
    //     return 0;
    // };

    void draw_character(/*, GLfloat thetaFoot,
                        GLfloat thetaLeg, GLfloat thetaArm*/
    );
    void draw_foot(/*, GLfloat theta */);
    void draw_leg(/*, GLfloat theta */);
    void draw_body();
    void draw_arm(/*, GLfloat theta */);
    void draw_head(GLint radius);
};

#endif /* CHARACTER_H */
