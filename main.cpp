#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "include/game.hpp"
#include "include/svg_reader.hpp"
#include "include/utils.hpp"

using namespace std;

#define INC_KEY 0.5
#define INC_KEYIDLE 0.5

// Key status
int keyStatus[256];

static char str[999];

// Window dimensions
// "será exibida em uma janela de 500x500 pixel do sistema operacional"
const GLint Width = 500;
const GLint Height = 500;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

static bool shouldPreserveFramerateSpeed = true;
static GLdouble framerate = 0;
Game *game = new Game();

void RenderString(float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(game->get_player()->get_center().x, -game->get_arena_background()->get_center().y - game->get_arena_background()->get_height() / 2);

    if (game->has_player_won())
    {
        sprintf(str, "VITORIA!");
        cout << "VITÓRIA" << endl;
    }
    else
    {
        sprintf(str, "GAME OVER!");
        cout << "GAME OVER" << endl;
    }
    char *text;
    text = str;
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *text);
        text++;
    }
}

void renderScene()
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    // cout << "\nDrawing game elements:" << endl;
    // cout << "Drawing background... ";
    game->get_arena_background()->draw_terrain();
    // cout << "Drawing terrains... ";
    game->draw_terrains();
    // cout << "Drawing player... ";
    game->draw_player();
    // cout << "Drawing enemies..." << endl;
    game->draw_enemies();
    // cout << "Finished drawing game elements." << endl;
    if (game->get_player()->get_gunshot() != NULL)
    {
        game->get_player()->get_gunshot()->draw();
    }
    for (size_t i = 0; i < game->get_enemies().size(); i++)
    {
        if (game->get_enemies()[i]->get_gunshot() != NULL)
        {
            game->get_enemies()[i]->get_gunshot()->draw();
        }
    }

    if (game->has_game_reached_end_state())
    {
        cout << "Game has reached end state!" << endl;
        RenderString(0, 0);
    }

    glutSwapBuffers(); // Draw the new frame of the game.
    glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        // animate = !animate;
        break;
    case 'w':
    case 'W':
        // player.jump();
        keyStatus[(int)('w')] = 1; // Using keyStatus trick
        break;
    case 'a':
    case 'A':
        keyStatus[(int)('a')] = 1; // Using keyStatus trick
        break;
    case 's':
    case 'S':
        keyStatus[(int)('s')] = 1; // Using keyStatus trick
        break;
    case 'd':
    case 'D':
        keyStatus[(int)('d')] = 1; // Using keyStatus trick
        break;
    case 'r':
    case 'R':
        keyStatus[(int)('r')] = 1; // Using keyStatus trick
        break;
    case 'f':
    case 'F':
        game->get_player()->shoot();
        break;
    case '2':
        game->get_debug_options().drawCharacterHitbox ? game->set_debug_options(false) : game->set_debug_options(true);
        break;
    case 27:
        exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i = 0;

    // Initialize keyStatus
    for (i = 0; i < 256; i++)
    {
        keyStatus[i] = 0;
    }
}

void init(Game *game)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    // glClearColor((GLfloat)r, (GLfloat)g, (GLfloat)b, 1);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray, no opacity(alpha).

    cout << "\nArena width: " << game->get_arena_dimensions().width << ", height: " << game->get_arena_dimensions().height << endl;
    GLfloat smallestArenaDimension = smallest_dimension(game->get_arena_dimensions());
    cout << "Smallest arena dimension: " << smallestArenaDimension << endl;

    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity();
    glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
            (ViewingWidth / 2),   // X coordinate of right edge
            -(ViewingHeight / 2), // Y coordinate of bottom edge
            (ViewingHeight / 2),  // Y coordinate of top edge
            -100,                 // Z coordinate of the “near” plane
            100);                 // Z coordinate of the “far” plane

    glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    glLoadIdentity();
}

