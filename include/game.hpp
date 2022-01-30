#ifndef GAME_H_
#define GAME_H_

#include <bits/stdc++.h>
#include "gunshot.hpp"
#include "utils.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "terrain.hpp"

using namespace std;

#define MOUSE_SENSITIVITY 1.2

typedef struct tDebug
{
    bool highlightTerrain;
    bool pacificEnemies;
    bool drawObjectCenter;
    bool drawCharacterHitbox;
    bool globalCamera;
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
    bool debugMode;
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
        this->debugMode = false;
        this->debugOptions = {false, false, false, false, false};
    };

    bool has_player_won();
    bool has_player_reached_arena_end();
    bool has_game_reached_end_state();

    void make_a_character_jump(Character *character, GLfloat frameTime);

    void move_gunshots_character(Character *character, GLfloat frameTime);
    void move_a_gunshot(Character *shooter, Gunshot *gunshot, GLfloat frameTime);

    void handle_collision_gunshot(Character *shooter, Gunshot *gunshot);
    bool check_collision_gunshot_non_character(Gunshot *gunshot);
    bool is_gunshot_outside_arena(Gunshot *gunshot);
    bool is_gunshot_inside_any_terrain(Gunshot *gunshot);
    Character *check_collision_gunshot_any_character(Gunshot *gunshot);
    void remove_character(Character *character);

    void move_a_character(Character *character, GLfloat dx, GLfloat dy, GLfloat frameTime);
    bool check_collision(Character *character);
    void handle_collision(Character *character, GLfloat dx, GLfloat dy, GLfloat frameTime);

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

    void apply_gravity(GLfloat frameTime);

    bool will_enemy_fall(Enemy *enemy, GLfloat dx, GLfloat frameTime);
    void enemies_shoot_at_player(GLfloat frameTime);
    void enemy_shoot_at_player(Enemy *enemy, GLfloat frameTime);
    void move_enemy_randomly(Enemy *enemy, GLfloat frameTime);
    void move_enemies_randomly(GLfloat frameTime);

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

    bool get_debug_mode();
    void set_debug_mode(bool debugMode);
    void set_debug_options(bool debug);
    Debug get_debug_options();
    void set_global_camera(bool globalCamera);
};

#endif /* GAME_H_ */
