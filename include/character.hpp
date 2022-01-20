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
    Terrain *terrainBelow;

    bool isJumping;
    GLfloat jumpTime;

    // Angle of each joint
    GLfloat gThetaFoot;
    GLfloat gThetaLeg;
    GLfloat gThetaArm;

    GLfloat direction;
    GLfloat speed;

public:
    Character(Point pos, GLfloat radius, Color color, GLint id)
    {
        this->set_center(pos);
        this->set_radius(radius);
        this->set_color(color);
        this->set_height(radius * 2);
        this->set_id(id);
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

    void set_terrain_below(Terrain *terrain);
    Terrain *get_terrain_below();

    Character()
    {
        terrainBelow = NULL;
        gThetaFoot = 0;
        gThetaLeg = 0;
        gThetaArm = 0;
    };

    // Gunshot *Shoot();

    void draw_character(/*, GLfloat thetaFoot,
                        GLfloat thetaLeg, GLfloat thetaArm*/
    );

    bool is_inside_another_character(Character *character);
    bool is_inside_terrain(Terrain *terrain);

    void move_character(GLfloat dx, GLfloat dy);
    void jump(GLfloat clock);

    void draw_foot(/*, GLfloat theta */);
    void draw_leg(/*, GLfloat theta */);
    void draw_body();
    void draw_arm(/*, GLfloat theta */);
    void draw_head(/* GLint radius */);

    void rotate_arm(GLfloat inc);
    void rotate_leg(GLfloat inc);
    void rotate_foot(GLfloat inc);
};

#endif /* CHARACTER_H */
