#ifndef __COIN_H__
#define __COIN_H__

#include "MovingObject.h"

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
  Circle coin_border;
  Line bombSpike[4];

public:
Coin(bool paused,bool rtheta,string mode):MovingObject() { //Initaialise coin to a random position, random angle, vertical graviy, etc
  coin_mode=mode;
  initRandCoin();
  drawCoin();
     double angle_rad = release_angle_deg*PI/180.0;
     double argvx = release_speed*cos(angle_rad);
     double argvy = -release_speed*sin(angle_rad);
  initMO(argvx,argvy,coin_ax,coin_ay,paused);
}
//Initialise coin to input parameters
Coin(double start_x,double start_y,double speed, double angle_deg, double argax,double argay, bool paused, bool rtheta, string mode):MovingObject(){
  coin_mode=mode;
  initCoin(start_x,start_y,speed,angle_deg,argax,argay);
  drawCoin();
     double angle_rad = release_angle_deg*PI/180.0;
     double argvx = release_speed*cos(angle_rad);
     double argvy = -release_speed*sin(angle_rad);
  initMO(argvx,argvy,coin_ax,coin_ay,paused);
}
//To make dummy coins at input positions
Coin(double start_x,double start_y, string mode):MovingObject(){
  coin_mode=mode;
  double argvx = 0;
  double argvy = 0;
  double speed = 0;
  double angle = 0;
  double argax=0;
  double argay=0;
  bool paused = true;
    initCoin(start_x,start_y,speed,angle,argax,argay);
    drawCoin();
    initMO(argvx,argvy,argax,argay,paused);
}

void initRandCoin();
void initCoin(double start_x,double start_y,double speed,double angle_deg,double argax,double argay);
void drawCoin();
void resetRandCoin();
void resetCoin();
void nextStep(double stepTime);

string checkMode(){return coin_mode;}
double random_x();
double random_angle(double start_x);
};

#endif
