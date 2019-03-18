
#include "Game.h"

using namespace std;

Game::Game(){

    //Background
    background = new Static("images/FinalBackground.png", -1, 1, 2, 2);

    //Tittle and Buttons
    title = new Title("images/PongniteFinal.png", 2, 1, -0.75, 0.75, 1.5, 0.5);
    onePlayerButton = new Button("images/FinalOnePlayer.png", -0.7, -0.3, 0.5, 0.5);
    twoPlayerButton = new Button("images/FinalTwoPlayer.png", 0.2, -0.3, 0.47, 0.47);

    //Padles
    Player_1 = new Paddle("images/Paddle1.png", -0.5, -0.8, 0.35,0.1);
    Player_2 = new Paddle("images/Paddle2.png", -0.5, 0.9, 0.35,0.1);

    //Ball
    ball = new Ball("images/ball.png", 0, 0.6, 0.1, 0.1);

    //Power_Ups
    Power_Up = new PowerUp("images/ship.png", 0, 0.15, 0.35, 0.12);

    //Display title again in game over
    gameOver = new Title("images/PongniteFinal.png", 2, 1, -0.75, 0.75, 1.5, 0.5);
    
    //Display who wins
    Player_1_Win = new Static("images/PlayerOneWin.png", -0.76, 0.2, 1.5, 1);
    Player_2_Win = new Static("images/PlayerTwoWin.png", -0.76, 0.2, 1.5, 1);

    
    
    //StartUP
    up = down = left = right = a = d = false;
    moving = false;
    game_over = false;
    startMenu = true;
    gamepause = false;
    
    //Score
    playerOneScore = '0';
    playerTwoScore = '0';
    
    //PowerUP
    bounces = 0; //Count bounces
    whoPower = 0;   //Someone has a powerUP and who
    Power_Up_left_start_x = -1 - Power_Up->w; //X-W to complete hide
    Power_Up_right_start_x = 1;
    started = false;
    
    s_ball_x = 0;
    s_ball_y = 0;
    s_ball_yinc = 0;
    s_ball_xinc = 0;
    s_ball_rising = NULL;
    s_playerOneScore = 'a';
    s_playerTwoScore = 'a';
    s_bounces = -1;
    s_whoPower = -1;
    s_usingPower = NULL;
    s_playerOne_x = 0;
    s_player_two_x = 0;
    s_powerUp_x = 0;
    saved = false;
    

}

void Game::draw (){

    if(startMenu){
        //Draw start menu
        background->draw();
        title->draw();
        onePlayerButton->draw();
        twoPlayerButton->draw();
    }else if(!game_over){
        //Draw game
        background->draw();
        Player_1->draw();
        Player_2->draw();
        ball->draw();
        drawScore(playerOneScore, '1', 11, -1, 0.93);
        drawScore(playerTwoScore, '2', 11, 0.65, 0.93);
        
        //Draw power up once in a while
        if (bounces > 2){
          Power_Up->draw();
        }
        
    }else{
        //Draw game over
        gameOver->draw();

        if(playerOneScore == '3'){
            Player_1_Win->draw();
        }else{
            Player_2_Win->draw();
        }
    }

}

