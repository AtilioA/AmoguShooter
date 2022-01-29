#include "../include/game.hpp"
#include "../include/svg_reader.hpp"

using namespace std;

void Game::make_a_character_jump(Character *character, GLfloat frameTime)
{
    // cout << "is_jumping: " << character->get_is_jumping() << endl;
    // cout << "initial y: " << character->get_jump_initial_y() - character->get_height() * 3 << endl;
    // cout << "y: " << character->get_center().y << endl;

    character->set_can_jump(false);

    if (character->get_is_jumping() && (character->get_jump_initial_y() - character->get_height() * 3) < character->get_center().y)
    {
        character->set_is_jumping(true);
        character->set_is_falling(false);
        character->set_terrain_below(NULL);

        // cout << -character->get_jump_speed() << endl;
        // cout << frameTime << endl;
        this->move_a_character(character, 0, -character->get_jump_speed(), frameTime);
    }
    else
    {
        character->set_is_jumping(false);
        character->set_can_jump(true);
        character->set_is_falling(true);
    }
}

bool Game::has_player_reached_arena_end()
{
    return this->player->get_center().x + (this->player->get_trunk_width() * 1.2) / 2 >= this->background->get_center().x + this->background->get_width();
}

bool Game::has_player_won()
{
    if (this->has_game_reached_end_state())
    {
        if (!this->player->is_alive())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool Game::has_game_reached_end_state()
{
    if (this->player->is_alive() && this->has_player_reached_arena_end())
    {
        return true;
    }
    if (!this->player->is_alive())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::move_gunshots_character(Character *character, GLfloat frameTime)
{
    vector<Gunshot *> gunshots = character->get_gunshots();
    for (vector<Gunshot *>::iterator it = gunshots.begin(); it != gunshots.end(); ++it)
    {
        Gunshot *gunshot = *it;
        this->move_a_gunshot(character, gunshot, frameTime);
    }
}

void Game::move_a_gunshot(Character *shooter, Gunshot *gunshot, GLfloat frameTime)
{
    if (gunshot != NULL)
    {
        gunshot->move(frameTime);
        this->handle_collision_gunshot(shooter, gunshot);
    }
}

void Game::remove_character(Character *character)
{
    if (character == this->player)
    {
        this->player = nullptr;
    }
    else
    {
        for (size_t i = 0; i < this->enemies.size(); i++)
        {
            if (this->enemies[i] == character)
            {
                this->enemies.erase(this->enemies.begin() + i);
                break;
            }
        }
    }
}

void Game::handle_collision_gunshot(Character *shooter, Gunshot *gunshot)
{
    if (this->check_collision_gunshot_non_character(gunshot))
    {
        shooter->remove_gunshot(gunshot);
    }
    else
    {
        Character *hitCharacter = this->check_collision_gunshot_any_character(gunshot);

        if (hitCharacter != NULL && hitCharacter != shooter)
        {
            shooter->remove_gunshot(gunshot);
            cout << "Hit character " << hitCharacter->get_id() << endl;
            hitCharacter->set_alive(false);
            if (hitCharacter == this->player)
            {
                cout << "Player hit by a gunshot" << endl;
                return;
            }

            remove_character(hitCharacter);
        }
    }
}

Character *Game::check_collision_gunshot_any_character(Gunshot *gunshot)
{
    if (gunshot->is_inside_character(this->player))
    {
        return this->player;
    }
    else
    {
        for (Enemy *enemy : this->enemies)
        {
            if (gunshot->is_inside_character(enemy))
            {
                return enemy;
            }
        }
    }

    return NULL;
}

bool Game::check_collision_gunshot_non_character(Gunshot *gunshot)
{
    if (this->is_gunshot_outside_arena(gunshot) || this->is_gunshot_inside_any_terrain(gunshot))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Game::is_gunshot_outside_arena(Gunshot *gunshot)
{
    Terrain *arenaTerrain = this->background;
    Point arenaPos = this->background->get_center();

    if (gunshot->get_center().y - gunshot->get_radius() < arenaPos.y ||
        gunshot->get_center().y + gunshot->get_radius() > arenaPos.y + arenaTerrain->get_height())
    {
        return true;
    }

    if (gunshot->get_center().x - gunshot->get_radius() / 2 < arenaPos.x || gunshot->get_center().x + gunshot->get_radius() / 2 > arenaPos.x + arenaTerrain->get_width())
    {
        return true;
    }

    return false;
}

bool Game::is_gunshot_inside_any_terrain(Gunshot *gunshot)
{
    for (Terrain *terrain : this->terrains)
    {
        if (gunshot->is_inside_terrain(terrain))
        {
            return true;
        }
    }

    return false;
}

void Game::move_a_character(Character *character, GLfloat dx, GLfloat dy, GLfloat frameTime)
{
    character->move_character(dx, dy, frameTime);
    this->handle_collision(character, dx, dy, frameTime);
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

void Game::handle_collision(Character *character, GLfloat dx, GLfloat dy, GLfloat frameTime)
{
    if (this->check_collision(character))
    {
        character->move_character(-dx, -dy, frameTime);
    }
}

void Game::apply_gravity(GLfloat frameTime)
{
    // Player should be affected by gravity in a way that they reach the ground in 2 seconds after when standing 3 times their own height from the ground.
    // GLint MAX_JUMP_HEIGHT = this->player->get_height() * 3;
    // GLint MAX_JUMP_TIME = 2;
    // GLfloat gravityVelocity = MAX_JUMP_HEIGHT / frameTime / MAX_JUMP_TIME;
    // cout << "gravityVelocity: " << gravityVelocity << endl;
    // GLfloat gravityVelocity = MAX_JUMP_HEIGHT / MAX_JUMP_TIME;

    GLfloat gravityVelocity = this->player->get_radius() * 0.3 * INC_KEYIDLE;

    // Apply gravity to player
    this->move_a_character(this->player, 0, gravityVelocity, frameTime);

    // Apply gravity to enemies
    Enemy *currentEnemy = NULL;
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        currentEnemy = this->enemies[i];
        this->move_a_character(currentEnemy, 0, gravityVelocity, frameTime);
    }
}

bool Game::will_enemy_fall(Enemy *enemy, GLfloat dx, GLfloat frameTime)
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
        GLfloat newX = enemy->get_center().x + (dx * frameTime);
        if (newX <= terrainBelowEnemy->get_center().x ||
            newX >= terrainBelowEnemy->get_center().x + terrainBelowEnemy->get_width())
        {
            return true;
        }
    }

    return false;
}

void Game::move_enemy_randomly(Enemy *enemy, GLfloat frameTime)
{
    int integerFrameTime = (int)frameTime;

    int randomNumber = rand() % (integerFrameTime * 2);

    switch (randomNumber)
    {
    case 1:
        if (!will_enemy_fall(enemy, -INC_KEY, frameTime))
        {
            move_a_character(enemy, -INC_KEY, 0, frameTime);
        }
        else
        {
            // move_a_character(enemy, INC_KEY, 0, frameTime);
            // cout << enemy->get_id() << ": "
            //  << "would fall" << endl;
        }
        break;
    case 2:
        if (!will_enemy_fall(enemy, INC_KEY, frameTime))
        {
            move_a_character(enemy, INC_KEY, 0, frameTime);
        }
        else
        {
            // move_a_character(enemy, -INC_KEY, 0, frameTime);
            // cout << enemy->get_id() << ": "
            //  << "would fall" << endl;
        }
        break;
    default:
        break;
    }
}

void Game::enemy_shoot_at_player(Enemy *enemy, GLfloat frameTime)
{
    GLfloat enemyXViewDistance = this->get_arena_background()->get_height() * 0.4;
    GLfloat enemyYViewDistance = enemy->get_height() * 3;

    if (enemy->get_center().x - enemyXViewDistance < this->player->get_center().x &&
        enemy->get_center().x + enemyXViewDistance > this->player->get_center().x)
    {
        // cout << "Player is in view of enemy ID " << enemy->get_id() << endl;

        // Set enemy facing direction to player direction
        if (enemy->get_center().x < this->player->get_center().x)
        {
            enemy->set_facing_direction(Direction::RIGHT);
        }
        else
        {
            enemy->set_facing_direction(Direction::LEFT);
        }

        // cout << "Player y: " << this->player->get_center().y << "enemyYViewDistance: " << enemyYViewDistance << endl;
        // cout << "Enemy y: " << enemy->get_center().y << endl;

        if (this->player->get_center().y + enemyYViewDistance >= enemy->get_center().y && this->player->get_center().y - enemyYViewDistance <= enemy->get_center().y)
        {
            // cout << "Player is close to enemy ID " << enemy->get_id() << endl;
            enemy->set_visor_color(get_player_colors().upperBody);

            // Shoot at player at random intervals
            GLfloat randomNumber = rand() % (int)frameTime;
            if (randomNumber < frameTime * 0.005)
            {
                cout << "Enemy " << enemy->get_id() << " is shooting at player" << endl;
                enemy->shoot();
            }
        }
        else
        {
            enemy->set_visor_color(DEFAULT_VISOR_COLOR);
        }
    }
    else
    {
        enemy->set_visor_color(DEFAULT_VISOR_COLOR);
    }
}

void Game::enemies_shoot_at_player(GLfloat frameTime)
{
    if (!this->debugOptions.pacificEnemies)
    {
        for (size_t i = 0; i < this->enemies.size(); i++)
        {
            this->enemy_shoot_at_player(this->enemies[i], frameTime);
        }
    }
}

void Game::move_enemies_randomly(GLfloat frameTime)
{
    for (size_t i = 0; i < this->enemies.size(); i++)
    {
        this->move_enemy_randomly(this->enemies[i], frameTime);
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
    delete this->player;

    this->enemies.clear();
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
    Terrain *arenaTerrain = this->background;
    Point arenaPos = this->background->get_center();

    if (character->get_center().y - character->get_radius() < arenaPos.y ||
        character->get_center().y + character->get_radius() * 0.98 > arenaPos.y + arenaTerrain->get_height())
    {
        if (character->get_center().y >= arenaPos.y)
        {
            // cout << "collided with bottom of arena" << endl;
            character->set_is_falling(false);
            character->set_is_jumping(false);
            character->set_can_jump(true);
        }

        if (character->get_center().y <= arenaPos.y)
        {
            // cout << "collided with top of arena" << endl;
            character->set_is_falling(true);
            character->set_is_jumping(false);
            character->set_can_jump(false);
        }
        return true;
    }

    if (character->get_center().y + character->get_radius() > arenaPos.y + arenaTerrain->get_height())
    {
        character->set_terrain_below(this->get_arena_background());
    }

    if (character->get_center().x - character->get_trunk_width() / 2 < arenaPos.x || character->get_center().x + character->get_trunk_width() / 2 > arenaPos.x + arenaTerrain->get_width())
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
            if (this->debugOptions.highlightTerrain)
            {
                terrain->set_color(character->get_crewmate_colors().upperBody);
            }

            return true;
        }
        else
        {
            // if (this->debugOptions.highlightTerrain)
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

bool Game::get_debug_mode()
{
    return this->debugMode;
}

void Game::set_debug_mode(bool debugMode)
{
    this->debugMode = debugMode;
    set_debug_options(debugMode);
}

void Game::set_debug_options(bool debug)
{
    if (this->debugMode)
    {
        this->debugOptions.highlightTerrain = debug;
        this->debugOptions.pacificEnemies = debug;
        this->debugOptions.drawObjectCenter = debug;
        this->debugOptions.drawCharacterHitbox = debug;
        this->debugOptions.globalCamera = debug;
    }
}

Debug Game::get_debug_options()
{
    return this->debugOptions;
}

void Game::set_global_camera(bool globalCamera)
{
    if (this->debugMode)
    {
        this->debugOptions.globalCamera = globalCamera;
    }
}
