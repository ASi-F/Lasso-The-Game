#include "screens.h"
#include "lasso.h"
#include <ctime>
#include<cstdlib>

void screens::Arcade(){
  ScrObj.colorScreen(255, 255, 204);                               //Color background

  std::srand(time(0));                                             //seed random funcion

  int stepCount = 0;
  float stepTime = STEP_TIME;
  float bufferTime = stepTime*0.2;
  float runTime = 120; // sec;
  float currTime = 0;
  int remaining_time=runTime;
  int timeCoin = rand()%remaining_time/3;
  int numTemp=5;
  int showerCoin = rand()%remaining_time;

beginFrame();
  Rectangle r1(PLAY_X_START/2,WINDOW_Y/2,PLAY_X_START,WINDOW_Y);
  r1.setColor(COLOR(0,0,255));
  r1.setFill(true);
  Rectangle r2(WINDOW_X-PLAY_X_START/2,WINDOW_Y/2, PLAY_X_START,WINDOW_Y );
  r2.setColor(COLOR(0,0,255));
  r2.setFill(true);

  Rectangle exitr;
  Line exit1,exit2;
  exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
  exitr.setColor(COLOR(255,255,255));
  exitr.setFill(true);
  int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
  exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
  exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", 0);
  Text coinScore(WINDOW_X-PLAY_X_START-150,2*COIN_SIZE+30, coinScoreStr);
  Coin score_display_coin(WINDOW_X-PLAY_X_START-150,COIN_SIZE+10);

  Coin regular_coin_instr(PLAY_X_START/2, 200);
   Text pt1(PLAY_X_START/2, 200+COIN_SIZE+20,"1 pt");
  Coin dummyBomb(true,true,"Bomb");
   dummyBomb.reset_all(PLAY_X_START/2,200+COIN_SIZE*2+40,0,0,0,0,true,true);
    Text pt2(PLAY_X_START/2,200+COIN_SIZE*3+60,"-2 pt");
  Coin dummyTime(true,true,"Time");
   dummyTime.reset_all(PLAY_X_START/2,200+COIN_SIZE*4+80,0,0,0,0,true,true);
    Text pt3(PLAY_X_START/2,200+COIN_SIZE*5+100,"+30s");
  Coin dummyShower(true,true,"CoinShower");
   dummyShower.reset_all(PLAY_X_START/2,200+COIN_SIZE*6+120,0,0,0,0,true,true);
    Text pt4(PLAY_X_START/2,200+COIN_SIZE*7+140,"FRENZY!!!");
  Coin dummySuper(true,true,"Super");
   dummySuper.reset_all(PLAY_X_START/2,200+COIN_SIZE*7+SUPER_COIN_SIZE+160,0,0,0,0,true,true);
    Text pt5(PLAY_X_START/2,200+COIN_SIZE*7+SUPER_COIN_SIZE+200,"+5 pts");

  char seconds[256];
  if(remaining_time%60<10)
    sprintf(seconds,"0%d",remaining_time%60);
  else
    sprintf(seconds,"%d",remaining_time%60);
  Text diplaySeconds(PLAY_X_START+100,20,seconds);

  char minutes[256];
  sprintf(minutes,"0%d :",remaining_time/60);
  Text diplayMinutes(PLAY_X_START+80,20,minutes);
  Text remainingTime(PLAY_X_START+90,50,"Remaining Time");

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta,PLAY_Y_HEIGHT+10);

  //Draw Coins  at random positions
  vector<Coin*> coinVect(9+2*numTemp,NULL);
  for(int i=0;i<3;i++){
    coinVect[i] = new Coin(paused,rtheta,"Regular");
  }
  for(int i=3;i<6;i++){
    coinVect[i] = new Coin(paused,rtheta,"Bomb");
  }
  coinVect[6] = new Coin(paused, rtheta, "Super");
  coinVect[7]= new Coin(paused,rtheta, "Time");
  coinVect[8]= new Coin(paused,rtheta, "CoinShower");
   for(int i=9;i<9+numTemp;i++){
          coinVect[i] = new Coin(WINDOW_X/2+(i-14)*(COIN_SIZE*2),-3*COIN_SIZE);
          coinVect[i+numTemp] = new Coin(WINDOW_X/2+(i-14)*(COIN_SIZE*2),-COIN_SIZE);
          }
