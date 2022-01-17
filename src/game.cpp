#include "../include/game.hpp"

using namespace std;

// Enemy interface
void Game::add_enemy(Enemy *enemy)
{
    this->enemies.push_back(enemy);
}

vector<Enemy *> Game::get_enemies()
{
    return this->enemies;
}

void Game::draw_enemies()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        (this->enemies[i])->draw_character();
    }
}

// Terrain interface
void Game::add_terrain(Terrain *terrain)
{
    this->terrains.push_back(terrain);
}

vector<Terrain *> Game::get_terrains()
{
    return this->terrains;
}

void Game::draw_terrains()
{
    for (size_t i = 0; i < this->terrains.size(); i++)
    {
        (this->terrains[i])->draw_terrain();
    }
}

// Player interface
Player *Game::get_player()
{
    return this->player;
}

void Game::add_player(Player *player)
{
    this->player = player;
}

void Game::draw_player()
{
    (this->player)->draw_character();
}

void Game::set_arena_background(Terrain *background)
{
    this->background = background;
}

Terrain *Game::get_arena_background()
{
    return this->background;
}

void Game::set_arena_svg_filename(string *arenaSVGFilename)
{
    this->arenaSVGFilename = arenaSVGFilename;
}

string *Game::get_arena_svg_filename()
{
    return this->arenaSVGFilename;
}

void Game::set_arena_dimensions(Dimensions arenaDimensions)
{
    this->arenaDimensions = arenaDimensions;
}

Dimensions Game::get_arena_dimensions()
{
    return this->arenaDimensions;
}
