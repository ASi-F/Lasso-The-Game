#include <simplecpp>
#include "screens.h"

using namespace simplecpp;

main_program {

  initCanvas("Lasso - The Game", WINDOW_X, WINDOW_Y);
  char currScreen='H';
  char prevScreen='H';
  string playerName="player1";
  bool dataDeleted = false;

  while(true){//create a new screen and initialise it with the information avaiable from the previous screen
  screens game(currScreen,prevScreen,playerName,dataDeleted);

  switch(currScreen){
    case 'H':
    game.homeScreen();break;
    case 'L':
    game.preGameScreen();break;
    case 'P':
    game.postGame();break;
    case 'I':
    game.infoScreen();break;
    case 'c':
    game.classicModeInstructions();break;
    case '1':
    game.arcadeModeInstructionsP1();break;
    case '2':
    game.arcadeModeInstructionsP2();break;
    case 'C':
    game.Classic();break;
    case 'A':
    game.Arcade();break;
    case 'Q':
    return 0;
    }
    //Store information of current screen befroe it runs out of scope
  currScreen=game.getCurrScreen();
  prevScreen=game.getPrevScreen();
  playerName=game.getPlayerName();
  dataDeleted=game.getDataDel();
  }
}

