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

public:
    Game(string *arenaSVGFilename)
    {
        this->arenaSVGFilename = arenaSVGFilename;
    };

    void add_enemy(Enemy *enemy);
    std::vector<Enemy *> get_enemies();
    void draw_enemies();

    void add_terrain(Terrain *terrain);
    std::vector<Terrain *> get_terrains();
    void draw_terrains();

    void add_player(Player *player);
    Player *get_player();
    void draw_player();
};

#endif /* GAME_H_ */
