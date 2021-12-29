#include "screens.h"
#include "lasso.h"


void screens::classicModeInstructions(){
  double y = 20;                         //gap between document ang upper window boudary
  double width = 20;                     // gap between cosecutive lines
  colorScreen(255,255,240);

beginFrame();
    Rectangle exitr;                     //Draw Exit
    Line exit1,exit2;
    exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
    int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
    exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
    exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

    //Draw dummy coins to explain their features.
    Coin goldCoin(WINDOW_X/2 , y+width*3-COIN_SIZE ,"Regular");
    Coin bomb(WINDOW_X/2 , y+width*7-COIN_SIZE ,"Bomb");

  Text temp;
  string line;
  inFile.open("classicModeInstructions.txt");
  while(!inFile.eof()){                    //print the arcade mode instructions to the screen untill the screen size runs out or document ends
    getline(inFile,line);
    temp.reset(WINDOW_X/2,y,line);
    y+=width;
    temp.imprint();
  }
  inFile.close();
endFrame();

  XEvent e;
  nextEvent(e);
  while(true){                         //Check for clicks
    bool pendingEvent = checkEvent(e);
    if(pendingEvent)
    if(checkExit(e)){curr_screen='L';prev_screen='c';return;}  //send user to preGameScreen if he/she presses exit
  }
}

