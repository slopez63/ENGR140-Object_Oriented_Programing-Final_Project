
#ifndef Button_h
#define Button_h

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

class Button {
public:
    float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    
    
    Button (const char*, float, float, float, float);
    
    void draw();
    
    bool contains(float, float);
    
};

#endif /* Button_h */
