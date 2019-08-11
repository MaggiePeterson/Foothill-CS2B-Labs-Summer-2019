//
//  Shapes.cpp
//  Screen
//
//  Created by Anand Venkataraman on 1/5/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//
#include <iostream>
#include <sstream>

using namespace std;

#include "Shapes.h"

// --------- Screen methods -----------------------------
Screen::Screen(int w, int h) : width(w), height(h) {

   clear();
}

void Screen::fill(char ch) {

   if(!pixels.size()){ //if empty, populate
      for(int i = 0; i < height; i++){
         vector<char>rows;
         for(int j = 0; j<width; j++){
            rows.push_back(ch);
         }
         pixels.push_back(rows);
      }
   }
   else { //if filled, replace
      for(int i = 0; i < height; i++){
         vector<char>rows;
         for(int j = 0; j<width; j++){
            rows.push_back(ch);
         }
         pixels[i] = rows;

      }
   }
}

string Screen::toString() const{

   string screen;

   for(int i = height-1; i >= 0 ; i--){
      for(int j = 0; j < width; j++){
         screen += pixels[i][j];
      }
      screen += "\n";
   }

   return screen;
}

// Output the screen on the given stream.
ostream& operator<<(ostream& os, const Screen& scr) {

   os<<scr.toString()<<endl;

   return os;
}

bool Screen::drawPoint(int x, int y, char ch){

   if(x >= width || x < 0 || y >= width || y <0)
      return false;

   for(int i = 0; i < this->height; i++){

      if( i == y){
         for(int j = 0; j < this->width; j++){
            if(j == x){
               pixels[i][j] = ch;
               break;
            }
         }
      }
   }

   return true;
}

// @override virtual shape method - Public API call.
// Draw this line on the given screen. Always draw left to right,
// and bottom to top if vertical. Use the supplied char ch as the



// --------- Point methods -----------------------------

// @override virtual shape method - Public API call.
bool Point::draw(Screen& scr, char ch) {

   return scr.drawPoint(this->x, this->y, ch);
}


// pixel char
bool Line::draw(Screen& scr, char ch) {

   if (x2 < x1 || (x2 == x1 && y2 < y1))
      return drawLine(scr, x2, y2, x1, y1, ch);
   return drawLine(scr, x1,y1, x2,y2, ch);

}

bool Line::drawByY(Screen& scr,int x1, int y1, int x2, int y2, char ch) {

   double dx = (double) (x2-x1)/abs(y2-y1);
   double dy = y2>y1 ? 1 : -1;

   bool contained = true;

   double x = x1, y = y1;
   int yDiff = abs(y2-y1);
   while(yDiff-- >= 0) {
      contained &= Point((int) x, (int) y).draw(scr, ch);
      x += dx;
      y += dy;
   }

   return contained;
}

bool Line::drawByX(Screen& scr, int x1, int y1, int x2, int y2, char ch){

   double dx = x2>x1 ? 1 : -1;
   double dy = (double) (y2-y1)/abs(x2-x1);

   bool contained = true;
   double x = x1, y = y1;

   int xDiff = abs(x2-x1);
   while(xDiff-- >= 0) {
      contained &= Point((int)x, (int)y).draw(scr, ch);
      x += dx;
      y += dy;
   }
   return contained;

}

bool Line::drawLine(Screen& scr, int x1, int y1, int x2, int y2,char ch) {

   if (abs(x2-x1) > abs(y2-y1))
      return drawByX(scr, x1,y1, x2,y2, ch);
   return drawByY(scr, x1,y1, x2,y2, ch);
}

//Quadrilateral------------
bool Quadrilateral::draw(Screen& scr, char ch){

   bool contained = true;
   contained &= Line(x1,y1,x2,y2).draw(scr,ch);
   contained &= Line(x2,y2,x3,y3).draw(scr,ch);
   contained &= Line(x3,y3,x4,y4).draw(scr,ch);
   contained &= Line(x4,y4,x1,y1).draw(scr,ch);

   return  contained;
}

//UpRightRectangle--------
bool UprightRectangle::draw(Screen& scr, char ch){

   bool contained = true;

   contained &= Line(x1,y1,x1,y2).draw(scr,ch);
   contained &= Line(x1,y2,x2,y2).draw(scr,ch);
   contained &= Line(x2,y2,x2,y1).draw(scr,ch);
   contained &= Line(x1,y1,x2,y1).draw(scr,ch);

   return contained;


}


//stickMan---------------

StickMan::StickMan(int x, int y, int w, int h) {

   this->x = x;
   this->y = y;

   width = w <= 1? DEFAULT_W : w;
   height = h <= 1? DEFAULT_H : h;

    head = new UprightRectangle(x,y+height/2,x+width-1,y+height-1);
    torso = new Line(x+width/2, y+height/4, x+width/2, y+height/2);
    leg1 =  new Line(x+width/2, y+height/4, x, y);
    leg2 = new Line(x+width/2, y+height/4,x+width-1, y);
    arm1 = new Line(x+width/2, y+height/2, x+width/4,y+height/4);
    arm2 = new Line(x+width/2, y+height/2,x+3*width/4,y+height/4);

   parts.push_back(head);
   parts.push_back(torso);
   parts.push_back(leg1);
   parts.push_back(leg2);
   parts.push_back(arm1);
   parts.push_back(arm2);
   
}

bool StickMan::draw(Screen& scr, char ch){

   bool contained = true;

   for(int i = 0; i < parts.size(); i++){

      contained &= parts[i]->draw(scr,ch);
   }

   return contained;
}