void idle(void)
{
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;

    // cout << "Framerate: " << (int)framerate << endl;
    // cout << "deltaTime: " << deltaTime << endl;

    if (keyStatus['r'] == 1 || keyStatus['R'] == 1)
    {
        // cout << "Parsing " << game->get_arena_svg_filename() << endl;
        game->reset_game();
    }

    if (!shouldPreserveFramerateSpeed)
    {
        deltaTime = 1;
    }

    Player *player = game->get_player();

    if (!game->get_debug_options().globalCamera)
    {
        glMatrixMode(GL_PROJECTION); // Select the projection matrix
        glLoadIdentity();
        glOrtho(-game->get_arena_background()->get_height() / 2 + player->get_center().x,                     // X coordinate of left edge
                game->get_arena_background()->get_height() / 2 + player->get_center().x,                      // X coordinate of right edge
                (-game->get_arena_background()->get_center().y - game->get_arena_background()->get_height()), // Y coordinate of bottom edge
                -game->get_arena_background()->get_center().y,                                                // Y coordinate of top edge
                -1,                                                                                           // Z coordinate of the “near” plane
                1);                                                                                           // Z coordinate of the “far” plane
        glMatrixMode(GL_MODELVIEW);                                                                           // Select the projection matrix
    }
    else
    {
        glMatrixMode(GL_PROJECTION); // Select the projection matrix
        glLoadIdentity();
        glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
                (ViewingWidth / 2),   // X coordinate of right edge
                -(ViewingHeight / 2), // Y coordinate of bottom edge
                (ViewingHeight / 2),  // Y coordinate of top edge
                -100,                 // Z coordinate of the “near” plane
                100);                 // Z coordinate of the “far” plane

        glMatrixMode(GL_MODELVIEW); // Select the projection matrix
        glLoadIdentity();
    }

    if (game->has_game_reached_end_state())
    {
        cout << "Game ended!" << endl;

        if (!player->is_alive())
        {
            cout << "Player is dead!" << endl;
        }
        else
        {
            cout << "Player won!" << endl;
        }
    }
    else
    {
        game->move_enemies_randomly(framerate);
        game->enemies_shoot_at_player(framerate);

        double inc = INC_KEYIDLE;
        GLfloat dx = 0, dy = 0;

        // Treat keyPress
        if (keyStatus['d'] == 1 || keyStatus['D'] == 1)
        {
            dx += inc;
            game->move_a_character(player, dx, dy);
        }
        if (keyStatus['a'] == 1 || keyStatus['A'] == 1)
        {
            dx -= inc;
            game->move_a_character(player, dx, dy);
        }
        if (keyStatus['w'] == 1 || keyStatus['W'] == 1)
        {
            dy -= inc;
            game->move_a_character(player, dx, dy * 2);
        }
        if (keyStatus['s'] == 1 || keyStatus['S'] == 1)
        {
            dy += inc;
            game->move_a_character(player, dx, dy * 2);
        }

        game->apply_gravity(deltaTime);

        // Handle gunshot (only allows one gunshot at a time)
        // Could use a list to handle multiple gunshots
        Gunshot *playerGunshot = player->get_gunshot();
        if (playerGunshot != NULL)
        {
            // cout << "Moving gunshot..." << endl;
            game->move_a_gunshot(player, framerate);
        }

        for (auto &enemy : game->get_enemies())
        {
            if (enemy->get_gunshot() != NULL)
            {
                game->move_a_gunshot(enemy, framerate);
            }
        }
    }
    glutPostRedisplay();
}

void aim_with_mouse(int x, int y)
{
    // x = ViewingHeight - x;
    y = ViewingHeight - y;
    game->get_player()->moveArmMouseHelper(x, y);
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    if (argc < 2)
    {
        printf("Usage: %s <svg file>\n", argv[0]);
        exit(1);
    }
    string arena_filename = argv[1];

    // Check if third argv argument is -d (for debug), set debug flag
    bool debug = false;
    if (argc >= 3 && strcmp(argv[2], "-d") == 0)
    {
        debug = true;
    }
    game->set_debug_options(debug);

    // Generate seed for random enemy activity
    srand(time(NULL));

    cout << "Parsing SVG file..." << endl;
    parseSVGFile(arena_filename, game);
    cout << "Finished parsing SVG file." << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("Trabalho 2D");

    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(aim_with_mouse);

    init(game);

    glutMainLoop();

    return 0;
}
