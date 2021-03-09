#include "screens.h"

using namespace simplecpp;


void screens::writeLasso(double cx, double cy, double sizeFactor){ //Write LASSO with help of rectangle, st colour to be red
  double a = sizeFactor;  // for easy notation
   Rectangle r[20];
  r[0].reset(cx-9*a,cy,a,4*a);  // L
  r[1].reset(cx-8*a,cy+1.5*a,3*a,a);
  r[2].reset(cx-4*a,cy-1.5*a,3*a,a); //A
  r[3].reset(cx-4*a,cy+0.5*a,3*a,a);
  r[4].reset(cx-5*a,cy,a,4*a);
  r[5].reset(cx-3*a,cy,a,4*a);
  r[6].reset(cx-a,cy-0.75*a,a,2.5*a); //S
  r[7].reset(cx+a,cy+0.75*a,a,2.5*a);
  r[8].reset(cx,cy,3*a,a);
  r[9].reset(cx,cy-1.5*a,3*a,a);
  r[10].reset(cx,cy+1.5*a,3*a,a);
  r[11].reset(cx+3*a,cy-0.75*a,a,2.5*a);//S
  r[12].reset(cx+5*a,cy+0.75*a,a,2.5*a);
  r[13].reset(cx+4*a,cy,3*a,a);
  r[14].reset(cx+4*a,cy-1.5*a,3*a,a);
  r[15].reset(cx+4*a,cy+1.5*a,3*a,a);
  r[16].reset(cx+8*a,cy+1.5*a,3*a,a);//0
  r[17].reset(cx+8*a,cy-1.5*a,3*a,a);
  r[18].reset(cx+9*a,cy,a,4*a);
  r[19].reset(cx+7*a,cy,a,4*a);
  for(int i=0;i<20;i++){r[i].setColor(COLOR(255,0,0));r[i].setFill(true);r[i].imprint();}
}

void screens::writeArcade(double cx,double cy, double sizeFactor){ //write ARCADE with help of rectangles. St colour to be red
double a = sizeFactor;    // for easy notation
Rectangle r[24];
  r[0].reset(cx-10*a,cy-1.5*a,3*a,a);     //A
  r[1].reset(cx-10*a,cy+0.5*a,3*a,a);
  r[2].reset(cx-11*a,cy,a,4*a);
  r[3].reset(cx-9*a,cy,a,4*a);
  r[4].reset(cx-7*a,cy,a,4*a);            //R
  r[5].reset(cx-6*a,cy-1.5*a,3*a,a);
  r[6].reset(cx-6*a,cy,3*a,a*0.8);
  r[7].reset(cx-5*a,cy-a,a,2*a);
  r[8].reset(cx-5.5*a,cy+a,a*0.8,2.5*a);r[8].left(45);
  r[9].reset(cx-3*a,cy,a,4*a);          //C
  r[10].reset(cx-2*a,cy+1.5*a,3*a,a);
  r[11].reset(cx-2*a,cy-1.5*a,3*a,a);
  r[12].reset(cx+2*a,cy-1.5*a,3*a,a);     //A
  r[13].reset(cx+2*a,cy+0.5*a,3*a,a);
  r[14].reset(cx+a,cy,a,4*a);
  r[15].reset(cx+3*a,cy,a,4*a);cx+=0.5*a;
  r[16].reset(cx+5*a,cy,a,4*a);         //D
  r[17].reset(cx+5.25*a,cy-1.5*a,2.5*a,a);
  r[18].reset(cx+5.25*a,cy+1.5*a,2.5*a,a);
  r[19].reset(cx+7*a,cy,a,2*a);
  r[20].reset(cx+9*a,cy,a,4*a);          //E
  r[21].reset(cx+10*a,cy-1.5*a,3*a,a);
  r[22].reset(cx+10*a,cy+1.5*a,3*a,a);
  r[23].reset(cx+10.37*a,cy,2.5*a/2,1*a);
  for(int i=0;i<24;i++){
  r[i].setColor(COLOR(255,0,0));
  r[i].setFill(true);r[i].imprint();
  }
}
void screens::writeClassic(double cx, double cy, double sizeFactor){// Write CLASSIC with help of rectangles. Set colour to be red
  double a =sizeFactor;              // for easy notation
  Rectangle r[25];
  r[0].reset(cx-13*a,cy,a,4*a);//C
  r[1].reset(cx-12*a,cy+1.5*a,3*a,a);
  r[2].reset(cx-12*a,cy-1.5*a,3*a,a);
  r[3].reset(cx-9*a,cy,a,4*a);//L
  r[4].reset(cx-8*a,cy+1.5*a,3*a,a);
  r[5].reset(cx-4*a,cy-1.5*a,3*a,a); //A
  r[6].reset(cx-4*a,cy+0.5*a,3*a,a);
  r[7].reset(cx-5*a,cy,a,4*a);
  r[8].reset(cx-3*a,cy,a,4*a);
  r[9].reset(cx-a,cy-0.75*a,a,2.5*a); //S
  r[10].reset(cx+a,cy+0.75*a,a,2.5*a);
  r[11].reset(cx,cy,3*a,a);
  r[12].reset(cx,cy-1.5*a,3*a,a);
  r[13].reset(cx,cy+1.5*a,3*a,a);
  r[14].reset(cx+3*a,cy-0.75*a,a,2.5*a); //S
  r[15].reset(cx+5*a,cy+0.75*a,a,2.5*a);
  r[16].reset(cx+4*a,cy,3*a,a);
  r[17].reset(cx+4*a,cy-1.5*a,3*a,a);
  r[18].reset(cx+4*a,cy+1.5*a,3*a,a);
  r[19].reset(cx+8*a,cy,a,4*a);//I
  r[20].reset(cx+8*a,cy+1.5*a,3*a,a);
  r[21].reset(cx+8*a,cy-1.5*a,3*a,a);
  r[22].reset(cx+11*a,cy,a,4*a);//C
  r[23].reset(cx+12*a,cy+1.5*a,3*a,a);
  r[24].reset(cx+12*a,cy-1.5*a,3*a,a);
  for(int i=0;i<25;i++){
  r[i].setColor(COLOR(255,0,0));
  r[i].setFill(true);r[i].imprint();
  }
}


