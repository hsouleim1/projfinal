#ifndef __RECTANGLE_H
#define __RECTANGLE_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include "common.h"


/*permet de dessiner les objets statiques, sans animation (path, wall, objectif) */
class Rectangle { //source : TP 2
  Point center;
  int w;
  int h;
  Fl_Color fillColor;
    Fl_Color frameColor;
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
  Rectangle(Point center, int w, int h, Fl_Color frameColor = FL_WHITE,
            Fl_Color fillColor = FL_WHITE);
  void draw();

  /// Setters
  void setFillColor(Fl_Color newFillColor);
  void setFrameColor(Fl_Color newFrameColor);
  void setWidth(int neww) { w = neww; }
  void setHeight(int newh) { h = newh; }

  /// Getters
  int getWidth() { return w; }
  Fl_Color getFrameColor() { return frameColor; }
  int getHeight() { return h; }
  Fl_Color getFillColor() { return fillColor; }
  Point getCenter() { return center; }

  bool contains(Point p);

  /**
   * dessine des traits sur les cellules
   */
  void drawstripes();
};

#endif //__RECTANGLE_H