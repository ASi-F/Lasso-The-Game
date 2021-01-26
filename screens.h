#ifndef __SCREENS_H__
#define __SCREENS_H__

#include<simplecpp>
#include "lasso.h"
#include "ScreenObjects.h"
#include<cstdio>
#include<cstdlib>
#include<fstream>

class screens{
ScreenObjects ScrObj;
std::ifstream inFile;
std::ofstream outFile;
char x;
string player_name;
public:
  screens(){x='H';
  inFile.open("Data.txt");
  outFile.open("Data.txt",ios::app);
  player_name="";
  }

 void homeScreen();
 void LevelScreen();
 void Classic();
 void Arcade();
 void postGame();

 char checkx(){return x;}
};

#endif
//g++ -std=c++11 -Wall -o lasso lasso.cpp MovingObject.cpp coin.cpp ScreenObjects.cpp screens.cpp Classic.cpp Arcade.cpp main.cpp -lsprite -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
