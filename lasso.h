#ifndef __LASSO_H__
#define __LASSO_H__

#include "MovingObject.h"
#include "coin.h"

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05
#define PROB_FACTOR 15  //10

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)
#define PLAY_Y_WIDTH 100
#define MIN_ANGLE 60
#define MAX_ANGLE 90

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5
#define LASSO_MAX_LENGTH 50

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200*2
#define INIT_RELEASE_SPEED 100*2

#define COIN_SPEED 120*2
#define COIN_ANGLE_DEG 90
#define COIN_START_X 265
#define COIN_END_X 625
#define BOMB_SPEED COIN_SPEED
#define BOMB_ANGLE_DEG 90

#define LASSO_G 30*3.3
#define COIN_G 30*3.8
#define BOMB_G 60*2
#define BOMB_W 20

#define SIZE_FACTOR 2.7
#define LASSO_SIZE 5
#define LASSO_RADIUS 50
#define COIN_SIZE 5*SIZE_FACTOR
#define SUPER_COIN_SIZE 8*SIZE_FACTOR
#define SPIKE_SIZE 4*SIZE_FACTOR

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  vector<Coin*> coins;;
  int num_coins;

  void initLasso(double, double);
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, double starty=PLAY_Y_HEIGHT-LASSO_Y_HEIGHT, double startx=PLAY_X_START+LASSO_X_OFFSET) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso(startx,starty);
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  int check_for_coin(vector<Coin*> coinVect);
  int getNumCoins() { return num_coins; }

}; // End class Lasso

#endif
