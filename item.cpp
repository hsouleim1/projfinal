#include "item.h"
#include "common.h"
#include <array>

Item::Item(Point center, int w, int h, Fl_Color frameColor,
                     Fl_Color fillColor)
    : center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {
}

void Item::draw() {
    array<Point, 5> points{
        Point{center.x - w / 2, center.y - h / 2},
        Point{center.x - w / 2, center.y + h / 2},
        Point{center.x + w / 2, center.y + h / 2},
        Point{center.x + w / 2, center.y - h / 2},
        Point{center.x - w / 2, center.y - h / 2}};
    fl_color(fillColor);
    fl_begin_polygon();
    for (auto &point : points) {
        fl_vertex(point.x, point.y);
    }
    fl_end_polygon();
    fl_color(frameColor);
    fl_begin_line();
    for (auto &point : points) {
        fl_vertex(point.x, point.y);
    }
    fl_end_line();
}


void Item::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}

void Item::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}

bool Item::contains(Point p) {
  return p.x >= center.x - w / 2 && p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 && p.y < center.y + h / 2;
}

void Item::drawstripes(){
  for (unsigned int i = 0 ; i < 5 ; i++){
    fl_line_style(FL_DOT, 3);
    fl_line(stripeInitPos[i].x,stripeInitPos[i].y,stripeFinalPos[i].x,stripeFinalPos[i].y);
    fl_line_style(0);
  }
}
    
