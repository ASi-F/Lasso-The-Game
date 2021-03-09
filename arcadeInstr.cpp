#include "screens.h"
#include "lasso.h"


void screens::arcadeModeInstructionsP1(){
  double y = 20;                        //gap between document ang upper window boudary
  double width = 20;                    // gap between cosecutive lines
  colorScreen(255,255,240);

beginFrame();
    Rectangle exitr;                    //Draw Exit
    Line exit1,exit2;
    exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
    int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
    exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
    exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

    double nextCx=WINDOW_X-CONTINUE_X_WIDTH; //Draw Next button
    double nextCy=WINDOW_Y-CONTINUE_Y_WIDTH;
    Rectangle playbtn(nextCx,nextCy,CONTINUE_X_WIDTH,CONTINUE_Y_WIDTH);
    playbtn.setColor(COLOR(0, 255,0));
    playbtn.setFill(true);
    Turtle tr;
    tr.hide();tr.penUp();
    tr.moveTo(nextCx-8,nextCy);
    tr.show();
    Text next(nextCx,nextCy+CONTINUE_Y_WIDTH/1.3,"Next");

    //Draw dummy coins to explain their features.
    Coin goldCoin(WINDOW_X/2 , y+width*5-COIN_SIZE , "Regular");
    Coin bomb(WINDOW_X/2 , y+width*9-COIN_SIZE , "Bomb");
    Coin time(WINDOW_X/2 , y+width*13-COIN_SIZE , "Time");
    Coin frenzy(WINDOW_X/2 , y+width*17-COIN_SIZE ,"Frenzy");
    Coin magnet(WINDOW_X/2 , y+width*21-COIN_SIZE ,"Magnet");
    Coin super(WINDOW_X/2 ,  y+width*26-COIN_SIZE ,"Super");

  Text temp;
  string line;
  inFile.open("arcadeModeInstructions.txt");
  while(y<WINDOW_Y  && !inFile.eof()){ //print the arcade mode instructions to the screen untill the screen size runs out or document ends
    getline(inFile,line);
    temp.reset(WINDOW_X/2,y,line);
    y+=width;
    temp.imprint();
  }
  inFile.close();
endFrame();

  XEvent e;
  nextEvent(e);
  while(true){                          //Check for clicks
    bool pendingEvent = checkEvent(e);
    if(pendingEvent)
    if(checkExit(e)){curr_screen='L';prev_screen='1';return;}   //send user to preGameScreen if he/she presses exit
    if(checkClick(e,nextCx,nextCy,CONTINUE_X_WIDTH,CONTINUE_Y_WIDTH)){curr_screen='2';prev_screen='1';return;} //send to next page if they press next
  }
}

void screens::arcadeModeInstructionsP2(){ //similar to page 1
  double y = 20;
  double width = 20;
  colorScreen(255,255,240);
beginFrame();
    Rectangle exitr;
    Line exit1,exit2;
    exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
    int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
    exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
    exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

    double backCx=CONTINUE_X_WIDTH;
    double backCy=WINDOW_Y-CONTINUE_Y_WIDTH;
    Rectangle playbtn(backCx,backCy,CONTINUE_X_WIDTH,CONTINUE_Y_WIDTH);
    playbtn.setColor(COLOR(0, 255,0));
    playbtn.setFill(true);
    Turtle tr;
    tr.hide();tr.penUp();
    tr.moveTo(backCx+8,backCy);tr.left(180);
    tr.show();
    Text backo(backCx,backCy+CONTINUE_Y_WIDTH/1.3,"Back");

    Text temp;
  string line;
  inFile.open("arcadeModeInstructions.txt");

  repeat(29) getline(inFile,line);  // skip first 29 lines

  while(y<WINDOW_Y  && !inFile.eof()){
    getline(inFile,line);
    temp.reset(WINDOW_X/2,y,line);
    y+=width;
    temp.imprint();
  }
  inFile.close();
endFrame();

  XEvent e;
  nextEvent(e);
  while(true){
    bool pendingEvent = checkEvent(e);
    if(pendingEvent)
    if(checkExit(e)){curr_screen='L';prev_screen='2';return;}
    if(checkClick(e,backCx,backCy,CONTINUE_X_WIDTH,CONTINUE_Y_WIDTH)){curr_screen='1';prev_screen='2';return;}
  }
}
