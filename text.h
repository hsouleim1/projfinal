#ifndef __TEXT_H
#define __TEXT_H


#include "common.h"
#include <string>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>

class Text {
  string s;
  Point center;
  int fontSize;
  Fl_Color color;

public:
  /// Constructor
  Text(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK)
      : s{s}, center{center}, fontSize{fontSize}, color{color} {}

  /// Draw
  void draw();

  /// Getters
  string getString() { return s; }
  Point getCenter() { return center; }
  int getFontSize() { return fontSize; }
  ///Setters
  void setFontSize(int newFontSize) { fontSize = newFontSize; }
  void setString(const string &newString) { s = newString;}
  void setCenter(Point newCenter) { center = newCenter; }
  void setColor(Fl_Color newColor){ color = newColor;}
};

#endif // __TEXT_H