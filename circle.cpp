
#include "circle.h"

Circle::Circle(Point center, int r, Fl_Color frameColor, Fl_Color fillColor)
    : center{center}, r{r}, fillColor{fillColor}, frameColor{frameColor} {}
    
void Circle::draw() {
  array<Point, 37> points;
  for (unsigned i = 0; i < 36; i++)
    points[i] = {static_cast<int>(center.x + r * sin(i * 10 * pi / 180)),
                 static_cast<int>(center.y + r * cos(i * 10 * pi / 180))};
  points[36] = points[0];
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

void Circle::setFillColor(Fl_Color newFillColor) { fillColor = newFillColor; }

void Circle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}
void Circle::setRay(int newRay){
  r = newRay;
}
bool Circle::contains(Point p) {
  return ((p.x - center.x) * (p.x - center.x) +
              (p.y - center.y) * (p.y - center.y) <=
          r * r);
}