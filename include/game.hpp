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
    bool highlightTerrain;
    bool pacificEnemies;
    bool drawObjectCenter;
    bool drawCharacterHitbox;
} Debug;

class Game
{
private:
    Player *player;
    vector<Enemy *> enemies;
    vector<Terrain *> terrains;
    Terrain *background;
    GLint nCharacters;
    string arenaSVGFilename;
    Dimensions arenaDimensions;
    Debug debugOptions;

public:
    Game()
    {
        this->player = NULL;
        this->enemies = vector<Enemy *>();
        this->terrains = vector<Terrain *>();
        this->background = NULL;
        this->nCharacters = 0;
        this->arenaSVGFilename = "";
        this->arenaDimensions = {0, 0};
        this->debugOptions = {false, false, false, false};
    };

    bool has_player_reached_arena_end();
    bool has_game_reached_end_state();

    void move_a_gunshot(Character *shooter, GLfloat deltaTime);

    void handle_collision_gunshot(Character *shooter);
    bool check_collision_gunshot_non_character(Gunshot *gunshot);
    bool is_gunshot_outside_arena(Gunshot *gunshot);
    bool is_gunshot_inside_any_terrain(Gunshot *gunshot);
    Character *check_collision_gunshot_any_character(Gunshot *gunshot);
    void remove_character(Character *character);

    void move_a_character(Character *character, GLfloat dx, GLfloat dy);
    bool check_collision(Character *character);
    void handle_collision(Character *character, GLfloat dx, GLfloat dy);

    void add_enemy(Enemy *enemy);
    std::vector<Enemy *> get_enemies();
    void draw_enemies();

    void free_terrains();
    void free_enemies();
    void free();
    void reset_game();

    bool is_character_inside_any_other_character(Character *character);
    bool is_outside_arena(Character *character);
    bool is_character_inside_any_terrain(Character *character);
    bool is_player_inside_any_enemy();
    bool is_player_inside_any_terrain();

    void apply_gravity(GLfloat deltaTime);

    bool will_enemy_fall(Enemy *enemy, GLfloat dx);
    void enemies_shoot_at_player(GLfloat deltaTime);
    void enemy_shoot_at_player(Enemy *enemy, GLfloat deltaTime);
    void move_enemy_randomly(Enemy *enemy, GLfloat deltaTime);
    void move_enemies_randomly(GLfloat deltaTime);

    void add_player(Player *player);
    Player *get_player();
    void draw_player();

    void add_terrain(Terrain *terrain);
    std::vector<Terrain *> get_terrains();
    void draw_terrains();

    void set_arena_background(Terrain *background);
    Terrain *get_arena_background();

    GLint get_n_characters();

    void set_arena_svg_filename(string arenaSVGFilename);
    string get_arena_svg_filename();

    void set_arena_dimensions(Dimensions arenaDimensions);
    Dimensions get_arena_dimensions();

    void set_debug_options(bool debug);
    Debug get_debug_options();
};

#endif /* GAME_H_ */
