#include "screens.h"
#include "lasso.h"
#include <ctime>
#include<cstdlib>

void screens::Arcade(){
  std::srand(time(0));                                      //seed random funcion

  int stepCount = 0;
  float stepTime = STEP_TIME;
  float bufferTime = BUFFER_TIME;                           //wait time that acounts for the time required in each loop
  float runTime = RUN_TIME; // sec;
  float currTime = 0;
  int remaining_time=runTime+0.01;                          // to avoid rounding off errors
  const int numTemp=40;                                     // number of coins taht fall in when FRENZY is caught
  int timeCoin =remaining_time-rand()%(remaining_time/2);  // time at which timecoin unpauses
  int frenzyTime =rand()%remaining_time;                   // time at which frenzy coin unpauses
  int magnetTime = rand()%remaining_time;                   // time at which magnet coin unpauses
  int magnetStartTime=-1;                                   // time at which the lasso is magnentized
  double magnetRemTime = MAGNET_TIME_SECONDS;               // time for which magnetization lasts
  int frenzyTimes[numTemp]={-1};                            // array which will contain the times at which each of the coin in frenzy mode should unpause
                                                            // so that they start falling at different times
  colorScreen(255, 255, 204);                               //Color background

beginFrame();

  Rectangle leftr(PLAY_X_START/2,WINDOW_Y/2,PLAY_X_START,WINDOW_Y);//checks if the user presses the default exit button on most screens on the top right
                                                                   // left side panel
  leftr.setColor(COLOR(255, 173, 153));
  leftr.setFill(true);
  Rectangle rightr(WINDOW_X-PLAY_X_START/2,WINDOW_Y/2, PLAY_X_START,WINDOW_Y );// right side panel
  rightr.setColor(COLOR(255,133,102));
  rightr.setFill(true);

  Rectangle exitr;                                          // draw the top right exit button
  Line exit1,exit2;
  exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
  exitr.setColor(COLOR(255,255,255));
  exitr.setFill(true);
  int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
  exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
  exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

  char coinScoreStr[256];                                    //display score
  sprintf(coinScoreStr, "Coins: %d", 0);
  Text coinScore(WINDOW_X-PLAY_X_START-150,2*COIN_SIZE+30, coinScoreStr);
  Coin score_display_coin(WINDOW_X-PLAY_X_START-150,COIN_SIZE+10,0,0,0,0,true,true,"Temp");

  char seconds[256];                                         // dispaly the seconds part of rem time
  if(remaining_time%60<10)
    sprintf(seconds,"0%d",remaining_time%60);
  else
    sprintf(seconds,"%d",remaining_time%60);
  Text diplaySeconds(PLAY_X_START+100,20,seconds);

  char minutes[256];                                         // display the minutes part of the rem time
  sprintf(minutes,"0%d :",remaining_time/60);
  Text diplayMinutes(PLAY_X_START+80,20,minutes);
  Text remainingTime(PLAY_X_START+90,50,"Remaining Time");

  char magnetTimer[256];                                    // will display the number of seconds after which lasso wil unmagnetize, once magnetized
  Text magnetMessage(WINDOW_X/2,70,"");

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta,PLAY_Y_HEIGHT+10);

  //draw dummy coins on the left panel to display their characteritics.
  double dum_coin_h = 100;
  Coin regular_coin_instr(PLAY_X_START/2, dum_coin_h,"Regular");
   Text pt1(PLAY_X_START/2, dum_coin_h+COIN_SIZE+20,"1 pt");
  Coin dummyBomb(PLAY_X_START/2,dum_coin_h+COIN_SIZE*2+40,"Bomb");
    Text pt2(PLAY_X_START/2,dum_coin_h+COIN_SIZE*3+60,"-1 pt");
  Coin dummyTime(PLAY_X_START/2,dum_coin_h+COIN_SIZE*4+80,"Time");
    Text pt3(PLAY_X_START/2,dum_coin_h+COIN_SIZE*5+100,"+15s");
  Coin dummyShower(PLAY_X_START/2,dum_coin_h+COIN_SIZE*6+120,"Frenzy");
    Text pt4(PLAY_X_START/2,dum_coin_h+COIN_SIZE*7+140,"FRENZY!!!");
  Coin dummyMagnet(PLAY_X_START/2,dum_coin_h+COIN_SIZE*8+160,"Magnet");
    Text pt5(PLAY_X_START/2,dum_coin_h+COIN_SIZE*9+180,"Coin Magnet!");
  Coin dummySuper(PLAY_X_START/2,dum_coin_h+COIN_SIZE*9+SUPER_COIN_SIZE+200,"Super");
    Text pt6(PLAY_X_START/2,dum_coin_h+COIN_SIZE*9+SUPER_COIN_SIZE*2+220,"+5 pts");

  //Draw Coins  at random positions
  vector<Coin*> coinVect(10+numTemp,NULL);
  for(int i=0;i<3;i++) coinVect[i] = new Coin(paused,rtheta,"Regular"); // creates three gold coins/regular coins
  for(int i=3;i<6;i++) coinVect[i] = new Coin(paused,rtheta,"Bomb");    // creates three bombs
  coinVect[6] = new Coin(paused, rtheta, "Super");
  coinVect[7]= new Coin(paused,rtheta, "Time");
  coinVect[8]= new Coin(paused,rtheta, "Frenzy");
  for(int i=9;i<9+numTemp;i++) //creates required amount of temporary coins for frenzy mode
  coinVect[i] = new Coin(coinVect[i]->random_x()*0.5+WINDOW_X*0.25,-3*COIN_SIZE,0,0,0,COIN_G,true,true,"Temp");
  coinVect.back()= new Coin(paused,rtheta, "Magnet");

