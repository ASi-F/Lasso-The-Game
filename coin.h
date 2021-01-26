#ifndef __COIN_H__
#define __COIN_H__

#include "MovingObject.h"
#include <string>

class Coin:public MovingObject{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;
  int random;
  string coin_mode;

  Circle coin_circle;
  Line bombSpike[4];
  Circle coin_border;

public:
Coin(bool paused,bool rtheta,string mode):MovingObject() {
  coin_mode=mode;
  initialiseCoin();
     double angle_rad = release_angle_deg*PI/180.0;
     double argvx = release_speed*cos(angle_rad);
     double argvy = -release_speed*sin(angle_rad);
  initMO(argvx,argvy,coin_ax,coin_ay,paused);
}

Coin(double start_x,double start_y):MovingObject(){
  coin_mode="Temp";
  coin_start_x=start_x;
  coin_start_y=start_y;
  initialiseCoin();
     if(release_angle_deg==0)
  initMO(release_speed,0,coin_ax,coin_ay,true);
  else
  initMO(-release_speed,0,coin_ax,coin_ay,true);
}

void initialiseCoin();
void resetCoin();
void nextStep(double stepTime);

string checkMode(){return coin_mode;}
double random_x();
double random_angle(double start_x);
};

#endif
