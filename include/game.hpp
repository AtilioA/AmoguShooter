#ifndef GAME_H_
#define GAME_H_

#include <bits/stdc++.h>
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "terrain.hpp"

using namespace std;

typedef struct tDebug
{
    bool highlightCollision;
    bool invinciblePlayer;
    bool pacificEnemies;
} Debug;

class Game
{
private:
    Player *player;
    vector<Enemy *> enemies;
    vector<Terrain *> terrains;
    Terrain *background;
    string *arenaSVGFilename;
    Dimensions arenaDimensions;
    Debug debugOptions;

public:
    Game(string *arenaSVGFilename)
    {
        this->arenaSVGFilename = arenaSVGFilename;
    };

    void add_enemy(Enemy *enemy);
    std::vector<Enemy *> get_enemies();
    void draw_enemies();

    bool is_inside_arena(Character *character);
    bool is_player_inside_any_enemy();
    bool is_player_inside_any_terrain();

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

    void set_debug_options(bool debug);
    Debug get_debug_options();
};

#endif /* GAME_H_ */