endFrame();
  while(true){


  // Press up arrow for throw
  // Press down arrow for yank
  // press left to rotate lasso acw
  // Press right to rotate lasso cw
  // Press enter to loop
  // Click exit button to redirect outof the game.

  XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c='z';
      if(keyPressEvent(e))
       { c = charFromEvent(e);}


      int a0=(e.xbutton.x)*65536+e.xbutton.y;
      if(ScrObj.checkExit(a0))  {
        x='L';
        for(size_t i=0;i<coinVect.size();i++)
          delete coinVect[i];
        break;
        }

        switch(c) {
      case 72:
	lasso.unpause();
	break;
      case 80:
	lasso.yank();
	break;
      case 13:
    if(!lasso.isPaused()) {
	 lasso.loopit();
	int a1=lasso.check_for_coin(coinVect);
      if(a1==1 || a1==3){
          remaining_time+=30;
          runTime+=30;
        }
        if(a1==2 || a1==3){
         for(int i=9;i<9+numTemp;i++){
          coinVect[i]->unpause();
          coinVect[i+numTemp]->unpause();
          }
        }
      }
	break;
	case 77:
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case 75:
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
      default:
	break;
      }//end switch

  }//end if
  beginFrame();
    lasso.nextStep(stepTime);
    for(size_t i=0;i<coinVect.size();i++){coinVect[i]->nextStep(stepTime);}
endFrame();
    for(size_t i=0;i<coinVect.size();i++){
    if(coinVect[i]->getYPos() > WINDOW_Y+SUPER_COIN_SIZE) {
      coinVect[i]->resetCoin();
    }}

    if(coinVect[0]->isPaused()){coinVect[0]->unpause();}
    if(coinVect[1]->isPaused()){
       if(rand()%(abs(remaining_time-60)*PROB_FACTOR+2)==0){coinVect[1]->unpause();}
    }
    if(coinVect[2]->isPaused()){
       if(rand()%(abs(remaining_time-60)*PROB_FACTOR*2+2)==0){coinVect[2]->unpause();}
    }
    if(rand()%(PROB_FACTOR*5)==0){
    if(coinVect[3]->isPaused())
      coinVect[3]->unpause();
    if(coinVect[4]->isPaused())
      coinVect[4]->unpause();
    }
    if(rand()%(PROB_FACTOR*2)==0){
    if(coinVect[5]->isPaused())
      coinVect[5]->unpause();
    }
    if(rand()%(PROB_FACTOR*30)==0){
    if(coinVect[6]->isPaused())
      coinVect[6]->unpause();
    }
    if(remaining_time == timeCoin){
    if(coinVect[7]->isPaused())
      coinVect[7]->unpause();
      float temp = runTime;
      timeCoin=rand()%int(temp);
    }
    if(remaining_time == showerCoin){
    if(coinVect[8]->isPaused())
      coinVect[8]->unpause();
      float temp = runTime;
      showerCoin=rand()%(int(temp)/3);
    }



  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

  if(stepCount%20==0){
  if(remaining_time%60<10)
    sprintf(seconds,"0%d",remaining_time%60);
  else
    sprintf(seconds,"%d",remaining_time%60);
    diplaySeconds.setMessage(seconds);

  sprintf(minutes,"0%d :",remaining_time/60);
  diplayMinutes.setMessage(minutes);
  }
  currTime+=stepTime;
  stepCount++;
  remaining_time=runTime-stepCount/20;


  wait(bufferTime);
  if((runTime > 0) && (currTime > runTime)) {
   diplaySeconds.setMessage("00");
   beginFrame();
   for(size_t i=0;i<coinVect.size();i++){
          delete coinVect[i];
          }

   endFrame();
   break; }

  }//end while
  outFile<<lasso.getNumCoins()<<endl;
  x='P';
  return;
}//end main
