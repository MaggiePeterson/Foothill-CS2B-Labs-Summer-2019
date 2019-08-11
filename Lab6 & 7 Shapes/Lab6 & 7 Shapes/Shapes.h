//
//  Shapes.h
//  Project name: Screen
//
//  Created by Anand Venkataraman on 1/3/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//
// A Screen object and various shapes that can be drawn on it. Search for

#ifndef Shapes_h
#define Shapes_h

#include <iostream>
#include <vector>
#include <cmath>

// -------------- Screen -------------------
// A virtual screen with pixels x: 0-(w-1) and y: 0-(h-1).

class Screen {
   friend class Shape;

private:
   int width, height;

   std::vector<std::vector<char> > pixels;
     vector<vector<char>>& ref = pixels;

public:
   static const char DEFAULT_FG_CH = '*', DEFAULT_BG_CH = '.';

   Screen(int w = 100, int h = 100);

   bool drawPoint(int x, int y, char ch);
   bool drawLine(int x1, int y1, int x2, int y2, char ch);

   int getHeight() const {return height;}
   int getWidth() const {return width;}

   void clear() { fill(DEFAULT_BG_CH);}
   void fill(char c);
   string toString() const;
 std::vector<std::vector<char>>& getPixels() const { return ref; }
   friend std::ostream& operator<<(std::ostream& os, const Screen& scr);
};

// --------- Shape ---------------------------------
// Base class for Point, Line, etc.
// Abstract.
class Shape {

private:
public:
   virtual bool draw(Screen& scr, char fg = Screen::DEFAULT_FG_CH) = 0;
   virtual ~Shape(){};

};

// --------- Point ---------------------------------
class Point : public Shape {
private:
   int x, y;

public:
   Point(int x1, int y1) : x(x1), y(y1) {}
   bool draw(Screen& scr, char fg = Screen::DEFAULT_FG_CH);
   int getX() const {return x;}
   int getY() const {return y;}
   ~Point(){};

};

// ----------- Line --------------------------------
class Line : public Shape {

private:
   int x1, y1, x2, y2;
   bool drawByY(Screen& scr, int x1, int y1, int x2, int y2,char ch);
   bool drawByX(Screen& scr, int x1, int y1, int x2, int y2,char ch);
   bool drawLine(Screen& scr, int x1, int y1, int x2, int y2,char ch);

public:
   Line(int X1, int Y1, int X2, int Y2) : x1(X1), y1(Y1), x2(X2), y2(Y2) {}
   bool draw(Screen& scr, char fg = Screen::DEFAULT_FG_CH);
   int getX1() const {return x1;}
   int getX2() const {return x2;}
   int getY1() const {return y1;}
   int getY2() const {return y2;}
   ~Line(){};
};

// ----------- Quadrilateral -----------------
// A general quadrilateral with points (x1,y1) ... (x4,y4), clockwise
// from bottom left. Don't do sophisticated checks to make sure the points
// form a single closed shape.

class Quadrilateral : public Shape{

private:
   int x1,y1,x2,y2,x3,y3,x4,y4;
public:
   Quadrilateral() : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0), x4(0), y4(0){}
   Quadrilateral(int X1, int Y1, int X2, int Y2, int X3, int Y3, int X4, int Y4):
   x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3), x4(X4), y4(Y4) {}
   bool draw(Screen& scr, char fg = Screen::DEFAULT_FG_CH);
   ~Quadrilateral(){};

};

// ----------- UprightRectangle, a special Quadrilateral -----------------

// An UprightRectangle is a special upright Quadrilateral so we don't have to
// parameterize the constructor with a ton of numbers

// TODO - Complete this class
// Type your code here

class UprightRectangle : public Quadrilateral{

private:
   int x1,y1,x2,y2;
public:
   UprightRectangle(int X1, int Y1, int X2, int Y2) : x1(X1), y1(Y1), x2(X2), y2(Y2) {}
   bool draw(Screen& scr, char fg = Screen::DEFAULT_FG_CH);
   ~UprightRectangle(){};


};

// ----------- StickMan, a composite Shape -----------------

class StickMan : public Shape {
private:
   static const int DEFAULT_W = 20, DEFAULT_H = 40;
   int width, height, x, y;
   std::vector<Shape *> parts;
   UprightRectangle * head = nullptr;
   Line * torso = nullptr;
   Line * leg1 = nullptr;
   Line * leg2 = nullptr;
   Line * arm1 = nullptr;
   Line * arm2 = nullptr;

public:
   StickMan() : width(DEFAULT_W), height(DEFAULT_H){}
   StickMan(int x, int y, int w, int h);
   const std::vector<Shape *>& getParts() const { return parts;}
   bool draw(Screen& scr, char fg = Screen::DEFAULT_FG_CH);
   ~StickMan(){};

};


#endif /* Shape_h */

