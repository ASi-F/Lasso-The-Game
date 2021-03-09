#include "screens.h"
#include "lasso.h"
#include<vector>

//Checks for an event e, if a click is detected in a rectangle centred cx,cy and dimensions lx,ly
 bool screens::checkClick(XEvent e,double cx,double cy,double lenx,double leny){
   double x0=e.xbutton.x;
   double y0=e.xbutton.y;
   double minX = cx-lenx/2;
   double maxX = cx+lenx/2;
   double minY = cy-leny/2;
   double maxY = cy+leny/2;

   return minX<x0 && x0<maxX && minY<y0 && y0<maxY;
}
//Colors the screen correspoding to the rgb values
void screens::colorScreen(int r, int g, int b){
  Rectangle *colscr = new Rectangle;
  colscr->reset(WINDOW_X/2,WINDOW_Y/2,WINDOW_X+1,WINDOW_Y+1);
  colscr->setColor(COLOR(r,g,b));
  colscr->setFill(true);
  colscr->imprint();
  delete colscr;
}


//This struct is solely for the ease of writing the below function
struct gamedata{
  string name;char ch;int gaurd;int score;
  };


// USeful data has gaurd=11 and useless data has gaurd =1
//Compress the data file to store only the previous high scores of all players.
void screens::compressData(){
  inFile.open("Data.txt");
  string name;char ch;int num1,num2;
  vector<gamedata> data;
  //copy useful data from data file to data vector
  while(!inFile.eof()){
  inFile>>name>>ch>>num1;
  if(num1==11){
  inFile>>num2;
  data.push_back(gamedata{name,ch,num1,num2});
  }
  }
  inFile.close();
  //Compare data from games of same player for  each mode and mark all games with score less than highest score as useless
  for(size_t i=0;i<data.size();i++)
  for(size_t j=i+1;j<data.size();j++)
    if(data[i].name == data[j].name  && data[i].ch == data[j].ch){
      if(data[i].score > data[j].score){ data[j].gaurd=1;}
      else{data[i].gaurd=1;}
  }

//Clear data file
//Transfer useful data for arcade mode back to data file
  outFile.open("Data.txt");
  for(size_t i=0;i<data.size();i++)
    if(data[i].gaurd==11 && data[i].ch=='A')
      outFile<<" "<<data[i].name<<" "<<data[i].ch<<" "<<data[i].gaurd<<" "<<data[i].score<<endl;
    outFile<<endl;
  outFile.close();
//Transfer useful data for classic mode back to data file
  outFile.open("Data.txt",ios::app);
  for(size_t i=0;i<data.size();i++)
    if(data[i].gaurd==11 && data[i].ch=='C')
      outFile<<" "<<data[i].name<<" "<<data[i].ch<<" "<<data[i].gaurd<<" "<<data[i].score<<endl;
  outFile.close();
}
