#include <math.h>
#include <GL/glut.h>

#include "../include/character.hpp"

void Character::draw_head()
{
    glColor3f(172.0 / 255, 66.0 / 255, 85.0 / 255); // rgb(172,66,85)

    glPointSize(4);

    glBegin(GL_POINTS);
    // clang-format off
        for (size_t i = 0; i < 360; i += 180)
        {
            glVertex2f(this->radius / 2 * cos(i * M_PI / 180), this->radius / 2 * sin(i * M_PI / 180));
        }
    // clang-format on
    glEnd();
}

// Draw a sequence of points representing the wheel of the character
void Character::draw_body()
{
    glColor3f(this->color.r, this->color.g, this->color.b); // rgb(56,76,92)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 4, 0);
        glVertex2f(this->radius / 4, 0);
        glVertex2f(this->radius / 4, this->height / 1.5);
        glVertex2f(-this->radius / 4, this->height / 1.5);
    // clang-format on
    glEnd();
}

void Character::draw_leg(/*, GLfloat theta */)
{
    glColor3f(228.0 / 255, 170.0 / 255, 141.0 / 255); // rgb(228, 170, 141)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 4, 0);
        glVertex2f(this->radius / 4, 0);
        glVertex2f(this->radius / 4, this->height / 2);
        glVertex2f(-this->radius / 4, this->height / 2);
    // clang-format on
    glEnd();
}

void Character::draw_foot(/*, GLfloat theta */)
{
    glColor3f(121.0 / 255, 200.0 / 255, 226.0 / 255); // rgb(121, 200, 255)
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 4, 0);
        glVertex2f(this->radius / 4, 0);
        glVertex2f(this->radius / 4, this->height / 2);
        glVertex2f(-this->radius / 4, this->height / 2);
    // clang-format on
    glEnd();
}

void Character::draw_arm(/*, GLfloat theta */)
{
    glColor3f(151.0 / 255, 220.0 / 255, 226.0 / 255); // rgb(151, 220, 255)

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->radius / 6, 0);
        glVertex2f(this->radius / 6, 0);
        glVertex2f(this->radius / 6, this->height / 2);
        glVertex2f(-this->radius / 6, this->height / 2);
    // clang-format on
    glEnd();
}

// Draw a character
void Character::draw_character()
{
    glPushMatrix();

    glTranslatef(this->center.x, -this->center.y, 0);
    // glRotatef(theta, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0, this->height / 2, 0);
    this->draw_leg(/*, theta */);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, this->height / 2, 0);
    this->draw_foot(/*, theta */);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, this->height / 2, 0);
    this->draw_arm(/*, theta */);
    glPopMatrix();

    this->draw_body();

    this->draw_head();

    glPopMatrix();
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
    Point backgroundPos = terrain->get_center();

    if (this->center.x >= backgroundPos.x &&
        this->center.x <= backgroundPos.x + terrain->get_width() &&
        this->center.y >= backgroundPos.y &&
        this->center.y <= backgroundPos.y + terrain->get_height())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Character::is_inside_another_character(Character *character)
{
    if (this->center.x + this->radius > character->center.x - character->radius &&
        this->center.x - this->radius<character->center.x + character->radius &&this->center.y + this->radius> character->center.y - character->radius &&
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
// void RotatePoint(Point position, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
// {
// }

// Gunshot *Character::Shoot()
// {
// }

void Character::set_center(Point p)
{
    this->center = p;
}
void Character::set_color(Color c)
{
    this->color = c;
}
void Character::set_radius(GLfloat r)
{
    this->radius = r;
}
void Character::set_height(GLfloat h)
{
    this->height = h;
}

Point Character::get_center()
{
    return this->center;
}

Color Character::get_color()
{
    return this->color;
}

GLfloat Character::get_radius()
{
    return this->radius;
}

GLfloat Character::get_height()
{
    return this->height;
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
