#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "utils.hpp"

class Character // abstract class
{
private:
    Point center;
    Color color;
    GLfloat radius;
    GLfloat height;

    // Angle of each joint
    GLfloat gThetaFoot;
    GLfloat gThetaLeg;
    GLfloat gThetaArm;

    GLfloat direction;
    GLfloat speed;

public:
    virtual void f() = 0;

    void set_center(Point p);
    Point get_center();

    void set_color(Color c);
    Color get_color();

    void set_radius(GLfloat r);
    GLfloat get_radius();

    void set_height(GLfloat h);
    GLfloat get_height();

    Character()
    {
        gThetaFoot = 0;
        gThetaLeg = 0;
        gThetaArm = 0;
    };

    void rotate_arm(GLfloat inc);
    void rotate_leg(GLfloat inc);
    void rotate_foot(GLfloat inc);
    void move_em_x(GLfloat dx);

    // Gunshot *Shoot();

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
    void move_character(GLfloat dx, GLfloat dy);
    void draw_foot(/*, GLfloat theta */);
    void draw_leg(/*, GLfloat theta */);
    void draw_body();
    void draw_arm(/*, GLfloat theta */);
    void draw_head(/* GLint radius */);
};

#endif /* CHARACTER_H */
