#include <simplecpp>
#include <string>
#include<cstdlib>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

// Comments are not added to functions which were not changed

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
  lasso_magnetized = false;
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
  num_bombs = 0;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR(0,0,100));

  lasso_band.setColor(COLOR(138,42,226));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  if(coins.size()!=0) {
    for(size_t i=0;i<coins.size();i++){
    if(sqrt(pow(getXPos()-coins[i]->getXPos(),2)+pow(getYPos()!=coins[i]->getYPos(),2))<1E-5){  //Checks if the coin has been caught by the Lasso
    if(coins[i]->checkMode()!="Temp")
    coins[i]->resetRandCoin();       //If the coin is not a temporary coin created for frenzy ode, it is resetted ramdomly(poition and angle)
    else
    coins[i]->resetCoin();
    }
    }
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
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

/* Here we check an entire vector of coin pointers, to avoid calling this functon in main program
 for each coin seperately, and to calculate the net effect of all coins caught, display a message
 accordingly, and avoid the wait in the end(the user must be able to read the mesage and hence we
 exercise a wait message before deleting the message) for each and every coin caught. */
int Lasso::check_for_coin(vector<Coin*> coinVect) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  int ret=0;        // the integer to be returned. helps us know if a special coin was caught...
  Text t1,t2,t3;    //...We will increment it by 1 when timeCoin is caugh, by 2 when frenzy coin is caught
  int delta_coins{0};   // strores the change in number of coins for all coins
  for(size_t i=0;i<coinVect.size();i++){  //iterate over all coins in the coin vector
  double coin_x = coinVect[i]->getXPos();
  double coin_y = coinVect[i]->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);

  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));  //calculate distance between coin and
  if(distance <= LASSO_RADIUS  && 1E-5 < distance) { // if in range, catch
    coins.push_back(coinVect[i]);
    coins.back()->getAttachedTo(this);
    string mode=coinVect[i]->checkMode();
    if(mode=="Regular" || mode=="Temp") { //change delta_coins according to the coin type
      delta_coins++;
      }
    else if(mode=="Super"){
     delta_coins+=5;
    }
    else if(mode=="Bomb"){
      delta_coins-=1;num_bombs++;         // increment the bomb counter
    }
    else if (mode=="Time"){
      ret+=1;
    }
    else if(mode=="Frenzy"){
       ret+=2;
    }
    else if(mode=="Magnet"){
       lasso_magnetized=true;    //magnetize coins
       magnetizeCoins(coinVect);
    }
}
  }
  num_coins+=delta_coins;  //change the coins counter
   string score;           //score string initialised
  if(delta_coins>0)
  score.push_back('+');    // first char + if num cins is increasing
  else if(delta_coins<0)
  score.push_back('-');    // first char - if num coins decreasing
  if(delta_coins<0)
  delta_coins*=-1;         // take absolute value of delta_coins
  if(delta_coins>=10);
  score.push_back('0'+delta_coins/10);  // if change in score is double digit push_back the 10s place digit (it cant be 3 digit)
  if(delta_coins>0);
  score.push_back('0'+delta_coins%10);  // add last digit to the string
  if(delta_coins!=0)                    // display change in score if it chanes delta_coins not=0, the score change and the other 2 messages..
  t1.reset(lasso_x+LASSO_RADIUS/2,lasso_y-LASSO_RADIUS/2,score);// ...are displayed at different positions around the lasso so that they dont overlap
  if(ret==1 || ret==3)                  // ret = 1 means timecoin catched, ret=2 means frenzy coin caught, ret=3  means both caught
  t2.reset(lasso_x+LASSO_RADIUS/2,lasso_y+LASSO_RADIUS/2,"+15s");
  if(ret==2 || ret==3)
  t3.reset(lasso_x+LASSO_RADIUS/2,lasso_y+LASSO_RADIUS/2,"FRENZY!");
  if(delta_coins!=0 || ret!=0)
  wait(STEP_TIME*3);                    // delta_coins not 0 and ret not zero means some message was displayed, so we wait to appreciate

    return ret;
} // End Lasso::check_for_coin()



void Lasso::magnetizeCoins(vector<Coin*> coinVect){
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  for(size_t i=0;i<coinVect.size();i++){
    bool paused = coinVect[i]->isPaused();
    string mode=coinVect[i]->checkMode();
    if(!paused && (mode=="Regular" || mode=="Temp")  ){ // magnetize only gold coins, both temp and regualr are gold coin modes
      double x=-(coinVect[i]->getXPos()-lasso_x);
      double y=-(coinVect[i]->getYPos()-lasso_y);
      if(x*x+y*y>COIN_SIZE*COIN_SIZE){                   // if lasso is far  away from the coin, direct its velocity, acceleration towayds lasso
        //point g and v in direction of lasso
        double a0x= x*COIN_G/sqrt(x*x+y*y);
        double a0y= y*COIN_G/sqrt(x*x+y*y);
        coinVect[i]->set_ax(a0x);
        coinVect[i]->set_ay(a0y);
        double v0x=coinVect[i]->get_vx();
        double v0y=coinVect[i]->get_vy();
        double v=sqrt(v0x*v0x+v0y*v0y);
        v0x= x*v/sqrt(x*x+y*y);
        v0y= y*v/sqrt(x*x+y*y);
        coinVect[i]->set_vx(v0x);
        coinVect[i]->set_vy(v0y);
      }
      else if(!paused){                            // if it is too close and lasso is not paused, give it a velocity parllel to the lasso. Here we dont change acceleration because coins
        coinVect[i]->set_vx(get_vx());             // will be magnetized at each step, so accleration of the coin wont matter
        coinVect[i]->set_vy(get_vy());
      }
      else if(sqrt(x*x+y*y)>1E-5){                 //If coin distance from lasso is between 0 and coin radius and lasso is in yanked position make the lasso still.
        coinVect[i]->set_vx(0);
        coinVect[i]->set_vy(0);
        coinVect[i]->set_ax(0);
        coinVect[i]->set_ay(0);
      }
    }
  }
  }  //end Lasso::magnetizeCoins()

void Lasso::unMagnetize(vector<Coin*> coinVect){
  lasso_magnetized=false;
  for(size_t i=0;i<coinVect.size();i++){
  coinVect[i]->set_ax(0);
  coinVect[i]->set_ay(COIN_G);
  }
} // End Lasso::unMagnetize