endFrame();

  while(true){


  // Press up arrow for throw
  // Press down arrow for yank
  // press left to rotate lasso cw
  // Press right to rotate lasso acw
  // Press spacebar to loop
  // Click exit button to redirect outof the game.

  XEvent e;
  bool pendingEv = checkEvent(e);

  if(pendingEv) {
    char c='z';  //to avoid random initialization
    if(keyPressEvent(e))
       c = charFromEvent(e);

    if(checkExit(e))  {
    beginFrame();
      for(size_t i=0;i<coinVect.size();i++)  //if player presses exit delete coin pointers and break out of inf loop
        delete coinVect[i];
    endFrame();
      break;
    }

    switch(c) {
    case 72:                  // if up key is pressed throw lasso
	  lasso.unpause();break;
    case 80:                  // if down key is pressed yank lasso
	  lasso.yank();break;
    case 32:                  // if space bar is pressed loop lasso if it is not yanked
      if(!lasso.isPaused()) {
	   lasso.loopit();
	   int a1=lasso.check_for_coin(coinVect);  // check for coins caught
       if(a1==1 || a1==3){    //a1==1 means timeCoin was caught a1==2 means frenzyCoin was caught a1==3 means noth were caught
          remaining_time+=BONUS_TIME;
          runTime+=BONUS_TIME;
          frenzyTime +=BONUS_TIME;
          magnetTime +=BONUS_TIME;
          if(magnetStartTime!=-1)
             magnetStartTime += BONUS_TIME;
          for(int i=0;i<numTemp;i++){
          if(frenzyTimes[i]!=-10)
            frenzyTimes[i] += BONUS_TIME;
          }
       }
       if(a1==2 || a1==3){
         for(int i=0;i<numTemp;i++){                      // set the frenzy time times for all coins. These coins will unpause...
         frenzyTimes[i]=remaining_time-rand()%(10);// ...when the remaining time will be equal to the corresponding frenzy times.
         }
       }
      }break;
	case 75:                 // left key press makes lasso rotate cw
	  if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}break;
    case 77:                 // right key press makes lasso rotate acw
	  if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
    default:
	  break;
      }//end switch

  }//end if

beginFrame();
      lasso.nextStep(stepTime);       // move coins and lasso
    for(size_t i=0;i<coinVect.size();i++) coinVect[i]->nextStep(stepTime);

    if(lasso.isMagnetized() && magnetRemTime>0){
    if(magnetStartTime==-1){         // when lasso is just magnetized magnetStartTime will still be -1, would be set to the time that was remaing then
      magnetStartTime=remaining_time;
      colorScreen(179,255,179);      // and the colour of the screen is also changed for this duration
    }
    if(stepCount%20==0){             // stepCount increment 20 times in a second. once in 20 increments, or once in a second the time being dislayed will change
    sprintf(magnetTimer,"Magnet ends in %d second",MAGNET_TIME_SECONDS+remaining_time-magnetStartTime);
    magnetMessage.setMessage(magnetTimer);
    }
    lasso.magnetizeCoins(coinVect);  // magnetizeCoins method will orient the velocity ang acceleration of all coins at present towards the lasso
    magnetRemTime-=stepTime;
    }

    if(magnetRemTime<0){             // magnet timer just ran out
    colorScreen(255,255,204);        // change back screeen color to whatever it was before
    magnetMessage.setMessage("");    // hide the remeaining magnet time message
    magnetStartTime=-1;              // reset startTime to -1
    lasso.unMagnetize(coinVect);     // change back velocity and acceleration of coins to norrmal
    magnetRemTime=MAGNET_TIME_SECONDS;// reset back magnetRemTime
    wait(3*stepTime);                // wait, appreciate
    }
