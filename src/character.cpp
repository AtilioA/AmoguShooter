#include "../include/character.hpp"

// Import game to check debug options
#include "../include/game.hpp"
extern Game *game;

bool Character::is_alive()
{
    return this->isAlive;
}

void Character::set_alive(bool alive)
{
    this->isAlive = alive;
}

void Character::delete_gunshot()
{
    if (this->gunshot != NULL)
    {
        delete this->gunshot;
        this->gunshot = NULL;
    }
}

Gunshot *Character::get_gunshot()
{
    return this->gunshot;
}

void Character::shoot()
{
    if (this->gunshot == NULL)
    {
        this->gunshot = new Gunshot(this->center.x, this->center.y, 0, 0, this->gThetaArm + (90 * this->facingDirection), this->facingDirection);
    }
}

void Character::move_arm_mouse_helper(GLfloat oldX, GLfloat oldY)
{
    // Normalize x
    GLfloat x = oldX - this->center.x;
    GLfloat y = oldY - this->center.y;

    // Calculate the angle of the arm
    GLfloat angle = rad_to_degrees(atan(y / x));

    if (angle < this->gThetaArmMAX && angle > this->gThetaArmMIN)
    {
        this->gThetaArm = angle * this->facingDirection;
    }
}

void Character::draw_head()
{
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

void Character::draw_body()
{
    glColor3f(this->colors.upperBody.r, this->colors.upperBody.g, this->colors.upperBody.b);
    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(-this->trunkWidth / 2, 0);
        glVertex2f(this->trunkWidth / 2, 0);
        glVertex2f(this->trunkWidth / 2, this->height / 8 * 5);
        glVertex2f(-this->trunkWidth / 2, this->height / 8 * 5);
    // clang-format on
    glEnd();
}

// 4/8 / 2
void Character::draw_left_thigh()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    if (facingDirection == Direction::LEFT)
    {
        glRotatef(-this->gThetaLeg / 2, 0, 0, 1);
    }
    else
    {
        glRotatef(this->gThetaLeg / 2, 0, 0, 1);
    }

    glRotatef(this->gThetaLeg, 0, 0, 1);

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 3, 0);
        glVertex2f(this->trunkWidth / 3, -this->height / 8 * 1.5);
        glVertex2f(0, -this->height / 8 * 1.5);
    // clang-format on
    glEnd();
}

// 4/8 / 2
void Character::draw_left_leg()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    if (facingDirection == Direction::LEFT)
    {
        glRotatef(this->gThetaLeg * 2, 0, 0, 1);
    }
    else
    {
        glRotatef(-this->gThetaLeg * 2, 0, 0, 1);
    }

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 3, 0);
        glVertex2f(this->trunkWidth / 3, -this->height / 8 * 1.5);
        glVertex2f(0, -this->height / 8 * 1.5);
    // clang-format on
    glEnd();
}

// 4/8 / 2
void Character::draw_right_thigh()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    if (facingDirection == Direction::RIGHT)
    {
        glRotatef(-this->gThetaLeg / 2, 0, 0, 1);
    }
    else
    {
        glRotatef(this->gThetaLeg / 2, 0, 0, 1);
    }

    glRotatef(this->gThetaLeg, 0, 0, 1);

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 3, 0);
        glVertex2f(this->trunkWidth / 3, -this->height / 8 * 1.5);
        glVertex2f(0, -this->height / 8 * 1.5);
    // clang-format on
    glEnd();
}

// 4/8 / 2
void Character::draw_right_leg()
{
    glColor3f(this->colors.lowerBody.r, this->colors.lowerBody.g, this->colors.lowerBody.b);

    if (facingDirection == Direction::RIGHT)
    {
        glRotatef(this->gThetaLeg * 2, 0, 0, 1);
    }
    else
    {
        glRotatef(-this->gThetaLeg * 2, 0, 0, 1);
    }

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(0, 0);
        glVertex2f(this->trunkWidth / 3, 0);
        glVertex2f(this->trunkWidth / 3, -this->height / 8 * 1.5);
        glVertex2f(0, -this->height / 8 * 1.5);
    // clang-format on
    glEnd();
}

void Character::draw_arm()
{
    glColor3f(this->colors.lowerBody.r * 0.5, this->colors.lowerBody.g * 0.5, this->colors.lowerBody.b * 0.5);

    glTranslatef(this->center.x, -this->center.y, 0);

    glRotatef(this->gThetaArm, 0, 0, 1);
    glRotatef(90 * this->facingDirection, 0, 0, 1);

    glBegin(GL_POLYGON);
    // clang-format off
        glVertex2f(- this->trunkWidth / 8, 0);
        glVertex2f( this->trunkWidth / 8, 0);
        glVertex2f(this->trunkWidth / 8, -this->height / 8 * 2.5);
        glVertex2f(-this->trunkWidth / 8, -this->height / 8 * 2.5);
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
    glTranslatef(-this->trunkWidth / 2, -this->radius + this->height / 8 * 1.5, 0);
    this->draw_left_leg();
    glPopMatrix();

    // Right leg
    glPushMatrix();
    glTranslatef(this->trunkWidth / 3 / 2, -this->radius + this->height / 8 * 1.5, 0);
    this->draw_right_leg();
    glPopMatrix();

    // Left thigh
    glPushMatrix();
    glTranslatef(-this->trunkWidth / 2, -this->radius + this->height / 8 * 3, 0);
    this->draw_left_thigh();
    glPopMatrix();

    // Right thigh
    glPushMatrix();
    glTranslatef(this->trunkWidth / 3 / 2, -this->radius + this->height / 8 * 3, 0);
    this->draw_right_thigh();
    glPopMatrix();

    // Body
    glPushMatrix();
    glTranslatef(0, -this->height / 8, 0);
    this->draw_body();
    glPopMatrix();

    // Head
    glPushMatrix();
    glTranslatef(0, this->height / 8 * 2, 0);
    this->draw_head();
    glPopMatrix();
    glPopMatrix();

    // Visual debug options
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
    glPushMatrix();
    this->draw_arm();
    glPopMatrix();
}

