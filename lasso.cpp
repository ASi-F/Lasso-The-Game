#include <simplecpp>
#include <string>
#include<cstdlib>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "ScreenObjects.h"
using namespace simplecpp;

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso(double startx,double starty) {
  lasso_start_x = startx;
  lasso_start_y = starty;
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR(153,102,0));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  //the_coin = NULL;
  num_coins = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR(0,0,100));

  lasso_band.setColor(COLOR(138,42,226));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  if(coins.size()!=0) {
    //num_coins++;
   // beginFrame();
    for(size_t i=0;i<coins.size();i++){
    if(sqrt(pow(getXPos()-coins[i]->getXPos(),2)+pow(getYPos()!=coins[i]->getYPos(),2))<1E-5){
    coins[i]->resetCoin();
    }
    }
   // endFrame();
  }
  bool paused = true, rtheta = true;//beginFrame();
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);//endFrame();
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getXPos()>WINDOW_X || 0>getXPos() || getYPos()>WINDOW_Y) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

int Lasso::check_for_coin(vector<Coin*> coinVect) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  int ret=0;
  Text *t1=new Text;
  Text *t2=new Text;
  Text *t3=new Text;
  int delta_coins{0};
  for(size_t i=0;i<coinVect.size();i++){
  double coin_x = coinVect[i]->getXPos();
  double coin_y = coinVect[i]->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);

  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS  && 1E-5 < distance) {
    coins.push_back(coinVect[i]);
    coins.back()->getAttachedTo(this);
    if(coinVect[i]->checkMode()=="Regular") {
      delta_coins++;
      }
    else if(coinVect[i]->checkMode()=="Super"){
     delta_coins+=5;
    }
    else if(coinVect[i]->checkMode()=="Bomb"){
      delta_coins-=1;
    }
    else if (coinVect[i]->checkMode()=="Time"){
      ret+=1;
    }
    else if(coinVect[i]->checkMode()=="CoinShower"){
       ret+=2;
    }
}
  }
  num_coins+=delta_coins;
   string score;
  if(delta_coins>0)
  score.push_back('+');
  else if(delta_coins<0)
  score.push_back('-');
  if(delta_coins<0)
  delta_coins*=-1;
  if(delta_coins>=10);
  score.push_back('0'+delta_coins/10);
  if(delta_coins>0);
  score.push_back('0'+delta_coins%10);
  if(delta_coins!=0)
  t1->reset(lasso_x+LASSO_RADIUS/2,lasso_y-LASSO_RADIUS/2,score);
  if(ret==1 || ret==3)
  t2->reset(lasso_x+LASSO_RADIUS/2,lasso_y+LASSO_RADIUS/2,"+30s");
  if(ret==2 || ret==3)
  t3->reset(lasso_x+LASSO_RADIUS/2,lasso_y+LASSO_RADIUS/2,"FRENZY!");
  if(delta_coins!=0)
  wait(STEP_TIME*3);

    delete t1;delete t2;delete t3;
  return ret;
} // End Lasso::check_for_coin()


