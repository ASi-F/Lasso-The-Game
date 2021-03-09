#include "coin.h"
#include "lasso.h"

#include <cstdlib>
#include <time.h>

void Coin::initRandCoin(){   // initialise coin at a random position between COIN_START_X AND COIN_END_X
  coin_start_x=random_x();
  coin_start_y = WINDOW_Y+SUPER_COIN_SIZE;  // initialise y to be below the screen so that coin is not visible when paused
  release_speed = (coin_mode=="Bomb")? (BOMB_SPEED):(COIN_SPEED);
  release_angle_deg=random_angle(coin_start_x);
  coin_ax = 0;
  coin_ay = (coin_mode=="Bomb")? (BOMB_G):(COIN_G);
}

// Initialise coin to the input parameters
void Coin::initCoin(double start_x,double start_y,double speed,double angle_deg,double argax,double argay){
  coin_start_x=start_x;
  coin_start_y=start_y;
  release_speed = speed;
  release_angle_deg = angle_deg;
  coin_ax = argax;
  coin_ay = argay;
}

void Coin::drawCoin(){  // initialise the visible parts of the coin.
int r{0},g{0},b{0};
  double coin_size = COIN_SIZE;
  if( coin_mode == "Regular" || coin_mode=="Temp")
    {r=255;g=204;b=0;}
  else if(coin_mode == "Bomb")
    {r=0;g=0;b=0;}
  else if(coin_mode == "Super")
    {r=255;g=153;b=0;coin_size=SUPER_COIN_SIZE;}
  else if(coin_mode == "Time")
    {r=0;g=255;b=0;}
  else if(coin_mode == "Frenzy")
    {r=255;g=104;b=0;}
  else if(coin_mode == "Magnet")
    {r=128,g=128,b=128;}

  coin_circle.reset(coin_start_x,coin_start_y,coin_size);
  coin_circle.setColor(COLOR(r,g,b));
  coin_circle.setFill(true);
  addPart(&coin_circle);

  if( coin_mode == "Regular" || coin_mode=="Temp")
    {r=255;g=255;b=11;}
  else if(coin_mode == "Bomb")
    {r=0;g=0;b=0;}
  else if(coin_mode == "Super")
    {r=204;g=51;b=0;coin_size=SUPER_COIN_SIZE;}
  else if(coin_mode == "Time")
    {r=102;g=0;b=204;}
  else if(coin_mode == "Frenzy")
    {r=153;g=51;b=51;}
  else if(coin_mode== "Magnet")
    {r=255;g=0;b=0;}


  if(coin_mode=="Bomb"){
    for(int i=0;i<4;i++) {
    int len=COIN_SIZE+SPIKE_SIZE*2;
    bombSpike[i].reset(coin_start_x-len/2,coin_start_y,coin_start_x+len/2,coin_start_y);
    bombSpike[i].setThickness(BOMB_SPIKE_THICKNESS);
    bombSpike[i].right(45*i);
    addPart(&bombSpike[i]);
    }
  }
  else{
  coin_border.reset(coin_start_x,coin_start_y,coin_size);
  coin_border.setColor(COLOR(r,g,b));
  addPart(&coin_border);
  }
}

void Coin::resetRandCoin(){ //Reset the coin to a random position at a corresponding angle, and the initial y below the screen
  coin_start_x=random_x();
  release_angle_deg=random_angle(coin_start_x);
  bool paused=true;
  bool rtheta =true;

  reset_all(coin_start_x, coin_start_y, release_speed, release_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::nextStep(double stepTime){  //Execute the next step form parent class, additonally make bomb rotate
  MovingObject::nextStep(stepTime);
  if(coin_mode=="Bomb"){
   for(int i=0;i<4;i++){
     if(release_angle_deg<90){
       bombSpike[i].right(BOMB_W*stepTime); // bomb rotates cw if thrown towards right
     }
     else{bombSpike[i].right(-BOMB_W*stepTime);} // bomb rotates acw if thrown left
   }
  }
}

void Coin::resetCoin(){                 // rest coin to its initial parameters during initialisation like position, speed, acceleraion etc
  bool paused=true;
  bool rtheta =true;
  reset_all(coin_start_x, coin_start_y, release_speed, release_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

double Coin::random_x() {              // genrate random x between COIN_START_X COIN_END_X
  double f=abs(1.0*rand()/RAND_MAX);
  return (COIN_START_X*1.0 + f*(COIN_END_X-COIN_START_X));
}

double Coin::random_angle(double start_x) { // generate pseudo random between MAX_ANGLE and MIN_ANGLE based on the starting position of coin so ...
  double f = 1-2.0*(start_x-COIN_START_X)/(COIN_END_X-COIN_START_X);//... the coin is always directed towards central portion of screen and not ...
  double angle = MAX_ANGLE*1.0-1.0*f*(MAX_ANGLE-MIN_ANGLE);//...away from the centre, outside the screen
  return angle;
}

