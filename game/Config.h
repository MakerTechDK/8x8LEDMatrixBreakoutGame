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

#define L_PIN 9
#define R_PIN 8
#define SELECT 7
#define START_SPEED 5
#define PADDLE_START 2
#define PADDLE_SIZE 3
#define BRICKS 24

enum {START, WON, LOST, PLAY, SETUP} state = SETUP;
enum {LEFT, RIGHT, NONE} controls = NONE;
enum {SEL, NO} actions = NO;

