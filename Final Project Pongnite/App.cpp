#pragma once
#include "App.h"
//
using namespace std;

static App* singleton;

void app_timer(int value){
    singleton->game->animate();
    
    ///////////Animating objects////////////
    ////game Over/////
    if (singleton->game->game_over){
        singleton->redraw();
        glutTimerFunc(300, app_timer, value);
    }
    else{
        ////Start Title/////
        if (singleton->game->startMenu){
            singleton->redraw();
            glutTimerFunc(300, app_timer, value);
        }
        ////Ball and Paddles/////
        if (singleton->game->up || singleton->game->down || singleton->game->left || singleton->game->right || singleton->game->moving && !singleton->game->game_over){
            singleton->redraw();
            glutTimerFunc(16, app_timer, value);
        }
    }
}


App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    
    singleton = this;
    
    game = new Game();
    
    app_timer(1);
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set Color
    glColor3d(1.0, 1.0, 1.0);


    //////////////////////////////////////////////////
    
    game->draw();
    
    /////////////////////////////////////////////////
    
    glFlush();
    glutSwapBuffers();
}
void App::mouseDown(float x, float y){
    mx = x;
    my = y;
    
    game->clickControl(x, y);
}

void App::idle(){
}

void App::specialKeyPress(int key){
    game->specialKeyPress(key);
}

void App::specialKeyUp(int key){
    game->specialKeyUp(key);
}

void App::keyPress(unsigned char key) {
    //Exit with esc
    if (key == 27){
        
        delete game;
        delete this;
        exit(0);
    }
    
    game->keyPress(key);
}

void App::keyUp(unsigned char key) {
    game->keyUp(key);
}
