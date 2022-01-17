#ifndef GAME_H_
#define GAME_H_

#include <bits/stdc++.h>
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "terrain.hpp"

using namespace std;

class Game
{
private:
    vector<Enemy *> enemies;
    Player *player;
    vector<Terrain *> terrains;
    Terrain *background;
    string *arenaSVGFilename;
    Dimensions arenaDimensions;

public:
    Game(string *arenaSVGFilename)
    {
        this->arenaSVGFilename = arenaSVGFilename;
    };

    void add_enemy(Enemy *enemy);
    std::vector<Enemy *> get_enemies();
    void draw_enemies();

    void add_player(Player *player);
    Player *get_player();
    void draw_player();

    void add_terrain(Terrain *terrain);
    std::vector<Terrain *> get_terrains();
    void draw_terrains();

    void set_arena_background(Terrain *background);
    Terrain *get_arena_background();

    void set_arena_svg_filename(string *arenaSVGFilename);
    string *get_arena_svg_filename();

    void set_arena_dimensions(Dimensions arenaDimensions);
    Dimensions get_arena_dimensions();
};

#endif /* GAME_H_ */
