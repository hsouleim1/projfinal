#ifndef __ITEM_H
#define __ITEM_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include "common.h"

/*Permet de dessiner les box lorsqu'elles sont animées*/


class Item { // source : TP 4
  Point center;
  int w;
  int h;
  Fl_Color fillColor, frameColor;
  vector<Point> stripeInitPos {{center.x-w/2, center.y - h /2 + 2},
                              {center.x-w/2, center.y - h /4},
                              {center.x-w/2, center.y},
                              {center.x-w/2, center.y + h /4},
                              {center.x-w/2, center.y + h/2 - 2}};
  vector<Point> stripeFinalPos {{center.x+w/2, center.y - h /2 + 2},
                              {center.x+w/2, center.y - h /4},
                              {center.x+w/2, center.y},
                              {center.x+w/2, center.y + h /4},
                              {center.x+w/2, center.y + h /2 - 2}};

public:
 Item(Point center, int w, int h, Fl_Color frameColor = FL_WHITE,
            Fl_Color fillColor = FL_WHITE);
  void draw();
  void setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() { return fillColor; }
  void setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() { return frameColor; }
  void setWidth(int neww) { w = neww; }
  void setHeight(int newh) { h = newh; }
  int getWidth() { return w; }
  int getHeight() { return h; }
  bool contains(Point p);
  Point getCenter() { return center; }
  void drawstripes();


};

#endif //__ITEM_H