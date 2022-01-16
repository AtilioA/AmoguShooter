#ifndef GAME_H_
#define GAME_H_

#include <bits/stdc++.h>
#include <iostream>
#include "utils.hpp"


using namespace std;

#include "player.hpp"
#include "enemy.hpp"
#include "terrain.hpp"

class Game
{
    vector<Enemy> enemies;
    vector<Terrain> terrains;
    Player player;

public:
    Game(Point position, float width, float height, Color color);

    void add_enemy(Enemy enemy);
    vector<Enemy> get_enemies();
    void draw_enemies();

    void add_terrain(Terrain terrain);
    vector<Terrain> get_terrains();
    void draw_terrains();

    void add_player(Player player);
    Player get_player();
    void draw_player();
};

#endif /* GAME_H_ */
