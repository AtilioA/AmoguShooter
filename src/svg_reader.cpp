
#include <iostream>

#include "../include/character.hpp"
#include "../include/player.hpp"
#include "../include/enemy.hpp"
#include "../include/game.hpp"
#include "../include/terrain.hpp"
#include "../include/tinyxml2.hpp"

using namespace tinyxml2;
using namespace std;

// extern Game *gameSVG;
// extern Player *player;

void parseCircle(XMLElement *circ, Game *game)
{
    GLfloat cx, cy, r;
    Color color;

    circ->QueryFloatAttribute("cx", &cx);
    circ->QueryFloatAttribute("cy", &cy);
    circ->QueryFloatAttribute("r", &r);

    Point position = {cx, cy};

    string circFill = circ->Attribute("fill");

    if (circFill == "red")
    {
        cout << "-- ENEMY --" << endl;
        color = {1.0, 0.0, 0.0};
        Enemy *enemy = new Enemy(position, r, color);
        game->add_enemy(enemy);
    }
    else if (circFill == "green")
    {
        cout << "-- PLAYER --" << endl;
        color = {0.0, 1.0, 0.0};
        Player *player = new Player(position, r, color);
        player->draw_character();
        game->add_player(player);
    }
    // else if (circFill == "blue")
    // {
    //     cout << "-- BACKGROUND --" << endl;
    //     color = {0.0, 0.0, 1.0};
    // }
    // else
    // {
    //     cout << "-- TERRAIN --" << endl;
    //     color = {1.0, 1.0, 1.0};
    // }

    cout << "cx: " << cx << " cy: " << cy << " r: " << r << " circFill: " << circFill << endl;
}

void parseRect(XMLElement *rect, Game *game)
{
    GLfloat x, y, width, height;
    Color color;

    rect->QueryFloatAttribute("x", &x);
    rect->QueryFloatAttribute("y", &y);
    rect->QueryFloatAttribute("width", &width);
    rect->QueryFloatAttribute("height", &height);
    string rectFill = rect->Attribute("fill");

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

        Terrain *background = new Terrain(position, width, height, color);
        game->set_arena_background(background);

        Dimensions dimensions = {width, height};
        game->set_arena_dimensions(dimensions);
    }

    cout << "x: " << x << " y: " << y << " width: " << width << " height: " << height << " rectFill: " << rectFill << endl;

    Terrain *terrain = new Terrain(position, width, height, color);
    game->add_terrain(terrain);
}

void parseSVGFile(string filepath, Game *game)
{
    XMLDocument gameSVGfile;

    cout << "Parsing " << filepath << endl;

    gameSVGfile.LoadFile(filepath.c_str());

    if (gameSVGfile.ErrorID() != 0)
    {
        cout << "Erro ao ler arquivo de entrada " << filepath << endl;
    }
    else
    {
        XMLElement *svgHeader = gameSVGfile.FirstChildElement("svg");
        XMLElement *svgBody = svgHeader->FirstChildElement();

        while (svgBody != NULL)
        {
            string tagType = svgBody->Value();

            if (tagType == "rect")
            {
                parseRect(svgBody, game);
            }
            else
            {
                parseCircle(svgBody, game);
            }

            svgBody = svgBody->NextSiblingElement();
        }
    }
}
