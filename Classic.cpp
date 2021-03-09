#include "screens.h"
#include "lasso.h"

#include <ctime>
#include<cstdlib>

void screens::Classic(){
  std::srand(time(0));                                //seed random funcion

  int stepCount = 0;
  float stepTime = STEP_TIME;
  float currTime = 0;
  float bufferTime=BUFFER_TIME*4;
  int currNumBombs=0;                                 //bomb counter
  int maxNumBombs=5;                                  // max numberofCoins. game ends if counter reaches this value
  int numGameBombs = 3;
  colorScreen(255, 255, 204);                         //Color background

beginFrame();
  Rectangle r1(PLAY_X_START/2,WINDOW_Y/2,PLAY_X_START,WINDOW_Y);// left side panel
  r1.setColor(COLOR(53,153,255));
  r1.setFill(true);
  Rectangle r2(WINDOW_X-PLAY_X_START/2,WINDOW_Y/2, PLAY_X_START,WINDOW_Y );// right side panel
  r2.setColor(COLOR(153,153,255));
  r2.setFill(true);

  Rectangle exitr;                                    // exit button
  Line exit1,exit2;
  exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
  exitr.setColor(COLOR(255,255,255));
  exitr.setFill(true);
  int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
  exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
  exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

  char coinScoreStr[256];                             // display score
  sprintf(coinScoreStr, "Coins: %d", 0);
  Text coinScore(WINDOW_X-PLAY_X_START-150,2*COIN_SIZE+30, coinScoreStr);
  Coin score_display_coin(WINDOW_X-PLAY_X_START-150,COIN_SIZE+10,0,0,0,0,true,true,"Temp");
  char bombsCaught[256];                              // dispaly bombsCaught
  sprintf(bombsCaught,"Bombs Caught: %d/5",currNumBombs);
  Text dispBombsCaught(PLAY_X_START+70,2*COIN_SIZE+40,bombsCaught);

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta,PLAY_Y_HEIGHT+10);

  // Create three coins and three bombs
  vector<Coin*> coinVect(6,NULL);
  for(int i=0;i<3;i++) coinVect[i] = new Coin(paused,rtheta,"Regular");
  for(int i=3;i<3+numGameBombs;i++) coinVect[i] = new Coin(paused,rtheta,"Bomb");

  //vector of counter bombs (displayed above the counter of bomb caught)
  vector<Coin*> bombVect(maxNumBombs,NULL);
endFrame();
  // Press up arrow for throw
  // Press down arrow for yank
  // press left to rotate lasso acw
  // Press right to rotate lasso cw
  // Press spacebar to loop
  // Click exit button to redirect outof the game.

  while(true) {
    //Endgame if bomb counter reaches max
    if(currNumBombs>=maxNumBombs) {
      beginFrame();
        for(size_t i=0;i<coinVect.size();i++)
          delete coinVect[i];
        for(size_t i=0;i<bombVect.size();i++)
          {delete bombVect[i];}
        endFrame();
         break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c='z';  //to avoid random initialization
      if(keyPressEvent(e))
         c = charFromEvent(e);

      if(checkExit(e))  { //if player presses exit delete coin pointers and break out of inf loop
        beginFrame();
        for(size_t i=0;i<coinVect.size();i++)
          delete coinVect[i];
        for(size_t i=0;i<bombVect.size();i++)
          {if(bombVect[i]!=NULL)delete bombVect[i];}
        endFrame();
        break;
        }

      switch(c) {
      case 72:                 // if up key is pressed throw lasso
	    lasso.unpause();break;
      case 80:                 // if down key is pressed yank lasso
	    lasso.yank();break;
      case 32:                 // if spacebar is pressed loop lasso if it is not yanked and check for coins
        if(!lasso.isPaused()) {
	      lasso.loopit();
	      lasso.check_for_coin(coinVect);
        }break;
	  case 75:                // left key press makes lasso rotate cw
	    if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}break;
      case 77:                // right key press makes lasso rotate acw
    	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }break;
      default:
	    break;
      }//end switch
    }// end if

  beginFrame();
    lasso.nextStep(stepTime); // move coins and lasso
    for(size_t i=0;i<coinVect.size();i++) coinVect[i]->nextStep(stepTime);
  endFrame();

    for(size_t i=0;i<coinVect.size();i++){                //reset all out of bound coins(completely out of screen) to random positions
    if(coinVect[i]->getYPos() > WINDOW_Y+SUPER_COIN_SIZE) {
      coinVect[i]->resetCoin();
    }}



    if(coinVect[0]->isPaused()) coinVect[0]->unpause();  //always unpause first regular/gold coin
    if(coinVect[1]->isPaused()){                         //unpause second reg/gold coin by a certain probability factor.
       if(rand()%(10*PROB_FACTOR+2)==0){coinVect[1]->unpause();}
    }
    if(coinVect[2]->isPaused()){                         //unpause third reg/gold coin half times as much as the second coin.
       if(rand()%(10*PROB_FACTOR*2+2)==0){coinVect[2]->unpause();}
    }
    if(rand()%(PROB_FACTOR*5)==0){                       // unpause the first two bombs together always
    if(coinVect[3]->isPaused())
      coinVect[3]->unpause();
    if(coinVect[4]->isPaused())
      coinVect[4]->unpause();
    }
    if(coinVect[5]->isPaused())                          // unpause the third bomb 1.5 as much as the first two  bombs.
    if(rand()%(PROB_FACTOR*2)==0){
      coinVect[5]->unpause();
    }
    for(int i=6;i<3+numGameBombs;i++){
      if(coinVect[i]->isPaused())
      if(rand()%(2*i*PROB_FACTOR)==0)
      coinVect[i]->unpause();
    }
    sprintf(coinScoreStr, "Coins: %d",lasso.getNumCoins());// display score
    coinScore.setMessage(coinScoreStr);

    wait(bufferTime);

    stepCount++;
    currTime += stepTime;

    if(stepCount%(20*30)==0){
     coinVect.push_back(NULL);
     coinVect.back()= new Coin(paused,rtheta,"Bomb");
     numGameBombs++;
    }

    if(lasso.getNumBombs()>currNumBombs){                // if the number of bombs caught by lasso increases increment bomb counter, display counter bombs
    for(int i=currNumBombs;i<min(maxNumBombs,lasso.getNumBombs());i++){
    double c_x = PLAY_X_START+(2*COIN_SIZE+20)*(i+0.5);
    double c_y = COIN_SIZE+10;
    bombVect[i] = new Coin(c_x , c_y , "Bomb");
    }
    currNumBombs=lasso.getNumBombs();
    sprintf(bombsCaught , "Bombs Caught: %d/%d" , currNumBombs,maxNumBombs);
    dispBombsCaught.setMessage(bombsCaught);
    }

  } // End for(;;)
  outFile.open("Data.txt", ios::app);
  outFile<<"1 "<<lasso.getNumCoins()<<endl;         // output the score to the data file
  outFile.close();
  curr_screen='P';prev_screen='C';            // set currscreen to postGame and lastSCreen to arcade
  return;

}
