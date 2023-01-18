#ifndef __CELL_H
#define __CELL_H

#include "common.h"
#include "rectangle.h"
#include "item.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <vector>
#include "circle.h"
#include "text.h"
#include "animation.h"

class Animation;
class Cell {


  Animation *animation; 
  Rectangle r;
  Item item;
  Circle c;
  Point position;
  vector<Cell *> neighbors;
  unsigned int color = FL_WHITE;
  string type;
  vector<Point> playervertex{};
  Text levelName;
  bool portal = false;
  int portalID = -1;
  int colorboxID = -1;
  int colorObjID = -1;
  bool objective= false;
  bool box = false;


  const string PATH = ".";
  const string WALL = "w";
  const string BOX = "b";
  const string STACKBOX = "s";
  const string PLAYER = "p";
  const string OBJECTIVE = "o";
  const string PORTAL = "#";
  const string LEVELBOX = "L";


public:
  // Constructor
  Cell(Point center, int w, int h);

  /**
   * dessine la cellule sans animation
   */
  void drawWithoutAnimation() ;

  /**
   * commence l'animation des cellules en fonction de sa direction
   * @param animationType droite gauche haut bas
   * @param distance
   */
  void startAnimation(string animationType, int distance=70) ;

  /**
   * verefie si une cellule est animée
   * @return True or false
   */
  bool isAnimated();
  void drawPlayer();


  // Methods that draw and handle events
  void draw();


  // Used to initalize neighbors after all cells are created


  //Setters
  void setColorBoxID(int newColorBoxID){colorboxID = newColorBoxID;}
  void setPortalID(int newPortalID){portalID = newPortalID;}
  void setType(string newType);
  void setNeighbors(const vector<Cell *> newNeighbors);
  void setPortal(bool newSet){ portal = newSet;}
  void setPosition(Point newPosition);
  void setColor (unsigned int newcolor){ color = newcolor;}
  void setLevelName(string newLvlName){levelName.setString(newLvlName);}
  void setObjective(bool newValue){objective = newValue;}
  void setBox(bool newValue){box = newValue;}
  void setColorObjID(int newColorObjID){colorObjID = newColorObjID;}

  //Getters
  vector<Cell *> getNeighbors();
  string getType();
  int getPortalID(){return portalID;}
  int getColorObjID(){return colorObjID;}
  int getColorBoxID(){return colorboxID;}
  Point getPosition();
  bool isPortal() {return portal;}
  bool isObjective(){return objective;}
  bool isBox(){return box;}

};

#endif //__CELL_H