void Game::animate(){
    ////Animates menu if its the beggining of a game////
    if(startMenu){
        title->animate();
        title->advance();
    }

    if (game_over){
        gameOver->advance();
    }

    if (moving){
        ball->jump();
        float bx = ball->x + ball->w/2;
        float by = ball->y - ball->h + 0.1;

        //If the ball hits player one paddle reverse
        if (Player_1->contains(bx, by-Player_1->h)){
            bounces++;
            ball->rising = true;
            ball->xinc = ball->yinc;
            //ball->yinc +=0.005;
            //makes ball faster (could be good for power ups)
            if (ball->yinc > 0.15){
                ball->yinc = 0.15;
            }
        }

        if (Player_2->contains(bx, by)){
            bounces++;
            ball->rising = false;
            ball->xinc = ball->yinc;
            //ball->yinc +=0.005;
            //makes ball faster (could be good for power ups)
            if (ball->yinc > 0.15){
                ball->yinc = 0.15;
            }
        }

        if(bounces == 2 && !usingPower){
          int iSecret = (rand() > RAND_MAX/2) ? 1 : 2;
            
            if(iSecret == 1){
                Power_Up->movingLeft = false;
            }else{
                Power_Up->movingLeft = true;
            }
          
          //Start Right
          if(Power_Up->movingLeft == true && started == false){
            Power_Up->x = Power_Up_right_start_x;
            started = true;
          }
          //Start Left
          else if(Power_Up->movingLeft == false && started == false){
            Power_Up->x = Power_Up_left_start_x;
            started = true;
          }
            
        }
        
        if(bounces > 2 && !gamepause) {

          //Mover Right
          if(Power_Up->movingLeft == false){
            Power_Up->moveRight(0.01 , true);
              if(Power_Up->x > 0.99){
                  bounces = 0;
                  started = false;
              }
          }
          //Move Left
          else{
            Power_Up->moveLeft(0.01, true);
              if(Power_Up->x < -1.0 - Power_Up->w){
                  bounces = 0;
                  started = false;
              }
             
          }

          //Make it dissapear
            if(Power_Up->contains(ball->x, ball->y)){
                usingPower = true;
                if(ball->rising){
                    whoPower = 1;
                    
                }else{
                    whoPower = 2;
                }
                
                bounces = 0;
                started = false;
          }

        }
        
        if(bounces == 3 && usingPower){
            usingPower = false;
            whoPower = 0;
            bounces = 0;
        }



     //////Boundaries to add score and reset ball position/////
        if (ball->y - ball->h < -0.99){
            ball->x = 0;
            ball->y = 0.6;
            ball->rising = false;
            playerTwoScore++;
        }

        if (ball->y > 0.99){
            ball->x = 0;
            ball->y = -0.6;
            ball->rising = true;
            playerOneScore++;
        }

    //////End Game if one of the scores are greater than or equal to 3/////
            if(playerOneScore == '3'){
                game_over = true;
                moving = false;
                gameOver->animate();
            }

            if(playerTwoScore == '3'){
                game_over = true;
                moving = false;
                gameOver->animate();
            }
        }


    ///////////Game Keys that interact with objects////////////
    if(whoPower == 0){
        Player_2->botSpeed = 0.0173;
        if (left){
            Player_1->moveLeft(0.05);
        }
        if (right){
            Player_1->moveRight(0.05);
        }
        
        if (a){
            Player_2->moveLeft(0.05);
        }
        if (d){
            Player_2->moveRight(0.05);
        }
    }
    
    if(whoPower == 1){
        Player_2->botSpeed = 0.017 - 0.005;
        
        if (left){
            Player_1->moveLeft(0.05);
        }
        if (right){
            Player_1->moveRight(0.05);
        }
        
        if (a){
            Player_2->moveLeft(0.015);
        }
        if (d){
            Player_2->moveRight(0.015);
        }
    }
    
    if(whoPower == 2){
        Player_2->botSpeed = 0.0173;
        
        if (left){
            Player_1->moveLeft(0.015);
        }
        if (right){
            Player_1->moveRight(0.015);
        }
        
        if (a){
            Player_2->moveLeft(0.02);
        }
        if (d){
            Player_2->moveRight(0.02);
        }
    }
    
    if(playerMode == 1){
        if(ball->rising && !gamepause){
            Player_2->bot(ball->xCenter());
        }
    }


}

    void Game::clickControl(float x, float y){
        if(onePlayerButton->contains(x, y)){
            ball->x = 0;
            ball->y = 0;
            ball->yinc = 0.018;
            ball->xinc = 0.018;
            ball->rising = false;
            game_over = false;
            title->stop();
            moving = true;
            playerMode = 1;
            startMenu = false;
        }

        if(twoPlayerButton->contains(x, y)){
            ball->x = 0;
            ball->y = 0.6;
            ball->yinc = 0.018;
            ball->xinc = 0.018;
            ball->rising = false;
            game_over = false;
            title->stop();
            moving = true;
            playerMode = 2;
            startMenu = false;
        }

    }

