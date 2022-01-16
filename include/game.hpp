#ifndef GAME_H_
#define GAME_H_

#include <bits/stdc++.h>
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "terrain.hpp"

class Game
{
private:
    std::vector<Enemy> enemies;
    std::vector<Terrain> terrains;
    Terrain background;
    Player player;

public:
    Game();

    void add_enemy(Enemy enemy);
    std::vector<Enemy> get_enemies();
    void draw_enemies();

    void add_terrain(Terrain *terrain);
    std::vector<Terrain> get_terrains();
    void draw_terrains();

    void add_player(Player player);
    Player get_player();
    void draw_player();
};

#endif /* GAME_H_ */
