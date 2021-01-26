#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include<cstdio>
#include<cstdlib>
#include "lasso.h"
#include "coin.h"
#include "screens.h"
#include "ScreenObjects.h"

using namespace simplecpp;

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  char screenCheck='H';


  while(true){
  screens game;
  switch(screenCheck){
    case 'H':
    game.homeScreen();break;
    case 'L':
    game.LevelScreen();break;
    case 'P':
    game.postGame();break;
    case 'C':
    game.Classic();break;
    case 'A':
    game.Arcade();break;
    }
  screenCheck=game.checkx();
  //cout<<screenCheck;
  }
}

