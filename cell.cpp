#include "cell.h"
#include <vector>
#include "common.h"
#include <iostream>


using namespace std;

/*--------------------------------------------------
Cell class.
The Board class below will have cells as instance
vraiables and call the methods of Cell
--------------------------------------------------*/


Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_WHITE, FL_WHITE),item(center, w, h, FL_WHITE, FL_WHITE), c(center,w/2,FL_WHITE,FL_WHITE), levelName("", center, h/2), animation{nullptr}{}//? à déterminer


void Cell::drawWithoutAnimation() {
  
  if (type == WALL){
    r.setFrameColor(fl_rgb_color(94, 94, 94));
    r.setFillColor(fl_rgb_color(94, 94, 94));
    r.draw();
    }

  else if (type == STACKBOX) {
    r.setFillColor(fl_rgb_color(	160,82,45));
    r.draw();

  }
  else if (type == BOX) {
    
    if(colorboxID >0 ) {
      item.setFillColor(color);
      c.setFillColor(color);

    }
    else {
    item.setFillColor(fl_rgb_color(115, 74, 18));
    }
    item.draw();
   
    }

  else if (type == PLAYER){
     if( isPortal()) { // évite la superposition des couleurs
      r.setFillColor(fl_rgb_color(0,204,0));
    }
    else if (isObjective()){
      if (colorObjID > 0) {
      r.setFillColor(color);
    }
      else{
      r.setFillColor(	fl_rgb_color(210,180,140));
    }
    }
    else {r.setFillColor(FL_WHITE);}

    r.draw();

    }
  else if (type == OBJECTIVE) {
    if (colorObjID > 0) {
      r.setFillColor(color);
    }
    else{
      r.setFillColor(	fl_rgb_color(210,180,140));
    }
    r.draw();

    }
  else if(type == PORTAL) {
    r.setFillColor(fl_rgb_color(0,204,0));
    r.setFrameColor(color);
    r.draw();
    r.drawstripes();
    }
    else{
      r.draw();
    }

  drawPlayer();
    
    }
void Cell::drawPlayer(){
  if (type == PLAYER){
  c.setFillColor(FL_DARK_YELLOW);
  c.draw();
  }
}


void Cell::startAnimation(string animationType, int distance){

    if (!animation) {
        if (animationType == "Left") {
            animation = new LeftSlide(this);
        }
        else if (animationType == "Right") {
            animation = new RightSlide(this);
        }
        else if (animationType == "Down") {

            animation = new DownSlide(this);
        }
        else if (animationType == "Up") {
            animation = new UpSlide(this);
        }
    }
}
bool Cell::isAnimated() {
    if (!animation) return false;
    else return true;
}



void Cell::setPosition(Point newPosition) { position = newPosition; }
Point Cell::getPosition() { return position; }

vector<Cell *> Cell::getNeighbors() {
    return neighbors;
}
void Cell::setNeighbors(const vector<Cell *> newNeighbors) {
    neighbors = newNeighbors;
  }



void  Cell::setType(string newType) { type = newType; }

string Cell::getType() { return type; }

void Cell::draw() {
  if (animation && animation->isComplete()) {
        delete animation;
        animation = nullptr;
        drawWithoutAnimation();
    }
    
    if (animation) animation->draw();
    else drawWithoutAnimation();
}