void Character::move_character(GLfloat dx, GLfloat dy, GLfloat frameTime)
{
    if (dx < 0)
    {
        this->facingDirection = Direction::LEFT;
    }
    else if (dx > 0)
    {
        this->facingDirection = Direction::RIGHT;
    }

    this->center.x += dx * frameTime;
    this->center.y += dy * frameTime;

    if (!this->isJumping)
    {
        // cout << "Not jumping" << endl;
        // cout << "gThetaLeg: " << this->gThetaLeg << endl;
        cout << abs(dx * frameTime * 3) << endl;
        // cout << "gThetaLegMAX: " << this->gThetaLegMAX << endl;
        {
            if (abs(gThetaLeg + abs(dx * frameTime * 3)) > 30)
                thetaLegIncreasing = !thetaLegIncreasing;
            if (thetaLegIncreasing)
            {
                // cout << "Increasing" << endl;
                gThetaLeg += abs(dx * frameTime * 3);
            }
            else
            {
                // cout << "Decreasing" << endl;
                gThetaLeg -= abs(dx * frameTime * 3);
            }
        }
    }
}

bool Character::is_inside_terrain(Terrain *terrain)
{
    Point terrainPos = terrain->get_center();

    if (this->center.y + this->radius >= terrainPos.y &&
        this->center.y - this->radius <= terrainPos.y + terrain->get_height())
    {
        if (this->center.x + this->trunkWidth / 2 >= terrainPos.x && this->center.x - this->trunkWidth / 2 <= terrainPos.x + terrain->get_width())
        {
            if (terrain->get_color().b != 1.0 && this->center.y <= terrainPos.y)
            {
                // cout << "collided from above terrain" << endl;
                this->isFalling = false;
                this->isJumping = false;
                this->canJump = true;
                this->terrainBelow = terrain;
            }

            // cout << "Player y: " << this->center.y << " Player radius: " << this->radius << endl;
            // cout << "Terrain y: " << terrainPos.y << " Terrain height: " << terrain->get_height() << endl;

            // if (this->center.y <= terrainPos.y)
            // {
            //     cout << "collided from above" << endl;

            //     this->isFalling = false;
            //     this->isJumping = false;
            //     this->canJump = true;
            // }

            if (this->center.y >= terrainPos.y + terrain->get_height())
            {
                // cout << "collided from below terrain" << endl;

                this->isFalling = true;
                this->isJumping = false;
                this->canJump = false;
            }

            return true;
        }
    }

    if (terrain->get_color().b == 1.0)
    {
        this->terrainBelow = NULL;
    }

    return false;
}

bool Character::is_inside_another_character(Character *character)
{
    // Check if characters are overlapping, considering both of their trunk widths
    return this->center.x + this->trunkWidth / 2 > character->center.x - character->trunkWidth / 2 &&
           this->center.x - this->trunkWidth / 2 < character->center.x + character->trunkWidth / 2 && this->center.y + this->radius > character->center.y - character->radius &&
           this->center.y - this->radius < character->center.y + character->radius;
}

GLfloat Character::get_jump_speed()
{
    return this->jumpSpeed;
}

GLfloat Character::get_jump_initial_y()
{
    return this->jumpInitialY;
}

void Character::set_jump_initial_y(GLfloat y)
{
    this->jumpInitialY = y;
}

void Character::set_is_falling(bool isFalling)
{
    this->isFalling = isFalling;
}
bool Character::get_is_falling()
{
    return this->isFalling;
}

void Character::set_is_jumping(bool isJumping)
{
    this->isJumping = isJumping;
}
bool Character::get_is_jumping()
{
    return this->isJumping;
}

void Character::set_can_jump(bool canJump)
{
    this->canJump = canJump;
}
bool Character::get_can_jump()
{
    return this->canJump;
}

void Character::set_jump_time(GLfloat jumpTime)
{
    this->jumpTime = jumpTime;
}
GLfloat Character::get_jump_time()
{
    return this->jumpTime;
}

void Character::set_facing_direction(GLint facingDirection)
{
    this->facingDirection = facingDirection;
}

GLint Character::get_facing_direction()
{
    return this->facingDirection;
}

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

void Character::set_theta_arm(GLfloat theta)
{
    this->gThetaArm = theta;
}

GLfloat Character::get_theta_arm()
{
    return this->gThetaArm;
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
