// 8x8 LED Matrix Breakout game
//
// For more info about this project (drawings, schematics, explanetations etc.), please visit my blog http://makertech.dk
// 
// * use at own risk *
//
// Author: Signe Colding-Jørgensen
// Maker Tech
// blog: http://makertech.dk
// facebook: https://www.facebook.com/makertechdk/
// instagram: https://www.instagram.com/makertech_dk/
// youtube: https://www.youtube.com/channel/UCZfXxUfpS7q-v1gsMY-hQtA
// twitter: https://twitter.com/MakerTech_dk

// This code is released under the GNU GPLv3 license (http://choosealicense.com/licenses/gpl-3.0/)

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Breakout.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
Breakout breakout;
int count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  pinMode(L_PIN, INPUT);
  pinMode(R_PIN, INPUT);

  matrix.begin(0x70);  // pass in the address
  matrix.setBrightness(0);
}

void loop() {
  // action depends on game state - idealy the state should be a part of the Breakout class or a seperate logic class
  switch(state){
    // setup game
    case SETUP:
      breakout.restart();
      breakout.speed = START_SPEED;
      state = START;
      break;
      
    case START:
    // ready to start the game, changed to PLAY if the action button is pushed. 
    // Change here if paddle should be able to move before you shoot the first ball and start the game.
      checkActions();
      if(actions == SEL){
        state = PLAY;
      }
      break;
      
    case LOST:
    // game lost
      breakout.lost();
      reDraw();
      blink(10, 100);
      breakout.restart();
      breakout.speed = START_SPEED;
      state = START;
      break;

    case WON:
    // game won
      breakout.won(); 
      reDraw();
      blink(10, 100);
      breakout.restart();
      state = START;
      break;
      
    case PLAY:
      // game in play
      {
        if(count > breakout.speed){
          checkControls();
          breakout.play(controls);
          count = 0;
        
          if(breakout.bricks == 0){
          state = WON;
          }
          if(breakout.ball.y == 0)
            state = LOST;
          }
        delay(20);
        count++;
      }
  }
  reDraw();
}

void reDraw(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(breakout.level[i][8-j-1] != 'E'){
        matrix.drawPixel(i,j,1);
      }
      else
        matrix.drawPixel(i,j,0);
    }  
  }
  matrix.writeDisplay();
}

void checkActions(){
  int count = 0;
  while(count < 5 && digitalRead(SELECT)){
    count++;
  }
  if(count > 4){
    actions = SEL;
    return;
  }
  actions = NO;
}

void checkControls(){
  int count = 0;
  while(count < 5 && digitalRead(L_PIN)){
    count++;
  }
  if(count > 4){
    controls = LEFT;
    return;
  }
  count = 0;
  while(count < 5 && digitalRead(R_PIN)){
    count++;
  }
  if(count > 4){
    controls = RIGHT;
    return;
  }
  controls = NONE;
}
void blink(int times, int wait){
  for(int i = 0; i < times; i++){
    matrix.setBrightness(2);
    matrix.writeDisplay();
    delay(wait);
    matrix.setBrightness(0);
    matrix.writeDisplay();
    delay(wait);
  }
}
