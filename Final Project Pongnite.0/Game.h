#include "Paddle.h"
#include "Static.h"
#include "Title.h"
#include "Ball.h"
#include "PowerUp.h"
#include "Button.h"

#include<iostream>
#include "GlutApp.h"

#include <stdio.h>
#include <ranlib.h>
#include <vector>

#ifndef Logic_h
#define Logic_h

class Game{

public:

    Game();
    void draw();
    void drawScore(char score,char player, int length, float x , float y);
    void animate();
    void clickControl(float x, float y);
    void specialKeyPress(int x);
    void specialKeyUp(int x);
    void keyPress(unsigned char key);
    void keyUp(unsigned char key);
    void pause();
    void save();
    void load();
    void reset();
    ~Game();

    bool game_over, up, down, left, right, a, d, moving, startMenu, gamepause, started, usingPower;
    int playerMode, bounces, whoPower;
    float Power_Up_left_start_x, Power_Up_right_start_x;
    char playerOneScore, playerTwoScore;
    
    Title* title;
    Title* gameOver;
    Static* background;
    Button* onePlayerButton;
    Button* twoPlayerButton;
    Ball* ball;
    Paddle* Player_1;
    Paddle* Player_2;
    Static* Player_1_Win;
    Static* Player_2_Win;
    PowerUp* Power_Up;
    
    float s_ball_x, s_ball_y, s_ball_yinc, s_ball_xinc, s_playerOne_x, s_player_two_x, s_powerUp_x;
    bool s_ball_rising, s_usingPower, s_ball_movingLeft, saved;
    char s_playerOneScore, s_playerTwoScore;
    int s_bounces, s_whoPower;
    
    
};

#endif
