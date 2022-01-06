
#include <iostream>
#include "../include/character.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include "../include/arena.hpp"
#include "../include/tinyxml2.hpp"

using namespace tinyxml2;
using namespace std;

extern Arena *arenaSVG;
extern Player *player;
extern Enemy *enemy;

void parseCircle(XMLElement *c)
{
    float cx, cy, r;
    Color color;

    c->QueryFloatAttribute("cx", &cx);
    c->QueryFloatAttribute("cy", &cy);
    c->QueryFloatAttribute("r", &r);

    // Point center = {cx, cy};

    string circFill = c->Attribute("fill");

    if (circFill == "red")
    {
        cout << "-- ENEMY --" << endl;
        color = {1.0, 0.0, 0.0};
    }
    else if (circFill == "green")
    {
        cout << "-- PLAYER --" << endl;
        color = {0.0, 1.0, 0.0};
    }
    else if (circFill == "blue")
    {
        cout << "-- BACKGROUND --" << endl;
        color = {0.0, 0.0, 1.0};
    }
    else
    {
        cout << "-- ARENA --" << endl;
        color = {1.0, 1.0, 1.0};
    }

    cout << "cx: " << cx << " cy: " << cy << " r: " << r << " circFill: " << circFill << endl;

    // if (i == 1)
    // {
    //   lutadorPrincipal = new Lutador(center, r, color, 0);
    // }
    // else
    // {
    //   lutadorOponente = new Oponente(center, r, color, 0);
    // }
}

void parseRect(XMLElement *ret)
{
    float x, y, width, height;
    Color color;

    ret->QueryFloatAttribute("x", &x);
    ret->QueryFloatAttribute("y", &y);
    ret->QueryFloatAttribute("width", &width);
    ret->QueryFloatAttribute("height", &height);
    string rectFill = ret->Attribute("fill");

    if (rectFill == "red")
    {
        cout << "-- ENEMY --" << endl;
        color = {1.0, 0.0, 0.0};
    }
    else if (rectFill == "green")
    {
        cout << "-- PLAYER --" << endl;
        color = {0.0, 1.0, 0.0};
    }
    else if (rectFill == "blue")
    {
        cout << "-- BACKGROUND --" << endl;
        color = {0.0, 0.0, 1.0};
    }
    else
    {
        cout << "-- ARENA --" << endl;
        color = {1.0, 1.0, 1.0};
    }

    cout << "x: " << x << " y: " << y << " width: " << width << " height: " << height << " rectFill: " << rectFill << endl;

    // Arena *arena = new Arena(x, y, width, height, color);
    // arenaSVG = arena;
}

void parseSVGFile(string filepath)
{
    XMLDocument arenaSVGfile;

    cout << filepath << endl;

    arenaSVGfile.LoadFile(filepath.c_str());

    if (arenaSVGfile.ErrorID() != 0)
    {
        cout << "Erro ao ler arquivo de entrada " << filepath << endl;
    }
    else
    {
        XMLElement *svgHeader = arenaSVGfile.FirstChildElement("svg");
        XMLElement *svgBody = svgHeader->FirstChildElement();

        // int i = 0;
        while (svgBody != NULL)
        {
            string tagType = svgBody->Value();

            if (tagType == "rect")
            {
                parseRect(svgBody);
            }
            else if (tagType == "circle")
            {
                parseCircle(svgBody);
            }

            svgBody = svgBody->NextSiblingElement();
        }
    }
}
