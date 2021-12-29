#include "screens.h"
#include "lasso.h"

void screens::preGameScreen(){
  beginFrame();
    colorScreen(255,204,0);

    for(int i=0;i<=10;i++)
    for(int j=0;j<=10;j++){
      Circle c(WINDOW_X*i/10,WINDOW_Y*j/10,50);
      c.setColor(COLOR(255, 224, 102));
      c.imprint();
    }

    Rectangle *namer = new Rectangle;   //Draw widow to enter name
    double cx=WINDOW_X/2;
    double cy=WINDOW_Y/2-150;
    double lx=200;
    double ly=50;
    namer->reset(cx,cy,lx,ly);
    namer->setColor(COLOR(255,255,255));
    namer->setFill(true);
    namer->imprint();
    namer->setColor(COLOR(0,0,0));namer->setFill(false);namer->imprint();

    //HERE WE have written some text and drawn rectangles around them ourselves for a better look. WE have used namer rectangle pointer here previously created
    //for no special reason
    namer->reset(cx,cy-ly,300,25);namer->setColor(COLOR(255,255,255));namer->setFill(true);namer->imprint();delete namer;
    Text namet(cx,cy-ly," Click BELOW to Enter your name: ");
    Rectangle chooser(WINDOW_X/2,WINDOW_Y/2.2,250,25);chooser.setColor(COLOR(255,255,255));chooser.setFill(true);
    Text choose(WINDOW_X/2,WINDOW_Y/2.2," Click on a MODE to play ");
    Rectangle chooser1(WINDOW_X/2,WINDOW_Y/2.2+50,300,25);chooser1.setColor(COLOR(255,255,255));chooser1.setFill(true);
    Text choose1(WINDOW_X/2,WINDOW_Y/2.2+50," Or click below to READ INSTRUCTIONS ");

    double arcadeCx=WINDOW_X/2-200;
    double classicCx=WINDOW_X/2+200;
    double centy=WINDOW_Y/1.5;
    double sizef=10;
    writeArcade( arcadeCx, centy, sizef );  //Wrie classic and arcade symbols in bold
    writeClassic( classicCx, centy, sizef );

    double arcadeiCx=arcadeCx;
    double arcadeiCy=centy+5*sizef;
    double lenaiCx=23*sizef;
    double leniCy=3*sizef;
    Rectangle arcadeinstr(arcadeiCx,arcadeiCy,lenaiCx,leniCy);
    arcadeinstr.setColor(COLOR(255,255,255));arcadeinstr.setFill(true);arcadeinstr.imprint();
    arcadeinstr.setColor(COLOR(0,0,0));arcadeinstr.setFill(false);
    Text arc(arcadeiCx,arcadeiCy,"Instructions for Arcade Mode");  //Draw instructions menu for Arcade mode

    double classiciCx=classicCx;
    double classiciCy=centy+5*sizef;
    double lenciCx=27*sizef;
    Rectangle classicinstr(classiciCx,classiciCy,lenciCx,leniCy);
    classicinstr.setColor(COLOR(255,255,255));classicinstr.setFill(true);classicinstr.imprint();
    classicinstr.setColor(COLOR(0,0,0));classicinstr.setFill(false);
    Text clas(classiciCx,classiciCy,"Instructions for Classic Mode");  //Draw instructions menu for classic mode

    Rectangle exitr;                                                   //Draw exit symbol
    Line exit1,exit2;
    exitr.reset(EXIT_X,EXIT_Y,EXIT_X_WIDTH,EXIT_Y_WIDTH);
    exitr.setColor(COLOR(255,255,255));
    exitr.setFill(true);
    int tempx=EXIT_X-EXIT_X_WIDTH/4,tempy=EXIT_Y-EXIT_Y_WIDTH/4;
    exit1.reset(tempx,tempy,tempx+EXIT_X_WIDTH/2,tempy+EXIT_Y_WIDTH/2);
    exit2.reset(tempx+EXIT_X_WIDTH/2,tempy,tempx,tempy+EXIT_Y_WIDTH/2);
 endFrame();

  string name=player_name; //initialise name to default player name
  Text tname(cx,cy,"");

  while(true){
     XEvent e;
    bool pendingEvent=checkEvent(e);
    player_name=name;
    tname.setMessage(name);  //display username

    if(pendingEvent){
    if(checkClick(e,cx,cy,lx,ly) && name==player_name){  // if user has clicked to change his player_name
     Rectangle instrr(cx,cy+ly,200,25);instrr.setColor(COLOR(255,255,255));instrr.setFill(true);
     name="";                                           // clear the current name
     Text instrct(cx,cy+ly," Too short !  ");
     tname.setMessage(name);                             
     nextEvent(e);
     while(!keyPressEvent(e)){nextEvent(e);}             //wait for key presses
     while(charFromEvent(e) != 13 || name==""){          // repeat while user does not press enter or if the user hasn't entered anything
       if(charFromEvent(e)!=13 && charFromEvent(e)!=8 && charFromEvent(e)!=32 && name.size()<MAX_NAME_LENGTH)  // (8 or backspace is not interpretted properly,32 or space causes problems)
         name.push_back(charFromEvent(e));               // add the typed character to name
       else if(charFromEvent(e)==8 && name.size()!=0)    // if backspace delete last char if string is not null
         name.pop_back();
       if(name.size()==MAX_NAME_LENGTH){
         instrct.setMessage("Too long!");
       }else if(name.size()==0){
         instrct.setMessage("Too short!");
        }
       else
         instrct.setMessage(" Press Enter !  ");
       tname.reset(cx,cy,name);                          // now display the name with the additional character just typed
       nextEvent(e);
       while(!keyPressEvent(e)){nextEvent(e);}           // waitfor next keyPressEvent
     }
    }//endif

    if(checkExit(e)){
      curr_screen='H';prev_screen='L';return;            // if user presses exit go back to homescreen
    }//check is user has clicked on instructions for arcade mode, if yes send them to first page of instructions
    if(checkClick(e,arcadeiCx,arcadeiCy,lenaiCx,leniCy)){curr_screen='1';prev_screen='L';break;}
    if(checkClick(e,classiciCx,classiciCy,lenciCx,leniCy)){curr_screen='c';prev_screen='L';break;}//similarly for classic mode instructions
    //if user presses on arcade mode.Note that we hare out puttting the data of the user to the data file only when they start playing one of the modes.
    // In each mode(C/A) the final output to data file is the playerScore no matter what. This helps us aintain data in form of ...username->mode->scoe->...
    // in the data file to avoid any errors.
    if(checkClick(e,arcadeCx,centy,23*sizef,4*sizef)){
        curr_screen='A';prev_screen='L';player_name=name;  //set current screen, preious screen, palyername
        outFile.open("Data.txt",ios::app);
        outFile<<" "<<name<<" ";                               // output name to data file
        outFile<<curr_screen<<" 1";                        // out put the mode chosen to Data file
        outFile.close();
        break;}
    if(checkClick(e,classicCx,centy,23*sizef,4*sizef)){     // Similar to above
        curr_screen='C';prev_screen='L';player_name=name;
        outFile.open("Data.txt",ios::app);
        outFile<<" "<<name<<" ";
        outFile<<curr_screen<<" 1";
        outFile.close();
        break;}
   }
   }//end inf loop
}
