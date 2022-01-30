#include "../include/gunshot.hpp"

void Gunshot::draw_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R * 1.3, G * 1.3, B * 1.3);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        glVertex2f(radius * 1 * cos(deg_to_radians(i)), radius * 1 * sin(deg_to_radians(i)));
    }
    glEnd();
}

void Gunshot::draw_gunshot(GLfloat x, GLfloat y, Color crewmateUpperBodyColor)
{
    glPushMatrix();
    glTranslatef(x, -y, 0);
    draw_circ(this->gRadiusGunshot, crewmateUpperBodyColor.r, crewmateUpperBodyColor.g, crewmateUpperBodyColor.b);
    glPopMatrix();
}

void Gunshot::move(GLdouble frameTime)
{
    this->gX += this->gVel * sin(deg_to_radians(this->gDirectionAng)) * frameTime;
    this->gY += this->gVel * cos(deg_to_radians(this->gDirectionAng)) * frameTime;
}

bool Gunshot::is_valid()
{
    return MAX_DISTANCE > sqrt(pow(this->gX, 2) + pow(this->gY, 2));
}

bool Gunshot::is_inside_character(Character *character)
{
    if (this->gX + this->gRadiusGunshot > character->get_center().x - character->get_trunk_width() / 2 &&
        this->gX - this->gRadiusGunshot < character->get_center().x + character->get_trunk_width() / 2 && this->gY + this->gRadiusGunshot > character->get_center().y - character->get_radius() &&
        this->gY - this->gRadiusGunshot < character->get_center().y + character->get_radius())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Gunshot::is_inside_terrain(Terrain *terrain)
{
    Point terrainPos = terrain->get_center();

    if (this->gY + this->gRadiusGunshot >= terrainPos.y &&
        this->gY - this->gRadiusGunshot <= terrainPos.y + terrain->get_height())
    {
        if (this->gX + this->gRadiusGunshot >= terrainPos.x && this->gX - this->gRadiusGunshot <= terrainPos.x + terrain->get_width())
        {
            return true;
        }
    }

    return false;
}

GLfloat Gunshot::get_radius()
{
    return this->gRadiusGunshot;
}

Point Gunshot::get_center()
{
    return {this->gX, this->gY};
}
