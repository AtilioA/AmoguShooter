
#include <iostream>

#include "../include/character.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include "../include/game.hpp"
#include "../include/terrain.hpp"
#include "../include/tinyxml2.hpp"

using namespace tinyxml2;
using namespace std;

extern Game *gameSVG;
extern Player *player;

void parseCircle(XMLElement *c)
{
    float cx, cy, r;
    Color color;

    c->QueryFloatAttribute("cx", &cx);
    c->QueryFloatAttribute("cy", &cy);
    c->QueryFloatAttribute("r", &r);

    Point position = {cx, cy};

    string circFill = c->Attribute("fill");

    if (circFill == "red")
    {
        cout << "-- ENEMY --" << endl;
        color = {1.0, 0.0, 0.0};
        Enemy *enemy = new Enemy(position, r, color);
        enemy->draw_character();
    }
    else if (circFill == "green")
    {
        cout << "-- PLAYER --" << endl;
        color = {0.0, 1.0, 0.0};
        player = new Player(position, r, color);
        player->draw_character();
    }
    else if (circFill == "blue")
    {
        cout << "-- BACKGROUND --" << endl;
        color = {0.0, 0.0, 1.0};
    }
    else
    {
        cout << "-- TERRAIN --" << endl;
        color = {1.0, 1.0, 1.0};
    }

    cout << "cx: " << cx << " cy: " << cy << " r: " << r << " circFill: " << circFill << endl;
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

    Point position = {x, y};

    if (rectFill == "black")
    {
        cout << "-- TERRAIN --" << endl;
        color = {0.0, 0.0, 0.0};
    }
    else if (rectFill == "blue")
    {
        cout << "-- BACKGROUND --" << endl;
        color = {0.0, 0.0, 1.0};
    }

    cout << "x: " << x << " y: " << y << " width: " << width << " height: " << height << " rectFill: " << rectFill << endl;

    Terrain *terrain = new Terrain(position, width, height, color);
    // Game *game = new Game(position, width, height, color);
    // game->draw_game_component();
    // gameSVG = game;
}

void parseSVGFile(string filepath)
{
    XMLDocument gameSVGfile;

    cout << filepath << endl;

    gameSVGfile.LoadFile(filepath.c_str());

    if (gameSVGfile.ErrorID() != 0)
    {
        cout << "Erro ao ler arquivo de entrada " << filepath << endl;
    }
    else
    {
        XMLElement *svgHeader = gameSVGfile.FirstChildElement("svg");
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
