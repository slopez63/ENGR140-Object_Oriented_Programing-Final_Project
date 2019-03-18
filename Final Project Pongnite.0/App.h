#ifndef App_hpp
#define App_hpp
//
#include "GlutApp.h"
//
#include "Game.h"


using namespace std;

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;

public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
     
    
    // These are the events we want to handle
    void draw();
    void mouseDown(float x, float y);
    void idle();
    void specialKeyPress(int key);
    void specialKeyUp(int key);
    void keyPress(unsigned char key);
    void keyUp(unsigned char key);
    
    Game* game;
    
};

#endif
