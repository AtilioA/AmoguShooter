
#include <iostream>
#include "../include/input.hpp"
#include "../include/player.hpp"
#include "../include/arena.hpp"
#include "../include/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

extern Arena *arenaSVG;
extern Lutador *lutadorPrincipal;
extern Oponente *lutadorOponente;

void parseCircle(XMLElement *c, int i)
{
    float cx, cy, r;
    Color color;

    c->QueryFloatAttribute("cx", &cx);
    c->QueryFloatAttribute("cy", &cy);
    c->QueryFloatAttribute("r", &r);

    Point center = {cx, cy};

    string fill = c->Attribute("fill");

    if (fill == "red")
    {
        color = {1.0, 0.0, 0.0};
    }
    else if (fill == "green")
    {
        color = {0.0, 1.0, 0.0};
    }
    else if (fill == "blue")
    {
        color = {0.0, 0.0, 1.0};
    }
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
        color = {1.0, 0.0, 0.0};
    }
    else if (rectFill == "green")
    {
        color = {0.0, 1.0, 0.0};
    }
    else if (rectFill == "blue")
    {
        color = {0.0, 0.0, 1.0};
    }

    // Arena *arena = new Arena(x, y, width, height, color);
    // arenaSVG = arena;
}

void parseSVGFile(string filepath)
{
    XMLDocument arenaSVGfile;

    arenaSVGfile.LoadFile(filepath.c_str());

    if (arenaSVGfile.ErrorID() != 0)
    {
        cout << "Erro no arquivo de entrada config.xml" << endl;
    }
    else
    {
        XMLElement *svgHeader = arenaSVGfile.FirstChildElement("svg");
        XMLElement *svgBody = svgHeader->FirstChildElement();

        int i = 0;
        while (svgBody != NULL)
        {
            string tagType = svgBody->Value();

            if (tagType == "rect")
            {
                parseRect(svgBody);
            }
            else if (tagType == "circle")
            {
                parseCircle(svgBody, i);
            }
            
            svgBody = svgBody->NextSiblingElement();
        }
    }
}
