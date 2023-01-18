#include <FL/fl_draw.H>

#include "animation.h"
#include "common.h"


/* ------------- ANIMATION CLASS ------------- */

Animation::Animation(Cell *toAnimate, int distance) : 
    toAnimate{toAnimate}, 
    distance{distance} {}

bool Animation::isComplete() {
  return time > animationDuration;
}

/* ------------- SLIDE CLASS ------------- */

Slide::Slide(Cell *toAnimate, int distance) : 
    Animation{toAnimate, distance} {}   


void Slide::draw() {
  ++time;
  Translation t3{currentPosition()}; // source : tp4
  toAnimate->drawWithoutAnimation(); 
}

/* ------------- RIGHT SLIDE CLASS ------------- */

RightSlide::RightSlide(Cell *toAnimate) : 
    Slide{toAnimate} {}

Point RightSlide::currentPosition(){
  if (isComplete()) return {0, 0};
  else {
    return {static_cast<int>(1 * time * distance/animationDuration), 0};
  }
}

/* ------------- LEFT SLIDE CLASS ------------- */


LeftSlide::LeftSlide(Cell *toAnimate) : 
    Slide{toAnimate} {}

Point LeftSlide::currentPosition(){
  if (isComplete()) return {0, 0};
  else {
    return {static_cast<int>(-1 * time * distance/animationDuration), 0};
  }
}

/* ------------- UP SLIDE CLASS ------------- */

UpSlide::UpSlide(Cell *toAnimate) : 
    Slide{toAnimate} {}

Point UpSlide::currentPosition(){
  if (isComplete()) return {0, 0};
  else {
    return {0, static_cast<int>(-1 * time * distance/animationDuration)};
  }
}

/* ------------- DOWN SLIDE CLASS ------------- */

DownSlide::DownSlide(Cell *toAnimate) : 
    Slide{toAnimate} {}

Point DownSlide::currentPosition() {
  if (isComplete()) return {0, 0};
  else {
    return {0, static_cast<int>(1 * time * distance/animationDuration)};
  }
}
