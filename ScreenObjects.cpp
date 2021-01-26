#include "ScreenObjects.h"

using namespace simplecpp;

void ScreenObjects::drawExit(){
  exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
  int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
  exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
  exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);
  }

bool ScreenObjects::checkExit(int temp){
  int tempx=temp/65536,tempy=temp%65536;
  return (EXIT_X-EXIT_X_WIDTH/2 < tempx && tempx<EXIT_X+EXIT_X_WIDTH/2 && EXIT_Y-EXIT_Y_WIDTH/2 < tempy && tempy<EXIT_Y+EXIT_Y_WIDTH/2);
}

void ScreenObjects::writeLasso(){
  wlasso.reset(WINDOW_X/2,WINDOW_Y/2,"LASSO - THE GAME");
}

void ScreenObjects::colorScreen(int r, int g, int b){
  Rectangle *colscr = new Rectangle;
  colscr->reset(WINDOW_X/2,WINDOW_Y/2,WINDOW_X+1,WINDOW_Y+1);
  colscr->setColor(COLOR(r,g,b));
  colscr->setFill(true);
  colscr->imprint();
  delete colscr;
}

void drawFrame(double width,double height){
  Rectangle *colscr = new Rectangle;
  colscr->reset(WINDOW_X/2,WINDOW_Y/2,width,height);delete colscr;
}

void ScreenObjects::drawContinue(){
  drawcont.reset(CONTINUE_X,CONTINUE_Y,CONTINUE_X_WIDTH,CONTINUE_Y_WIDTH);
  drawcont.setColor(COLOR(255,255,255));
  drawcont.setFill(true);
  tr.moveTo(CONTINUE_X-8,CONTINUE_Y);
  tr.show();
}

bool ScreenObjects::checkContinue(int temp){
  int tempx=temp/65536,tempy=temp%65536;
  return abs(tempx-CONTINUE_X) < CONTINUE_X_WIDTH/2 && abs(tempy-CONTINUE_Y)<CONTINUE_Y_WIDTH/2;
}

void ScreenObjects::drawLevel(int I){
  I-=3;
  level.reset(LEVEL_X+I*LEVEL_S+I*LEVEL_OFFSET,LEVEL_Y,LEVEL_S,LEVEL_S);
  level.imprint();
  char temp='1'+2+I;
  string tem=string(1,temp);
  levelt.reset(LEVEL_X+I*LEVEL_S+I*LEVEL_OFFSET,LEVEL_Y,tem);
  levelt.imprint();
}

void ScreenObjects::drawChoose(){
  levelt.reset(WINDOW_X/2,WINDOW_Y/2.2,"CHOOSE A LEVEL");levelt.imprint();
}



int ScreenObjects::checkLevel(int temp){
  int x=temp/65536,y=temp%65536;
  if(LEVEL_Y-LEVEL_S/2 < y && y<LEVEL_Y+LEVEL_S/2){
    x=x-LEVEL_X+5*LEVEL_S/2+2*LEVEL_OFFSET;
    for(int i=0;i<5;i++){
     if(i*(LEVEL_S+LEVEL_OFFSET)<x && x<i*(LEVEL_S+LEVEL_OFFSET)+LEVEL_S)
     return i+1;
    }
  }
  return -1;
}
 void ScreenObjects::enterName(){
   levelt.reset(WINDOW_X/2,WINDOW_Y/2-200,"Enter your name:");levelt.imprint();
   level.reset(WINDOW_X/2,WINDOW_Y/2-150,200,50);levelt.imprint();
 }

