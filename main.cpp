#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>


#include "map.h"
#include "unit.h"
Map M;
Unit U;
bool keysPressed[4];

class screen{
public:
    static const int width  = 640;
    static const int height = 480;
};

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    static float  x = 0;
//    glViewport(0,0,640,480);
//    x -= 0.01;
//    glTranslatef(-1.0f,-31.0f,0.0f);
    M.draw();
    U.draw();
    /*
    glLoadIdentity();
    glOrtho(0.0f, screen::width, screen::height, 0.0f, -1.0f, 1.0f);
    gluLookAt(1.0,0.0,1.0,  // eye
              0.0,1.0,0.0,  // center
              1.0,1.0,5.0); // up
    */
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int){
    switch (key){
        case 'a':
        case 'A':
            keysPressed[Unit::Right]= false;
            keysPressed[Unit::Left] = true;
            break;
        case 'd':
        case 'D':
            keysPressed[Unit::Left] = false;
            keysPressed[Unit::Right]= true;
            break;
        case 'w':
        case 'W':
        case  32:
            keysPressed[Unit::Down] = false;
            keysPressed[Unit::Up]   = true;
            break;
        case 's':
        case 'S':
            keysPressed[Unit::Up]   = false;
            keysPressed[Unit::Down] = true;
            break;
        case 27:
            exit(0);
    }
}

void keyboardup(unsigned char key, int, int){
    switch (key){
        case 'a':
        case 'A':
            keysPressed[Unit::Left] = false;
            break;
        case 'd':
        case 'D':
            keysPressed[Unit::Right]= false;
            break;
        case 'w':
        case 'W':
        case  32:
            keysPressed[Unit::Up]   = false;
            break;
        case 's':
        case 'S':
            keysPressed[Unit::Down] = false;
            break;
    }
}


void timer(int = 0){
    display();
    U.update();
    if(keysPressed[Unit::Left]) U.move(Unit::Left);
    if(keysPressed[Unit::Right])U.move(Unit::Right);
    if(keysPressed[Unit::Up])   U.move(Unit::Up);
    if(keysPressed[Unit::Down]) U.move(Unit::Down);
    if(!keysPressed[Unit::Left] && !keysPressed[Unit::Right])
        U.stop();
    glutTimerFunc(100, timer, 0);
}

int main(int argc, char **argv){

    glutInit(&argc, argv);
//    alutInit(&argc, argv);
//    InitializeOpenAL();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screen::width, screen::height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mario");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, screen::width, screen::height, 0.0f, -1.0f, 1.0f); // От верхнего левого угла (0,0)(left,right,bottom,top,z,z)
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardup);
    glEnable(GL_ALPHA_TEST);        // Включаем прозрачность
    glAlphaFunc(GL_GREATER,0.0);    // - * -
//    glEnable (GL_BLEND);          // В источнике указаны ещё 2 функции, но прозрачность прекрасно работает и без них.
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cerr << "Map TileSet: ";
    M.loadTileSet("TileSet.tga");
    std::cerr << "Unit Sprites: ";
    U.loadSprite("Sprites.tga");
    M.tmpInitMap();
    U.assignMap(&M);
    timer();
    glutMainLoop();
//    alutExit();
//    DestroyOpenAL();
    return 0;
}
