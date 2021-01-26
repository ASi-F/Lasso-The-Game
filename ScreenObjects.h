#ifndef __SCREENOBJECTS_H__
#define __SCREENOBJECTS_H__

#include<simplecpp>
#include "lasso.h"

#define EXIT_X_WIDTH 20
#define EXIT_Y_WIDTH 20
#define EXIT_X WINDOW_X-40
#define EXIT_Y 40

#define CONTINUE_X_WIDTH 50
#define CONTINUE_Y_WIDTH 50
#define CONTINUE_X WINDOW_X/2
#define CONTINUE_Y WINDOW_Y/1.5

#define LEVEL_X WINDOW_X/2
#define LEVEL_Y WINDOW_Y/1.5
#define LEVEL_S 50
#define LEVEL_OFFSET 10

class ScreenObjects{
Line exit1,exit2;
Rectangle exitr,drawcont,level;
Text wlasso,levelt,*score_c,*score_b;
Turtle tr;

public:
  ScreenObjects(){
  tr.hide();tr.penUp();
  }
  //ScreenObjects()
  void drawExit();
  bool checkExit(int);

  void writeLasso();
  void colorScreen(int,int,int);
  void drawFrame(double,double);

  void drawContinue();
  bool checkContinue(int);

  void drawLevel(int);
  void drawChoose();
  int checkLevel(int);

  void enterName();
};

#endif
