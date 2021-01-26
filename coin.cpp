#include "coin.h"
#include "lasso.h"

#include <cstdlib>
#include <time.h>

void Coin::initialiseCoin(){
  if(coin_mode!="Temp"){
  coin_start_x=random_x();
  coin_start_y = WINDOW_Y+SUPER_COIN_SIZE;
  release_speed = (coin_mode=="Bomb")? (BOMB_SPEED):(COIN_SPEED);
  release_angle_deg=random_angle(coin_start_x);
  coin_ax = 0;
  coin_ay = (coin_mode=="Bomb")? (BOMB_G):(COIN_G);
  }
  if(coin_mode=="Temp"){
  coin_ax=0;
  coin_ay = COIN_G/2;
  release_speed =0;

  }
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
  else if(coin_mode == "CoinShower")
    {r=255;g=104;b=0;}

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
  else if(coin_mode == "CoinShower")
    {r=153;g=51;b=51;}

  if(coin_mode=="Bomb"){
    for(int i=0;i<4;i++) {
    int len=COIN_SIZE+SPIKE_SIZE*2;
    bombSpike[i].reset(coin_start_x-len/2,coin_start_y,coin_start_x+len/2,coin_start_y);
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

void Coin::resetCoin(){
  if(coin_mode!="Temp"){
  coin_start_x=random_x();
  coin_start_y = WINDOW_Y+SUPER_COIN_SIZE;
  release_angle_deg=random_angle(coin_start_x);
  }
  bool paused=true;
  bool rtheta =true;

  reset_all(coin_start_x, coin_start_y, release_speed, release_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::nextStep(double stepTime){
  MovingObject::nextStep(stepTime);
  if(coin_mode=="Bomb"){
   for(int i=0;i<4;i++){
     if(release_angle_deg<90){
       bombSpike[i].right(BOMB_W*stepTime);
     }
     else{bombSpike[i].right(-BOMB_W*stepTime);}
   }
  }
}

double Coin::random_x() {
  double f=abs(1.0*rand()/RAND_MAX);
  return (f*COIN_START_X + (1-f)*COIN_END_X);
}

double Coin::random_angle(double start_x) {
  double f=1.0*rand()/RAND_MAX;
  double angle= 1.0*MIN_ANGLE*f+MAX_ANGLE*(1-f);
   if(start_x < COIN_START_X*0.5+COIN_END_X*0.5)
     return angle;
   else
     return 180-angle;
}

