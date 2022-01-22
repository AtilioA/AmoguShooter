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

#define INC_KEY 1
#define INC_KEYIDLE 1

// Key status
int keyStatus[256];

// Window dimensions
// "será exibida em uma janela de 500x500 pixel do sistema operacional"
const GLint Width = 500;
const GLint Height = 500;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

// Controla a animacao do robo
// int animate = 0;

// Componentes do mundo virtual sendo modelado
// Gunshot *gunshot = NULL; // One gunshot at a time
// Alvo alvo(0, 200); // Um alvo por vez

static bool shouldPreserveFramerateSpeed = true;
static GLdouble framerate = 0;
Game *game = new Game();

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

    // glBegin(GL_QUADS);
    // glVertex2f(0, 0);
    // glVertex2f(200, 0);
    // glVertex2f(200, 50);
    // glVertex2f(0, 50);
    // glEnd();

    // robo.Draw();

    // if (gunshot)
    // {
    //     gunshot->draw();
    // }

    glutSwapBuffers(); // Draw the new frame of the game.
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

    if (!shouldPreserveFramerateSpeed)
    {
        deltaTime = 1;
    }

    Player *player = game->get_player();

    game->move_enemies_randomly(framerate);

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
        game->move_a_character(player, dx, dy);
    }
    if (keyStatus['s'] == 1 || keyStatus['S'] == 1)
    {
        dy += inc;
        game->move_a_character(player, dx, dy);
    }

    game->apply_gravity(deltaTime);

    // Handle gunshot (only allows one gunshot at a time)
    // Could use a list to handle multiple gunshots
    Gunshot *playerGunshot = player->get_gunshot();
    if (playerGunshot != NULL)
    {
        // cout << "Moving gunshot..." << endl;
        playerGunshot->move(framerate);

        // // Trata colisao
        // if (alvo.Atingido(playerGunshot))
        // {
        //     alvo.Recria(rand() % 500 - 250, 200);
        // }

        if (!playerGunshot->is_valid())
        {
            player->delete_gunshot();
        }
    }
    else
    {
        // cout << "playerGunshot is NULL" << endl;
    }

    if (keyStatus['r'] == 1 || keyStatus['R'] == 1)
    {
        // cout << "Parsing " << game->get_arena_svg_filename() << endl;
        game->reset_game();
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
