
#ifndef Paddle_h
#define Paddle_h

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

class Paddle {
public:
    float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    
    
    Paddle(const char*, float, float, float, float);
    
    void draw();
    
    bool contains(float, float);
    
    void moveUp(float rate=0.1);
    void moveDown(float rate=0.1);
    void moveLeft(float rate=0.1, bool free = false);
    void moveRight(float rate=0.1, bool free = false);
    float xCenter();
    void bot(float x);
    
    bool movingLeft;
    
    float xinc, yinc, translate, botSpeed;
    
};

#endif /* Paddle_h */
