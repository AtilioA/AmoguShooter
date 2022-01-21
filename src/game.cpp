#include "../include/game.hpp"
#include "../include/svg_reader.hpp"

using namespace std;

void Game::move_a_character(Character *character, GLfloat dx, GLfloat dy)
{
    character->move_character(dx, dy);
    this->handle_collision(character, dx, dy);
}

bool Game::check_collision(Character *character)
{
    if (this->is_outside_arena(character) || this->is_character_inside_any_terrain(character))
    {
        return true;
    }
    else
    {
        return is_character_inside_any_other_character(character);
    }
}

void Game::handle_collision(Character *character, GLfloat dx, GLfloat dy)
{
    if (this->check_collision(character))
    {
        character->move_character(-dx, -dy);
    }
}

void Game::apply_gravity(GLfloat deltaTime)
{
    // Player should be affected by gravity in a way that they reach the ground in 2 seconds after when standing 3 times their own height from the ground.
    // GLint MAX_JUMP_HEIGHT = this->player->get_height() * 3;
    // GLint MAX_JUMP_TIME = 2;
    // GLfloat gravityVelocity = MAX_JUMP_HEIGHT / deltaTime / MAX_JUMP_TIME;
    // cout << "gravityVelocity: " << gravityVelocity << endl;
    // GLfloat gravityVelocity = MAX_JUMP_HEIGHT / MAX_JUMP_TIME;

    GLfloat gravityVelocity = 0.33;

    // Apply gravity to player
    this->move_a_character(this->player, 0, gravityVelocity);

    // Apply gravity to enemies
    Enemy *currentEnemy = NULL;
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        currentEnemy = this->enemies[i];
        this->move_a_character(currentEnemy, 0, gravityVelocity);
    }
}

bool Game::will_enemy_fall(Enemy *enemy, GLfloat dx)
{
    Terrain *terrainBelowEnemy = enemy->get_terrain_below();
    if (terrainBelowEnemy == NULL)
    {
        return false;
    }
    else
    {
        // Add character trunk width / 2 later
        // cout << "new: " << enemy->get_center().x + dx << endl;
        // cout << "terrain: " << terrainBelowEnemy->get_center().x << " + " << terrainBelowEnemy->get_width() << "(" << terrainBelowEnemy->get_center().x + terrainBelowEnemy->get_width() << ")" << endl;
        GLfloat newX = enemy->get_center().x + dx;
        if (newX <= terrainBelowEnemy->get_center().x ||
            newX >= terrainBelowEnemy->get_center().x + terrainBelowEnemy->get_width())
        {
            return true;
        }
    }

    return false;
}

void Game::move_enemy_randomly(Enemy *enemy, float deltaTime)
{
    int integerDeltaTime = (int)deltaTime;

    // Placeholder
    GLfloat dx = 1.0;

    int randomNumber = rand() % integerDeltaTime;
    switch (randomNumber)
    {
    case 1:
        if (!will_enemy_fall(enemy, -dx))
        {
            move_a_character(enemy, -dx, 0);
        }
        break;
    case 2:
        if (!will_enemy_fall(enemy, dx))
        {
            move_a_character(enemy, dx, 0);
        }
        break;
    default:
        break;
    }
}

void Game::move_enemies_randomly(float deltaTime)
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        this->move_enemy_randomly(this->enemies[i], deltaTime);
    }
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

// WIP
void Game::free()
{
    // delete this->player;

    // this->enemies.clear();
    this->terrains.clear();

    delete this->background;
}

void Game::reset_game()
{
    this->free();
    parseSVGFile(this->arenaSVGFilename, this);
}

bool Game::is_outside_arena(Character *character)
{
    Terrain *terrain = this->background;
    Point terrainPos = this->background->get_center();

    // if (character == this->player)
    // {
    //     cout << terrainPos.y + terrain->get_height() << endl;
    //     cout << character->get_center().y << " | " << character->get_radius() << endl;
    //     cout << (character->get_center().x - character->get_radius() > terrainPos.x || character->get_center().x + character->get_radius() >= terrainPos.x + terrain->get_width()) << endl;
    // }

    // Replace radius with height
    if (character->get_center().y - character->get_radius() < terrainPos.y ||
        character->get_center().y + character->get_radius() > terrainPos.y + terrain->get_height())
    {
        return true;
    }

    // Replace radius with trunkWidth
    if (character->get_center().x - character->get_radius() < terrainPos.x || character->get_center().x + character->get_radius() > terrainPos.x + terrain->get_width())
    {
        return true;
    }

    return false;
}

bool Game::is_character_inside_any_other_character(Character *character)
{
    GLint charID = character->get_id();
    if (charID != this->player->get_id() && character->is_inside_another_character(this->player))
    {
        return true;
    }

    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        if (charID != this->enemies[i]->get_id() && character->is_inside_another_character(this->enemies[i]))
        {
            return true;
        }
    }

    return false;
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
                terrain->set_color(character->get_color());
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
    this->nCharacters++;
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
    this->nCharacters++;
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

GLint Game::get_n_characters()
{
    return this->nCharacters;
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
    this->debugOptions.drawObjectCenter = debug;
    this->debugOptions.drawCharacterHitbox = debug;
}

Debug Game::get_debug_options()
{
    return this->debugOptions;
}
