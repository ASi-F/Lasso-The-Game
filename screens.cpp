#include "screens.h"
#include "lasso.h"


void screens::homeScreen(){
  beginFrame();
    ScrObj.colorScreen(255, 51, 255);
    ScrObj.writeLasso();
    ScrObj.drawContinue();
    ScrObj.drawExit();
  endFrame();

  while(true){
    int t=getClick();
    if(ScrObj.checkContinue(t)==true){ x = 'L' ;return ;}
    if(ScrObj.checkExit(t)){ x='O';return;}
             }
}// Exit HomeScreen

void screens::LevelScreen(){
  beginFrame();
    ScrObj.colorScreen(204, 51, 0);
    ScrObj.drawChoose();
    Rectangle arcade(WINDOW_X/2-200,WINDOW_Y/1.5,150,100);
    Text arc(WINDOW_X/2-200,WINDOW_Y/1.5,"ARCADE");
    Rectangle clas(WINDOW_X/2+200,WINDOW_Y/1.5,150,100);
    Text classic(WINDOW_X/2+200,WINDOW_Y/1.5,"CLASSIC");
    ScrObj.drawExit();
    ScrObj.enterName();
  endFrame();
  string name="player1";
  Text ti;
  wait(0.5);
  while(true){
  int a0=getClick();
    int x0=a0/65536,y0=a0%65536;
    if(-100<WINDOW_X/2-x0 && WINDOW_X/2-x0<100 && WINDOW_Y/2-150-y0<25 && -25<WINDOW_Y/2-150-y0 && name=="player1"){
     name="";
     XEvent e;
      nextEvent(e);
      while(!keyPressEvent(e)){
      nextEvent(e);
      }
      while(charFromEvent(e) != 13){
      cout<<charFromEvent(e);
        name.push_back(charFromEvent(e));
        ti.reset(WINDOW_X/2,WINDOW_Y/2-150,name);
        nextEvent(e);
      }
    }
      outFile<<name<<endl;
      ti.reset(WINDOW_X/2,WINDOW_Y/2-150,name);
      ti.imprint();
    if(ScrObj.checkExit(65536*x0+y0)){
      x='H';return;
    }
    if(WINDOW_X/2-275<x0 && x0<WINDOW_X/2-125 && WINDOW_Y/1.5-50<y0 &&  y0<WINDOW_Y/1.5+50){x='A';break;}
    if(WINDOW_X/2+125<x0 && x0<WINDOW_X/2+275 && WINDOW_Y/1.5-50<y0 &&  y0<WINDOW_Y/1.5+50){x='C';break;}

   }
   player_name=name;
}

void screens::postGame(){
  ScrObj.colorScreen(255,255,255);
  ScrObj.drawExit();
  string name;
  int high_score{-1000},score{0};
  while(!inFile.eof()){
  inFile>>name>>score;
  if(score>high_score)
    high_score=score;
  }
  char display_score[256];
  sprintf(display_score,"High score is %d",high_score);
  Text t1(WINDOW_X/2,WINDOW_Y/2,display_score);
  Text t2(WINDOW_X/2,WINDOW_Y/2-100,name);
  sprintf(display_score,"Your score was %d",score);
  Text t3(WINDOW_X/2,WINDOW_Y/2-50,display_score);
  while(true){
  int p = getClick();
  if(ScrObj.checkExit(p)){x='H';return;}

  }

}




//g++ -std=c++11 -Wall -o lasso lasso.cpp MovingObject.cpp coin.cpp ScreenObjects.cpp Level_1.cpp Level_2.cpp screens.cpp main.cpp -lsprite -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
