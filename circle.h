#ifndef __CIRCLE_H
#define __CIRCLE_H
#include "common.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <time.h>

#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#if __cplusplus >= 202002L
#include <numbers>
using std::numbers::pi;
#else
const long double pi = 3.141592653589793238462643383279502884L;
#endif


class Circle {  // source TP 6
  Point    center;
  int      r;
  Fl_Color fillColor, frameColor;

 public:
  Circle(Point center, int r, Fl_Color frameColor = FL_BLACK,
         Fl_Color fillColor = FL_WHITE);
  void     draw();
  void     setFillColor(Fl_Color newFillColor);
  void     setRay(int newRay);
  int     getRay() {return r;}
  Fl_Color getFillColor() { return fillColor; }
  void     setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() { return frameColor; }
  bool     contains(Point p);
  Point    getCenter() { return center; }
};


#endif //__C_H