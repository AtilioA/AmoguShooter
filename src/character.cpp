#include <math.h>
#include <GL/glut.h>

#include "../include/character.hpp"

// Import game to check debug options
#include "../include/game.hpp"
extern Game *game;


void Character::draw_head()
{
    // glColor3f(200.0 / 255, 66.0 / 255, 85.0 / 255); // rgb(200,66,85)
    glColor3f(255.0 / 255, 255.0 / 255, 255.0 / 255);

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->trunkWidth / 2, 0);
        glVertex2f(this->trunkWidth / 2, 0);
        glVertex2f(this->trunkWidth / 2, this->height / 8);
        glVertex2f(-this->trunkWidth / 2, this->height / 8);
    // clang-format on
    glEnd();
}

// Draw a sequence of points representing the wheel of the character
void Character::draw_body()
{
    glColor3f(this->colors.upperBody.r, this->colors.upperBody.g, this->colors.upperBody.b); // rgb(56,76,92)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->trunkWidth / 2, 0);
        glVertex2f(this->trunkWidth / 2, 0);
        glVertex2f(this->trunkWidth / 2, this->height / 8 * 3);
        glVertex2f(-this->trunkWidth / 2, this->height / 8 * 3);
    // clang-format on
    glEnd();
}

// 4/8 / 2
void Character::draw_thigh()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b); // rgb(228, 170, 141)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 3, 0);
        glVertex2f(this->trunkWidth / 3, -this->height / 8 * 2);
        glVertex2f(0, -this->height / 8 * 2);
    // clang-format on
    glEnd();
}

// 4/8 / 2
void Character::draw_leg()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b); // rgb(121, 200, 255)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 3, 0);
        glVertex2f(this->trunkWidth / 3, -this->height / 8 * 2);
        glVertex2f(0, -this->height / 8 * 2);
    // clang-format on
    glEnd();
}

void Character::draw_arm()
{
    glColor3f(200.0 / 255, 180.0 / 255, 255.0 / 255); // rgb(200, 180, 255)

    glRotatef(this->gThetaArm, 0, 0, 1);

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 4, 0);
        glVertex2f(this->trunkWidth / 4, -this->height / 8 * 2);
        glVertex2f(0, -this->height / 8 * 4);
    // clang-format on
    glEnd();
}

// Draw a character
void Character::draw_character()
{
    glPushMatrix();

    glTranslatef(this->center.x, -this->center.y, 0);

    // Left leg
    glPushMatrix();
    glTranslatef(-this->trunkWidth / 2, -this->radius + this->height / 8 * 2, 0);
    this->draw_leg(/*, theta */);
    glPopMatrix();

    // Right leg
    glPushMatrix();
    glTranslatef(this->trunkWidth / 3 / 2, -this->radius + this->height / 8 * 2, 0);
    this->draw_leg(/*, theta */);
    glPopMatrix();

    // Left thigh
    glPushMatrix();
    glTranslatef(-this->trunkWidth / 2, -this->radius + this->height / 8 * 4, 0);
    this->draw_thigh(/*, theta */);
    glPopMatrix();

    // Right thigh
    glPushMatrix();
    glTranslatef(this->trunkWidth / 3 / 2, -this->radius + this->height / 8 * 4, 0);
    this->draw_thigh(/*, theta */);
    glPopMatrix();

    // Body
    glPushMatrix();
    this->draw_body();
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0, this->height / 8 * 3, 0);
    this->draw_head();
    glPopMatrix();

    // Draw a circle of radius this->radius
    // glPushMatrix();
    // glTranslatef(this->center.x, -this->center.y, 0);
    // glColor3f(this->color.r, this->color.g, this->color.b); // rgb(56,76,92)
    // glBegin(GL_POLYGON);
    // // clang-format off
    //     for (size_t i = 0; i < 360; i += 5)
    //     {
    //         glVertex2f(this->radius * cos(i * M_PI / 180), this->radius * sin(i * M_PI / 180));
    //     }
    // // clang-format on
    // glEnd();
    // glPopMatrix();

    glPopMatrix();

    if (game->get_debug_options().drawObjectCenter)
    {
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y, 0);
        glPointSize(4);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        glPopMatrix();

        // Also draw height
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y - this->radius, 0);
        glTranslatef(0, this->height, 0);
        glPointSize(4);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        glPopMatrix();
    }

    if (game->get_debug_options().drawCharacterHitbox)
    {
        glPushMatrix();
        glTranslatef(this->center.x, -this->center.y - this->radius, 0);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0, 0);
        glVertex2f(-this->trunkWidth / 2, 0);
        glVertex2f(-this->trunkWidth / 2, this->height);
        glVertex2f(this->trunkWidth / 2, this->height);
        glVertex2f(this->trunkWidth / 2, 0);
        glEnd();
        glPopMatrix();
    }

    // Arm
    // glPushMatrix();
    // glTranslatef(this->center.x, -this->center.y, 0);

    // glTranslatef(this->trunkWidth / 4, this->height / 8 * 3 / 2, 0);
    // this->draw_arm();
    // glPopMatrix();
}

