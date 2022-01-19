#include "../include/game.hpp"
#include "../include/svg_reader.hpp"

using namespace std;

void Game::apply_gravity(GLfloat deltaTime)
{
    // Player should be affected by gravity in a way that they reach the ground in 2 seconds after when standing 3 times their own height from the ground.
    GLint MAX_JUMP_HEIGHT = this->player->get_height() * 3;
    GLint MAX_JUMP_TIME = 2;
    GLfloat gravityVelocity = MAX_JUMP_HEIGHT / deltaTime / MAX_JUMP_TIME;
    // cout << "gravityVelocity: " << gravityVelocity << endl;
    // GLfloat gravityVelocity = MAX_JUMP_HEIGHT / MAX_JUMP_TIME;

    this->player->move_character(0, 0.33);
}

void Game::free_terrains()
{
    for (auto &terrain : this->terrains)
    {
        delete terrain;
    }
}

void Game::free_enemies()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        if (this->enemies[i] != NULL)
        {
            delete this->enemies[i];
        }
    }
}

void Game::free()
{
    delete this->player;

    // free_terrains();
    // free_enemies();

    delete this->background;
}

void Game::reset_game()
{
    this->free();
    parseSVGFile(this->arenaSVGFilename, this);
}

bool Game::is_inside_arena(Character *character)
{
    return character->is_inside_terrain(this->background);
}

bool Game::is_player_inside_any_enemy()
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        Enemy *enemy = this->enemies[i];
        if (this->player->is_inside_another_character(enemy))
        {
            return true;
        }
    }

    return false;
}

bool Game::is_character_inside_any_terrain(Character *character)
{
    for (size_t i = 0; i < this->terrains.size(); i++)
    {
        Terrain *terrain = this->terrains[i];
        if (character->is_inside_terrain(terrain))
        {
            if (this->debugOptions.highlightCollision)
            {
                if (character == this->player)
                {
                    terrain->set_color({0, 1, 0});
                }
                else
                {
                    terrain->set_color({1, 0, 0});
                }
            }

            return true;
        }
        else
        {
            // if (this->debugOptions.highlightCollision)
            // {
            //     terrain->set_color({0, 0, 0});
            // }
        }
    }

    return false;
}

bool Game::is_player_inside_any_terrain()
{
    return is_character_inside_any_terrain(this->player);
}

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
    this->player->draw_character();
}

void Game::set_arena_background(Terrain *background)
{
    this->background = background;
}

Terrain *Game::get_arena_background()
{
    return this->background;
}

void Game::set_arena_svg_filename(string arenaSVGFilename)
{
    this->arenaSVGFilename = arenaSVGFilename;
}

string Game::get_arena_svg_filename()
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

// If debug is true, make Debug struct have all elements as true. If false, make Debug struct have all elements as false (default)
void Game::set_debug_options(bool debug)
{
    this->debugOptions.highlightCollision = debug;
    this->debugOptions.pacificEnemies = debug;
    this->debugOptions.invinciblePlayer = debug;
}

Debug Game::get_debug_options()
{
    return this->debugOptions;
}
