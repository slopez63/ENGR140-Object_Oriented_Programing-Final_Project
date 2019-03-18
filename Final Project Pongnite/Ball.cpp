
#include "Ball.h"

Ball::Ball (const char* filename, float x=0, float y=0, float w=0.5, float h=0.5){
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    
    texture_id = SOIL_load_OGL_texture (
                                        filename,
                                        SOIL_LOAD_AUTO,
                                        SOIL_CREATE_NEW_ID,
                                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                                        );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    rising = false;
    
    
    xinc = 0;
    yinc = 0;
    translate = 0;
}

void Ball::moveUp(float rate){
    y += rate;
}
void Ball::moveDown(float rate){
    y -= rate;
}
void Ball::moveLeft(float rate, bool free){
    x -= rate;
    if (x < -0.99 && !free){
        x = -0.99;
    }
}
void Ball::moveRight(float rate, bool free){
    x += rate;
    if (x + w > 0.99 && !free){
        x = 0.99 - w;
    }
}

void Ball::jump(){
    if(rising){
        y+=yinc;
        if (movingLeft){
            x -=xinc;
        }
        else {
            x +=xinc;
        }
    }
    else {
        y-=yinc;
        if (movingLeft){
            x -=xinc;
        }
        else{
            x +=xinc;
        }
    }
    
    if (y > 0.99){
        rising = false;
    }
    if ((y-h) < -0.99){
        rising = true;
    }
    if (x < -0.99) {
        movingLeft = false;
        
    }
    if (x+w > 0.99) {
        movingLeft = true;
        
    }
}


void Ball::draw(){
    glBindTexture( GL_TEXTURE_2D, texture_id );
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(x, y - h);
    
    glTexCoord2f(0, 1);
    glVertex2f(x, y);
    
    glTexCoord2f(1, 1);
    glVertex2f(x+w, y);
    
    glTexCoord2f(1, 0);
    glVertex2f(x+w, y - h);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}



float Ball::xCenter(){
    return x;
}

