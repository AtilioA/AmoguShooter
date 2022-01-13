#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "include/enemy.hpp"
#include "include/player.hpp"
#include "include/character.hpp"
#include "include/svg_reader.hpp"

#define INC_KEY 1
#define INC_KEYIDLE 1

// Key status
int keyStatus[256];

// Window dimensions
// "será exibida em uma janela de 500x500 pixel do sistema operacional"
const GLint Width = 700;
const GLint Height = 700;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;

// Controla a animacao do robo
// int animate = 0;

// Componentes do mundo virtual sendo modelado
// Robo robo;
// Tiro *tiro = NULL; // Um tiro por vez
// Alvo alvo(0, 200); // Um alvo por vez

void renderScene(void)
{
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    parseSVGFile("input/arena_teste.svg");

    // glBegin(GL_QUADS);
    // glVertex2f(0, 0);
    // glVertex2f(200, 0);
    // glVertex2f(200, 50);
    // glVertex2f(0, 50);
    // glEnd();

    // robo.Draw();

    // if (tiro)
    // {
    //     tiro->Draw();
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
    case 'a':
    case 'A':
        keyStatus[(int)('a')] = 1; // Using keyStatus trick
        break;
    case 'd':
    case 'D':
        keyStatus[(int)('d')] = 1; // Using keyStatus trick
        break;
    case 'w':
    case 'W':
        // player.Jump();
        break;
    case ' ':
        // if (!tiro)
        // {
        //     // tiro = robo.Atira();
        // }
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
        keyStatus[i] = 0;
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    // glClearColor((GLfloat)r, (GLfloat)g, (GLfloat)b, 1);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Dark gray, no opacity(alpha).

    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity();
    // glOrtho(xlim1 / 2, xlim2 / 2, ylim1 / 2, ylim2 / 2, -100, 100);
    glOrtho(-(ViewingWidth / 2),  // X coordinate of left edge
            (ViewingWidth / 2),   // X coordinate of right edge
            -(ViewingHeight / 2), // Y coordinate of bottom edge
            (ViewingHeight / 2),  // Y coordinate of top edge
            -100,                 // Z coordinate of the “near” plane
            100);                 // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW);   // Select the projection matrix
    glLoadIdentity();
}

void idle(void)
{
    // double inc = INC_KEYIDLE;
    // // Treat keyPress
    // if (keyStatus[(int)('a')])
    // {
    //     robo.MoveEmX(-inc);
    // }
    // if (keyStatus[(int)('d')])
    // {
    //     robo.MoveEmX(inc);
    // }

    // // Trata o tiro (só permite um tiro por vez)
    // // Poderia usar uma lista para tratar varios tiros
    // if (tiro)
    // {
    //     tiro->Move();

    //     // Trata colisao
    //     if (alvo.Atingido(tiro))
    //     {
    //         alvo.Recria(rand() % 500 - 250, 200);
    //     }

    //     if (!tiro->Valido())
    //     {
    //         delete tiro;
    //         tiro = NULL;
    //     }
    // }

    // Control animation
    // if (animate)
    // {
    //     static int dir = 1;
    //     if (robo.ObtemX() > (ViewingWidth / 2))
    //     {
    //         dir *= -1;
    //     }
    //     else if (robo.ObtemX() < -(ViewingWidth / 2))
    //     {
    //         dir *= -1;
    //     }
    //     robo.MoveEmX(dir * INC_KEYIDLE);
    // }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
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

    init();

    glutMainLoop();

    return 0;
}
