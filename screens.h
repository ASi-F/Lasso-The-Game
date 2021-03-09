#ifndef __SCREENS_H__
#define __SCREENS_H__

#include<simplecpp>
#include "lasso.h"
#include<fstream>

#define MAX_NAME_LENGTH 8
#define EXIT_X_WIDTH 20
#define EXIT_Y_WIDTH 20
#define EXIT_X WINDOW_X-40
#define EXIT_Y 40

#define CONTINUE_X_WIDTH 50
#define CONTINUE_Y_WIDTH 50
#define CONTINUE_X WINDOW_X/2
#define CONTINUE_Y WINDOW_Y*3/4


class screens{
std::ifstream inFile;
std::ofstream outFile;
char curr_screen,prev_screen;
string player_name;
bool data_deleted;
public:
  screens(char currScreen,char prevScreen,string playerName, bool dataDeleted):curr_screen(currScreen),prev_screen(prevScreen),player_name(playerName),data_deleted{dataDeleted}{}

  void homeScreen();                // H
  void preGameScreen();             // L
  void postGame();                  // P
  void infoScreen();                // I
  void classicModeInstructions();   // c
  void arcadeModeInstructionsP1();  // 1
  void arcadeModeInstructionsP2();  // 2
  void Classic();                   // C
  void Arcade();                    // A

  char getCurrScreen(){return curr_screen;}
  char getPrevScreen() {return prev_screen;}
  string getPlayerName() {return player_name;}
  bool getDataDel() {return data_deleted;}

  bool checkClick(XEvent e,double cx,double cy,double lenx,double leny);
  void colorScreen(int r,int g,int b);
  bool checkExit(XEvent e){ return checkClick(e,EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);}

  void writeLasso(double cx,double cy,double sizeFactor);
  void writeArcade(double cx,double cy,double sizeFactor);
  void writeClassic(double cx,double cy,double sizeFactor);
  
  void compressData();
};

#endif
//g++ -std=c++11 -Wall -o lasso lasso.cpp MovingObject.cpp coin.cpp BigWords.cpp screens.cpp HomeScreen.cpp  preGameScreen.cpp InfoScreen.cpp classicInstr.cpp arcadeInstr.cpp postGame.cpp Classic.cpp Arcade.cpp main.cpp -lsprite -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