void Game::specialKeyPress(int key){
    if (!game_over && !gamepause){
        if (key == 100){
            left = true;
        }
        if (key == 101){
            //up = true;
        }
        if (key == 102){
            right = true;
        }
        if (key == 103){
            //down = true;
        }
    }

}

void Game::specialKeyUp(int key){
    if (key == 100) {
        left = false;
    }
    if (key == 101) {
        // up = false;
    }
    if (key == 102) {
        right = false;
    }
    if (key == 103) {
        //down = false;
    }
}



void Game::keyPress(unsigned char key){
    
    //Reset
    if(key == ' '){
        reset();
    }
    
    if(key == 'p'){
        if(gamepause == false){
            gamepause = true;
        }else{
            gamepause = false;
        }
        pause();
    }
    
    if(key == 's'){
        save();
    }
    
    if(key == 'l' && saved){
        load();
    }

    //Second player controls
    if(playerMode == 2 && !gamepause){
        if(key == 'a'){
            a = true;
        }

        if(key == 'd'){
            d = true;
        }
    }
}
void Game::keyUp(unsigned char key){
    //Release action with these keys
    if(key == 'a'){
        a = false;
    }

    if(key == 'd'){
        d = false;
    }
}

void Game::drawScore(char score, char player, int length, float x , float y){
    vector<char> text;
    
    text.push_back('P');
    text.push_back('l');
    text.push_back('a');
    text.push_back('y');
    text.push_back('e');
    text.push_back('r');
    text.push_back(' ');
    text.push_back(player);
    text.push_back(':');
    text.push_back(' ');
    text.push_back(score);
    glColor3f(1.0,1.0,1.0);
    glRasterPos2f(x, y);
    for (unsigned int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , text[i]) ;
    }
    
}

void Game::pause(){
    if(gamepause == true){
        ball->yinc = 0;
        ball->xinc = 0;
    }else{
        ball->yinc = 0.02;
        ball->xinc = 0.02;
    }
}

void Game::save(){
    s_ball_x = this->ball->x;
    s_ball_y = this->ball->y;
    s_ball_yinc = this->ball->yinc;
    s_ball_xinc = this->ball->xinc;
    s_ball_rising = this->ball->rising;
    s_playerOneScore = this->playerOneScore;
    s_playerTwoScore = this->playerTwoScore;
    s_bounces = this->bounces;
    s_whoPower = this->whoPower;
    s_usingPower = this->usingPower;
    s_playerOne_x = this->Player_1->x;
    s_player_two_x = this->Player_2->x;
    s_powerUp_x = this->Power_Up->x;
    s_ball_movingLeft = this->ball->movingLeft;
    
    saved = true;
}

void Game::load(){
    this->ball->x = s_ball_x;
    this->ball->y = s_ball_y;
    this->ball->yinc = s_ball_yinc;
    this->ball->xinc = s_ball_xinc;
    this->ball->rising = s_ball_rising;
    this->playerOneScore = s_playerOneScore;
    this->playerTwoScore = s_playerTwoScore;
    this->title->stop();
    this->startMenu = false;
    this->moving = true;
    this->game_over = false;
    this->bounces = s_bounces;
    this->whoPower = s_whoPower;
    this->usingPower = s_usingPower;
    this->Player_1->x = s_playerOne_x;
    this->Player_2->x = s_player_two_x;
    this->Power_Up->x = s_powerUp_x;
    this->ball->movingLeft = s_ball_movingLeft;
}

void Game::reset(){
    ball->x = 0;
    ball->y = 0.6;
    ball->yinc = 0.02;
    ball->xinc = 0.02;
    ball->rising = false;
    game_over = false;
    playerOneScore = '0';
    playerTwoScore = '0';
    title->stop();
    moving = false;
    startMenu = true;
    bounces = 0;
    whoPower = 0;
    usingPower = false;
}

Game::~Game(){

    delete title;
    delete gameOver;
    delete background;
    delete onePlayerButton;
    delete twoPlayerButton;
    delete ball;
    delete Player_1;
    delete Player_2;

}
