#include "screens.h"
#include "lasso.h"

void screens::postGame(){
  string name;
  char mode;
  string bestPlayer[3];
  int guard;
  int high_score[3]={-1000};                               //Initialising these variables to unrealisicallly low values
  int score{-1000};
  int personal_h_score{-1000};

  colorScreen(0,176,178);

beginFrame();
    Rectangle exitr;                      //Draw Exit
    Line exit1,exit2;
    exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
    exitr.setColor(COLOR(255,255,255));
    exitr.setFill(true);
    int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
    exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
    exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);

  writeLasso(WINDOW_X/2-125,WINDOW_Y*0.15,10);        //Write Lasso on the screen
  if(prev_screen=='C')
  writeClassic(WINDOW_X/2+135,WINDOW_Y*0.15,10);       // Write the mode of the played game on the screen
  else if(prev_screen=='A')
  writeArcade(WINDOW_X/2+125,WINDOW_Y*0.15,10);
endFrame();

  inFile.open("Data.txt");
  /*Here we input name, mode,gaurd and score consecutively. Thse represent the data from previous games played. For games played in the same mode we increment
  we compare the scores to find the high_score and the highest scorer among all the players and scores with the same name as our player to find the personal high score of our
  player. gaurd is the number after the mode in data file. if gaurd is 1 then there is no score entered after it. This prevents the program from crashing if the score
  was not saved in a previous game for some reason such as shutting down the canvas externally in middle of game.
  */
  while(!inFile.eof()){
    inFile>>name>>mode>>guard;
    if(guard == 11){
    inFile>>score;
    if(mode==prev_screen && score>high_score[0]) {
      high_score[0]=score;
      bestPlayer[0]=name;}
    if(mode==prev_screen && name==player_name && score>personal_h_score)
      personal_h_score=score;
      }
  }
  inFile.close();inFile.open("Data.txt");
  //Here we are finding the name and score of the second best.
  while(!inFile.eof()){
    inFile>>name>>mode>>guard;
    if(guard == 11){
    inFile>>score;
    if(name!=bestPlayer[0] && mode==prev_screen && score>high_score[1]) {
      high_score[1]=score;
      bestPlayer[1]=name;}
      }
  }
   inFile.close();inFile.open("Data.txt");
  //Here we are finding the name and score of the third best.
  while(!inFile.eof()){
    inFile>>name>>mode>>guard;
    if(guard == 11){
    inFile>>score;
    if(name!=bestPlayer[0] && name!=bestPlayer[1] && mode==prev_screen && score>high_score[2]) {
      high_score[2]=score;
      bestPlayer[2]=name;}
      }
  }
  inFile.close();
beginFrame();
  char display_score[256];
  int cx = WINDOW_X/2,cy = WINDOW_Y/2-150;
  Rectangle r0(cx,cy,300,25);r0.setColor(COLOR(255,255,255));r0.setFill(true);        //Display message game over
  Text t0(cx,cy,"GAME OVER");

  Rectangle r1(cx,cy+50,300,25);r1.setColor(COLOR(255,255,255));r1.setFill(true);     // DIsplay player name
  Text t1(cx,cy+50,player_name);

  sprintf(display_score,"Your current score was %d",score);                           // Display player Score
  Rectangle r2(cx,cy+100,300,25);r2.setColor(COLOR(255,255,255));r2.setFill(true);
  Text t2(cx,cy+100,display_score);

  Rectangle r3(cx,cy+150,300,25);r3.setColor(COLOR(255,255,255));r3.setFill(true);
  sprintf(display_score,"Persoal High score is %d",personal_h_score);                 //Dislay personal hogh core
  Text t3(cx,cy+150,display_score);

  Rectangle r4; Text t4;                                                              //Declared r6 and t6 outside fucnction...
  if(score==personal_h_score ){                                                       //...so that they dont run out of scope
  r4.reset(cx,cy+200,300,25);r4.setColor(COLOR(255,255,255));r4.setFill(true);
  string new_h_score = player_name + "  You have a new high score !";
  t4.reset(cx,cy+200,new_h_score);
  }

  Rectangle R0(cx,cy+310,250,150);R0.setColor(COLOR(255,255,255));R0.setFill(true);
  Text T0(cx,cy+250,"LEADERBOARD");                                                                  //      LEADERBOARD
  Text T1(cx,cy+285,"#RANK      NAME      SCORE");                                                   //#RANK   NAME    SCORE
  Text y0,y1,y2,t5,t6,t7,l0,l1,l2;                                                                   // # 1    PLYR1    XY
  if(high_score[0]!=-1000){                                                                           // # 2    PLYR2    PQ
    y0.reset(cx-70,cy+310,"# 1");t5.reset(cx,cy+310,bestPlayer[0]);l0.reset(cx+70,cy+310,high_score[0]);}// # 3    PLYR3    MN
  if(high_score[1]!=-1000){
    y1.reset(cx-70,cy+335,"# 2");t6.reset(cx,cy+335,bestPlayer[1]);l1.reset(cx+70,cy+335,high_score[1]);}
  if(high_score[2]!=-1000){
    y2.reset(cx-70,cy+360,"# 3");t7.reset(cx,cy+360,bestPlayer[2]);l2.reset(cx+70,cy+360,high_score[2]);}
  if(high_score[1]==high_score[0])
    y1.setMessage("# 1");
  if(high_score[1]==high_score[2] && high_score[2]!=high_score[0])
    y2.setMessage("# 2");
  if(high_score[1]==high_score[2] && high_score[2]==high_score[0])
    {y1.setMessage("# 1");y2.setMessage("# 1");}

  compressData();
endFrame();
  XEvent e;
  nextEvent(e);
  while(true){
    bool pendingEvent=checkEvent(e);
    if(pendingEvent)
    if(checkExit(e)){curr_screen='H';prev_screen='P';return;}
  }

}
