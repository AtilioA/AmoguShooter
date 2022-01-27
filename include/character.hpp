#ifndef CHARACTER_H
#define CHARACTER_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "gunshot.hpp"
#include "utils.hpp"
#include "terrain.hpp"

enum Direction : GLint
{
    LEFT = -1,
    RIGHT = 1
};

class Gunshot;
class Character // abstract class
{
protected:
    GLint id;
    Point center;
    CrewmateColors colors;
    GLfloat radius;
    GLfloat height;
    GLfloat trunkWidth;
    Terrain *terrainBelow;

    Gunshot *gunshot;

    bool isAlive;

    GLint facingDirection;
    bool isWalking;
    bool isAnimationObverse;

    bool isFalling;
    bool isJumping;
    bool canJump;
    GLfloat jumpTime;

    // Angle of each joint
    GLfloat gThetaThigh;
    GLfloat gThetaLeg;
    GLfloat gThetaLegMAX;
    GLfloat gThetaLegMIN;
    GLfloat gThetaArm;
    GLfloat gThetaArmMAX;
    GLfloat gThetaArmMIN;

    GLfloat speed;

public:
    Character(Point center, GLfloat radius, CrewmateColors colors, GLint id)
    {
        this->set_center(center);
        this->set_radius(radius);
        this->set_crewmate_colors(colors);
        this->set_height(radius * 2);
        this->set_id(id);
        this->set_terrain_below(NULL);
        this->gunshot = NULL;
        this->trunkWidth = radius;
        this->facingDirection = Direction::RIGHT;
        this->gThetaArm = 0;
        this->isAlive = true;
    };

    virtual void f() = 0;

    void set_isFalling(bool isFalling);
    bool get_isFalling();

    void set_isJumping(bool isJumping);
    bool get_isJumping();

    void set_canJump(bool canJump);
    bool get_canJump();

    void set_jumpTime(GLfloat jumpTime);
    GLfloat get_jumpTime();

    bool is_alive();
    void set_alive(bool alive);

    void delete_gunshot();
    Gunshot *get_gunshot();
    void shoot();

    void set_id(GLint id);
    GLint get_id();

    void set_center(Point p);
    Point get_center();

    void set_crewmate_colors(CrewmateColors c);
    CrewmateColors get_crewmate_colors();

    void set_radius(GLfloat r);
    GLfloat get_radius();

    void set_height(GLfloat h);
    GLfloat get_height();

    void set_trunk_width(GLfloat t);
    GLfloat get_trunk_width();

    void set_terrain_below(Terrain *terrain);
    Terrain *get_terrain_below();

    void set_facing_direction(GLint facingDirection);
    GLint get_facing_direction();

    void draw_character();

    bool is_inside_another_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);

    void move_character(GLfloat dx, GLfloat dy, GLfloat deltaTime);
    void jump(GLfloat clock);

    void determine_animation_direction();

    void moveArmMouseHelper(GLfloat dy, GLfloat dx);

    void draw_leg();
    void draw_thigh();
    void draw_body();
    void draw_arm();
    void draw_head();

    void rotate_arm(GLfloat inc);
    void rotate_thigh(GLfloat inc);
    void rotate_leg(GLfloat inc);
};

#endif /* CHARACTER_H */