endFrame();

    for(size_t i=0;i<coinVect.size();i++)                   //reset all out of bound(completely out of screen) coins to random positions
    if(!coinVect[i]->isPaused() && coinVect[i]->getYPos() > WINDOW_Y+SUPER_COIN_SIZE) {
      if(coinVect[i]->checkMode()!="Temp")
      coinVect[i]->resetRandCoin();
      else
      coinVect[i]->resetCoin();
    }

    if(coinVect[0]->isPaused()){coinVect[0]->unpause();}  //always unpause first regular/gold coin
    if(coinVect[1]->isPaused()){                          //unpause second reg/gold coin by a certain probability factor.
       if(rand()%(abs(remaining_time-60)*PROB_FACTOR/10+2)==0){coinVect[1]->unpause();}
    }
    if(coinVect[2]->isPaused()){                          //unpause third reg/gold coin half times as much as the second coin.
       if(rand()%(abs(remaining_time-60)*PROB_FACTOR/10+2)==0){coinVect[2]->unpause();}
    }
    if(rand()%(PROB_FACTOR*10)==0){                       // unpause the first two bombs together always.
    if(coinVect[3]->isPaused())
      coinVect[3]->unpause();
    if(coinVect[4]->isPaused())
      coinVect[4]->unpause();
    }
    if(coinVect[5]->isPaused())                           // unpause the third bomb 1.5 as much as the first two  bombs.
    if(rand()%(PROB_FACTOR*10)==0){
      coinVect[5]->unpause();
    }
    if(coinVect[6]->isPaused())                           // unpause the super coin by a certain probability factor.
    if(rand()%(PROB_FACTOR*20)==0){
      coinVect[6]->unpause();
    }
    if(coinVect[7]->isPaused())                           // check if timeCoin is paused?
    if(remaining_time == timeCoin){                       // check if current time is that at which the coin should be paused
    if(!lasso.isMagnetized()){                            // check if lasso is magnetized?
      coinVect[7]->unpause();                             // if not unpause the time coin and reset its unpause time.
      float temp = 1.7*runTime;                           // this is done so that time coin does not mess with time remaing for lasso to be magnetzed
      timeCoin=rand()%int(temp);
      }
      else{
      timeCoin+=10;                                       // else unPause the coins 10 seconds later
      }
    }
    if(coinVect[8]->isPaused())                           //unpause the frenzy coin if the time is right and frenzy is not alsready on and choose next time
    if(remaining_time == frenzyTime){
      coinVect[8]->unpause();
      float temp = runTime;
      frenzyTime=rand()%(int(temp));
    }
    for(int i=9;i<9+numTemp;i++){                         // check if the time is right for temporary coins created for frenzy to be unpaused
    if(frenzyTimes[i-9]==remaining_time)
      coinVect[i]->unpause();
    }
    if(coinVect.back()->isPaused()){                      // unpause the magnet coin if the time is right and choose next time
    if(remaining_time == magnetTime ){
     if(!lasso.isMagnetized())                            // dont unpause coin magnet if lasso is aready magnetize, but reset the time anyways
        coinVect.back()->unpause();
     float temp = runTime;
     magnetTime=rand()%(int(temp));}
    }


  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());// display score
    coinScore.setMessage(coinScoreStr);

  if(stepCount%20==0){                                    // change time every second
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


  wait(bufferTime);                                      // wait for bufferTime
  if((runTime > 0) && (currTime > runTime)) {
   diplaySeconds.setMessage("00");                       // if timer runsout display 0 seconds remaining
   for(size_t i=0;i<coinVect.size();i++) delete coinVect[i]; // delete all coins on stack so they dont linger around on later screens
   break;
   }

  }//end while

  outFile.open("Data.txt",ios::app);
  outFile<<"1 "<<lasso.getNumCoins()<<endl;                     // output the score to the data file
  outFile.close();
  curr_screen='P';prev_screen='A';                                             // set currscreen to postGame and lastSCreen to arcade
  return;
}//end main