void Character::move_character(GLfloat dx, GLfloat dy /*, GLfloat deltaTime*/)
{
    // Placeholder
    // GLdouble deltaTime = 1;

    Character::center.x += dx /** deltaTime*/;
    Character::center.y += dy /** deltaTime*/;
}

bool Character::is_inside_terrain(Terrain *terrain)
{
    Point terrainPos = terrain->get_center();

    if (this->center.y + this->radius >= terrainPos.y &&
        this->center.y - this->radius <= terrainPos.y + terrain->get_height())
    {
        if (this->center.x + this->trunkWidth / 2 >= terrainPos.x && this->center.x - this->trunkWidth / 2 <= terrainPos.x + terrain->get_width())
        {
            if (terrain->get_color().b != 1)
            {
                this->terrainBelow = terrain;
            }
            return true;
        }
    }

    if (terrain->get_color().b == 1)
    {
        this->terrainBelow = NULL;
    }

    return false;
}

bool Character::is_inside_another_character(Character *character)
{
    if (this->center.x + this->trunkWidth / 2 > character->center.x - character->trunkWidth / 2 &&
        this->center.x - this->trunkWidth / 2 < character->center.x + character->trunkWidth / 2 && this->center.y + this->radius > character->center.y - character->radius &&
        this->center.y - this->radius < character->center.y + character->radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Funcao auxiliar de rotacao
// void RotatePoint(Point center, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
// {
// }

// Gunshot *Character::Shoot()
// {
// }

void Character::set_terrain_below(Terrain *terrain)
{
    this->terrainBelow = terrain;
}

void Character::set_center(Point p)
{
    this->center = p;
}

void Character::set_crewmate_colors(CrewmateColors c)
{
    this->colors = c;
}

void Character::set_radius(GLfloat r)
{
    this->radius = r;
}

void Character::set_height(GLfloat h)
{
    this->height = h;
}

void Character::set_id(GLint id)
{
    this->id = id;
}

GLint Character::get_id()
{
    return this->id;
}

Point Character::get_center()
{
    return this->center;
}

CrewmateColors Character::get_crewmate_colors()
{
    return this->colors;
}

GLfloat Character::get_radius()
{
    return this->radius;
}

GLfloat Character::get_height()
{
    return this->height;
}

void Character::set_trunk_width(GLfloat t)
{
    this->trunkWidth = t;
}

GLfloat Character::get_trunk_width()
{
    return this->trunkWidth;
}

Terrain *Character::get_terrain_below()
{
    return this->terrainBelow;
}

// Make character jump for 4 seconds. The maximum height will be equal to 3 times the character's height and shall be reached in 2 seconds.
void Character::jump(GLfloat clock)
{
    if (clock <= 0)
    {
        return;
    }

    // GLint jumpTime = 4;
    // GLfloat jumpHeight = 3 * this->height;
    // GLfloat jumpVelocity = jumpHeight / jumpTime / 2;

    // GLfloat jumpAcceleration = jumpVelocity / jumpTime;
}
