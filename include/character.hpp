#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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

    // Combat
    Gunshot *gunshot;
    bool isAlive;

    // Walking
    GLint facingDirection;
    bool isWalking;
    bool isAnimationObverse;

    // Jumping
    bool isFalling;
    bool isJumping;
    bool canJump;
    GLfloat jumpTime;
    GLfloat jumpSpeed;
    GLfloat jumpInitialY;

    // Angle of each joint
    GLfloat gThetaThigh;
    GLfloat gThetaLeg;
    GLfloat gThetaLegLIMIT;
    bool isWalkingObserve;

    GLfloat gThetaArm;
    GLfloat gThetaArmMAX;
    GLfloat gThetaArmMIN;

public:
    Character(Point center, GLfloat radius, CrewmateColors colors, GLint id)
    {
        this->set_center(center);
        this->set_radius(radius);
        this->set_crewmate_colors(colors);
        this->set_height(radius * 2);
        this->set_id(id);
        this->set_terrain_below(NULL);

        this->trunkWidth = radius;

        this->gThetaArm = 0;
        this->gThetaArmMIN = -45;
        this->gThetaArmMAX = 45;

        this->gThetaLeg = 0;
        this->gThetaThigh = 0;
        this->gThetaLegLIMIT = 30;
        this->isWalkingObserve = true;

        this->facingDirection = Direction::RIGHT;

        this->gunshot = NULL;
        this->isAlive = true;

        this->canJump = true;
        this->isJumping = false;
        this->isFalling = false;
        this->jumpTime = 0;
        this->jumpSpeed = this->height * 0.33 * INC_KEYIDLE; // 3x player height in 1 second
        this->jumpInitialY = center.y;
    };
    virtual ~Character()
    {
        this->delete_gunshot();
    };

    GLfloat get_jump_speed();

    void set_is_falling(bool isFalling);
    bool get_is_falling();

    void set_is_jumping(bool isJumping);
    bool get_is_jumping();

    void set_can_jump(bool canJump);
    bool get_can_jump();

    void set_jump_time(GLfloat jumpTime);
    GLfloat get_jump_time();

    void set_jump_initial_y(GLfloat y);
    GLfloat get_jump_initial_y();

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

    void set_theta_arm(GLfloat theta);
    GLfloat get_theta_arm();

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

    void move_character(GLfloat dx, GLfloat dy, GLfloat frameTime);
    void jump(GLfloat clock);

    void determine_animation_direction();

    void move_arm_mouse_helper(GLfloat oldY, GLfloat oldX);

    void draw_left_thigh();
    void draw_left_leg();
    void draw_right_thigh();
    void draw_right_leg();
    void draw_body();
    void draw_arm();
    void draw_head();

    void rotate_arm(GLfloat inc);
    void rotate_thigh(GLfloat inc);
    void rotate_leg(GLfloat inc);
};

#endif /* CHARACTER_H */
