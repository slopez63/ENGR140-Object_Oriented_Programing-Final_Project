
#include "Paddle.h"


Paddle::Paddle (const char* filename, float x=0, float y=0, float w=0.5, float h=0.5){
    
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
    
    botSpeed = 0.0173;;
    
    xinc = 0;
    yinc = 0;
    translate = 0;
}

void Paddle::moveUp(float rate){
    y += rate;
}
void Paddle::moveDown(float rate){
    y -= rate;
}
void Paddle::moveLeft(float rate, bool free){
    x -= rate;
    if (x < -0.99 && !free){
        x = -0.99;
    }
}
void Paddle::moveRight(float rate, bool free){
    x += rate;
    if (x + w > 0.99 && !free){
        x = 0.99 - w;
    }
}

void Paddle::draw(){
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


bool Paddle::contains(float mx, float my){
    return mx >= x && mx <= x+w && my <= y && my >= y - h;
}

float Paddle::xCenter(){
    return x;
}

void Paddle::bot(float ballCenter){
    if(x > -1 && x < 1-w){
        if(x > ballCenter){
            x += +botSpeed * -1;
        }
        else if(x < ballCenter){
            x += -botSpeed * -1;
        }
        else{
            x += 0.0;
        }
    }else{
        if(x > 1-w){
            x += -0.01;
        }
        if(x < -1){
            x += +0.01;
        }
    }
}


