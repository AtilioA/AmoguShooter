#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "utils.hpp"
#include "terrain.hpp"

class Character // abstract class
{
protected:
    GLint id;
    Point center;
    Color color;
    GLfloat radius;
    GLfloat height;
    GLfloat trunkWidth;
    Terrain *terrainBelow;

    bool isWalking;
    bool isAnimationObverse;

    bool isJumping;
    GLfloat jumpTime;

    // Angle of each joint
    GLfloat gThetaThigh;
    GLfloat gThetaLeg;
    GLfloat gThetaLegMAX;
    GLfloat gThetaLegMIN;
    GLfloat gThetaArm;
    GLfloat gThetaArmMAX;
    GLfloat gThetaArmMIN;
    bool animateHead;

    GLfloat direction;
    GLfloat speed;

public:
    Character(Point center, GLfloat radius, Color color, GLint id)
    {
        this->set_center(center);
        this->set_radius(radius);
        this->set_color(color);
        this->set_height(radius * 2);
        this->set_id(id);
        this->set_terrain_below(NULL);
        this->trunkWidth = radius;
        this->animateHead = true;
        this->gThetaArm = 80;
    };

    virtual void f() = 0;

    void set_id(GLint id);
    GLint get_id();

    void set_center(Point p);
    Point get_center();

    void set_color(Color c);
    Color get_color();

    void set_radius(GLfloat r);
    GLfloat get_radius();

    void set_height(GLfloat h);
    GLfloat get_height();

    void set_trunk_width(GLfloat t);
    GLfloat get_trunk_width();

    void set_terrain_below(Terrain *terrain);
    Terrain *get_terrain_below();

    // Gunshot *Shoot();

    void draw_character(/*, GLfloat thetaLeg,
                        GLfloat thetaThigh, GLfloat thetaArm*/
    );

    bool is_inside_another_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);

    void move_character(GLfloat dx, GLfloat dy);
    void jump(GLfloat clock);

    void determine_animation_direction();

    void draw_leg();
    void draw_thigh();
    void draw_body();
    void draw_arm();
    void draw_head();
    void toggle_animate_head();

    void rotate_arm(GLfloat inc);
    void rotate_thigh(GLfloat inc);
    void rotate_leg(GLfloat inc);
};

#endif /* CHARACTER_H */
