
#ifndef Static_h
#define Static_h

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

class Static {
public:
    float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    
    Static(const char*, float, float, float, float);
    
    void draw();
    
};



#endif /* Background_h */
