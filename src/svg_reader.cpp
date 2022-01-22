
#include <iostream>

#include "../include/character.hpp"
#include "../include/player.hpp"
#include "../include/utils.hpp"
#include "../include/enemy.hpp"
#include "../include/game.hpp"
#include "../include/terrain.hpp"
#include "../include/tinyxml2.hpp"

using namespace tinyxml2;
using namespace std;

void parseCircle(XMLElement *circ, Game *game)
{
    GLfloat cx, cy, r;
    CrewmateColors colors;

    circ->QueryFloatAttribute("cx", &cx);
    circ->QueryFloatAttribute("cy", &cy);
    circ->QueryFloatAttribute("r", &r);
    string circFill = circ->Attribute("fill");

    Point center = {cx, cy};

    cout << "cx: " << cx << " cy: " << cy << " r: " << r << " circFill: " << circFill << endl;

    if (circFill == "red")
    {
        cout << "-- ENEMY --" << endl;
        colors = get_random_enemy_colors();
        Enemy *enemy = new Enemy(center, r, colors, game->get_n_characters());
        game->add_enemy(enemy);
    }
    else if (circFill == "green")
    {
        cout << "-- PLAYER --" << endl;
        colors = get_player_colors();
        Player *player = new Player(center, r, colors, game->get_n_characters());
        game->add_player(player);
    }
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

    Point center = {x, y};

    cout << "x: " << x << " y: " << y << " width: " << width << " height: " << height << " rectFill: " << rectFill << endl;

    if (rectFill == "black")
    {
        cout << "-- TERRAIN --" << endl;
        color = {0.0, 0.0, 0.0};
        Terrain *terrain = new Terrain(center, width, height, color);
        terrain->draw_terrain();
        game->add_terrain(terrain);
    }
    else if (rectFill == "blue")
    {
        cout << "-- BACKGROUND --" << endl;
        color = {0.0, 0.0, 0.75};

        Terrain *background = new Terrain(center, width, height, color);
        game->set_arena_background(background);

        Dimensions dimensions = {width, height};
        game->set_arena_dimensions(dimensions);
    }
}

void parseSVGFile(string filepath, Game *game)
{
    XMLDocument gameSVGfile;

    game->set_arena_svg_filename(filepath);

    cout << "Parsing " << game->get_arena_svg_filename() << endl;

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
