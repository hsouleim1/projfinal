#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "cell.h"


class Cell; 

struct Translation {
  Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() {
    fl_pop_matrix();
  }
};


class Animation {
  protected:
    Cell* toAnimate;  
    int animationDuration = 10; 
    int distance;               
    int time{0};
  public:
    Animation(Cell* toAnimate, int distance=50); 
    virtual void draw() =0;
    virtual Point currentPosition() =0;
    virtual bool isComplete();
    virtual ~Animation()=default;
};


class Slide : public Animation {
  
  public:
    Slide(Cell *toAnimate, int distance=50); 
    void draw() override;
};

/*  classes enfant */

class RightSlide : public Slide {  
  Point currentPosition() override;
  public:
    RightSlide(Cell *toAnimate);
};


class LeftSlide : public Slide {   
  Point currentPosition() override;
  public:
    LeftSlide(Cell *toAnimate);
};


class UpSlide : public Slide { 
  Point currentPosition() override;
  public:
    UpSlide(Cell *toAnimate);
};


class DownSlide : public Slide {      
  Point currentPosition() override;
  public:
    DownSlide(Cell *toAnimate);
};


#endif  // ANIMATION_H