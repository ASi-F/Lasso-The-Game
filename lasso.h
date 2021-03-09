#ifndef __LASSO_H__
#define __LASSO_H__

#include "MovingObject.h"
#include "coin.h"

#define WINDOW_X 800
#define WINDOW_Y 600

#define RUN_TIME 120
#define STEP_TIME 0.05
#define BUFFER_TIME STEP_TIME*0.2
#define MAGNET_TIME_SECONDS 10
#define BONUS_TIME 15
#define PROB_FACTOR 15  //10
#define PLAY_X_START WINDOW_X/8
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y*5/6)
#define PLAY_Y_WIDTH WINDOW_X/8
#define MIN_ANGLE 70
#define MAX_ANGLE 90

#define LASSO_X_OFFSET 50
#define LASSO_Y_HEIGHT WINDOW_Y/6
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
#define MAX_RELEASE_SPEED 240*2
#define INIT_RELEASE_SPEED 120*2

#define COIN_SPEED 120*2
#define COIN_ANGLE_DEG 90
#define COIN_START_X 2*PLAY_X_START
#define COIN_END_X WINDOW_X-2*PLAY_X_START
#define BOMB_SPEED COIN_SPEED
#define BOMB_ANGLE_DEG 90

#define LASSO_G 34*3.3
#define COIN_G 30*3.8
#define BOMB_G 60*2
#define BOMB_W 20

#define SIZE_FACTOR 2.7
#define LASSO_SIZE 5
#define LASSO_RADIUS 50
#define BOMB_SPIKE_THICKNESS 4
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
  bool lasso_magnetized;
  vector<Coin*> coins;;
  int num_coins;
  int num_bombs;

  void initLasso(double, double);
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, double starty=PLAY_Y_HEIGHT-LASSO_Y_HEIGHT, double startx=PLAY_X_START+LASSO_X_OFFSET)
 : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
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
  int getNumBombs() { return num_bombs; }
  void setNumBoms(int x){num_bombs=x;}
  void magnetizeCoins(vector<Coin*> coinVect);
  void unMagnetize(vector<Coin*> coinVect);

  bool isMagnetized(){return lasso_magnetized;}
}; // End class Lasso

#endif
