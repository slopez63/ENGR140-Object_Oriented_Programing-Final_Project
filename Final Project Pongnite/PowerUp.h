
#ifndef PowerUp_h
#define PowerUp_h

#include <stdio.h>

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

class PowerUp {
public:
    float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    
    
    PowerUp (const char*, float, float, float, float);
    
    void draw();
    
    bool contains(float, float);
    
    void moveUp(float rate=0.1);
    void moveDown(float rate=0.1);
    void moveLeft(float rate=0.1, bool free = false);
    void moveRight(float rate=0.1, bool free = false);
    
    bool movingLeft;
    
    float translate;
    
};

#endif /* PowerUp_h */
