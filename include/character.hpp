#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
// #include "game.hpp"
#include "utils.hpp"

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

    void set_center(Point p);
    Point get_center();

    void set_color(Color c);
    Color get_color();

    void set_radius(float r);
    float get_radius();

    void set_height(float h);
    float get_height();

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
    void move_character(float dx, float dy);
    void draw_foot(/*, GLfloat theta */);
    void draw_leg(/*, GLfloat theta */);
    void draw_body();
    void draw_arm(/*, GLfloat theta */);
    void draw_head(/* GLint radius */);
};

#endif /* CHARACTER_H */
