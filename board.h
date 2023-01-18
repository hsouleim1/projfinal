#ifndef __BOARD_H
#define __BOARD_H

#include "cell.h"
#include "common.h"
#include "text.h"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>




class Board{
  ///Attributs nécessaires à la lecture du fichier contenant la map
  const string PATH = ".";
  const string WALL = "w";
  const string BOX = "b";
  const string STACKBOX = "s";
  const string PLAYER = "p";
  const string OBJECTIVE = "o";
  const string PORTAL = "#";
  const string LEVELBOX = "L";

  vector<vector<Cell>> cells;
  bool isInMenu = true;

  ///couleur
  vector<unsigned int> boxcolors{fl_rgb_color(255,102,102), fl_rgb_color(255,178,102),
                              fl_rgb_color(255,255,102),fl_rgb_color(178,255,102),
                              fl_rgb_color(102,255,102),fl_rgb_color(102,255,178),
                              fl_rgb_color(102,255,255),fl_rgb_color(102,178,255),
                              fl_rgb_color(102,102,255),fl_rgb_color(178,102,255),
                              fl_rgb_color(255,102,255),fl_rgb_color(255,102,178),
  };
  vector<unsigned int> objectivecolors{fl_rgb_color(255,204,204), fl_rgb_color(255,229,204),
                              fl_rgb_color(255,255,204),fl_rgb_color(229,255,204),
                              fl_rgb_color(204,255,204),fl_rgb_color(204,255,229),
                              fl_rgb_color(204,255,255),fl_rgb_color(204,229,255),
                              fl_rgb_color(204,204,225),fl_rgb_color(229,204,255),
                              fl_rgb_color(255,204,255),fl_rgb_color(255,204,229), //c un tableau excel à ce point....
  };
    vector<unsigned int> portalColors{fl_rgb_color(127,0,255), fl_rgb_color(128,255,0),
                                         fl_rgb_color(FL_RED),fl_rgb_color(0,0,255),
                                         fl_rgb_color(255,255,0),fl_rgb_color(FL_GRAY0),
                                      fl_rgb_color(0,255,255),fl_rgb_color(255,128,0),
                                      fl_rgb_color(FL_GREEN),
    };

  unsigned int steps = 0;
  unsigned int gamesHighScore = 0;
  unsigned int counter = 0;
  unsigned int stepsLimit;
  Cell* playerCell;
  vector<vector<string>> board_chars{};
  string highScoreFile;
  ///texts
  Text textYouWin{"YOU WIN", {340, 200}, 70, FL_GREEN};
  Text textYouLose{"YOU LOST :(", {340, 200}, 70, FL_RED};
  Text intro {"SOKOBAN", {400, 150}, 70, fl_rgb_color(255,153,204)};
  Text name1{"Ali Bahja", {300, 200}, 20, FL_GRAY0};
  Text name2{"Hodo Souleiman Ahmed", {300, 200}, 20, FL_GRAY0};
  ///Menu texts
  Text textSelectLevel{"Select your level : press 1 (level 1) ,2 (level 2) or 3 (level 3)", {90, 320}, 20, FL_DARK_MAGENTA};
  Text movecommands{"Movement commands : ", {150, 60}, 20, FL_DARK_MAGENTA};
  Text gamecommands {"MENU = P  - QUIT = Q ", {90, 220}, 20, FL_DARK_MAGENTA};
  Text extracommands {"RESET HIGHSCORE = R - RESET LEVEL = SPACEBAR", {100, 270}, 20, FL_DARK_MAGENTA};
  Text movementUp{   "UP      = O " ,{150,110}     ,20, FL_GRAY0};
  Text movementDown{ "DOWN  = L ",{150,140 },20,    FL_GRAY0};
  Text movementLeft{ "RIGHT = M ",{150,160},20,    FL_GRAY0};
  Text movementRight{"LEFT   = K ",{150,180},20,    FL_GRAY0};

public :

  ///Animation related

  /**
   * commence l'animation des deplacement des boxes et joueur
   * @param cell
   * @param direction
   * @param distance
   */
  void start_cell_animation(Cell* cell, string direction, int distance);

  /**
   * verifie si un string est un nombre
   * @param s  string à verifier
   * @return  True or False
   */
  bool isNumber(string s);

  /**
   * gere l'animation du board
   */
  void handleAnimation();

  /**
   * lit et initialise les fichiers du board choisis dans le menu principal
   * @param filename
   * @param HighScoreFile
   * @return
   */
  vector<vector<string>> read_file(string filename, string HighScoreFile);

  /**
   * initialise le board
   * @param boardinfo le fichier du board et son highscore
   */
  void initialize(vector<vector<string>> boardinfo);

  /**
   * dessine le board
   */
  void draw();
  vector<vector<Cell>>getCells();
  ///setters
  void setIsMenu(bool newflag){isInMenu = newflag;}
  void setStackBoxPos(Point cell);
  void setHighscore(unsigned int newHighscore);
  void setHSFile(string newHSFile){highScoreFile = newHSFile;}
  void setSteps(int numSteps){steps = numSteps;}

  ///getters
  bool getIsMenu() {return isInMenu;}
  string getMatchingDirection( Point vecteur);
  string getHSFile(){return highScoreFile;}
  int getNumSteps() const {return steps;}

  void incrementSteps(){steps++;}
   /**
    * met à jour toutes les voisins des cellules
    */
  void updateAllNeighbors();

  /**
   *  trouve tous les voisins d'une cellule et les ajoutent ensuite dans une liste
   * @param cell
   */
  void updateCellNeighbors(Cell* cell);

  /**
   * verifie si une cellule x est voisine à une cellule y
   * @param c1
   * @param c2
   * @return      True or false
   */
  static bool areNeighbors(Cell* c1, const Cell* c2);

  /**
   * verifie si la destination chosie est sur le board
   * @param newppos destination du joueur/box
   * @return    true or false
   */
  bool isInBoard(Point newppos);

  /**
   * verifie si le joueur peut aller à une case precise
   * @param destination  destination du joueur
   * @return true or false
   */
  bool isValidMove(Point destination);

  /**
   * deplace le joueur sur le board
   * @param destination destination du joueur
   */
  void playermove(Point destination);

  /**
   * verifie si la destination du stackbox est valide
   * @param vecteur destination du box
   * @return
   */
  Point isValidStackBoxMove(Point vecteur);

  /**
   * deplace une stackbox
   * @param vecteur  destination du box
   */
  void StackBoxMove(Point vecteur);

  /**
   * deplace le joueur de sa postion initiale à une position donnée
   * @param vecteur  destination du joueur
   */
  void move(Point vecteur);

  /**
   * verifie si les deux portail sont connectés
   * @param c1  portail de base
   * @param c2  portail comparé
   * @return   True or False
   */
  static bool matchPortals(Cell c1, Cell c2);


  /**
   * teleporte le joueur d'un portail vers une autre corespondent
   * @param Portal   le portail dont le joueur est en dessus
   */
  void PortalTravel(Point Portal);

  /**
   * inisialise le highscore du joueur
   */
  void initHighscore();

  /**
   * renitialise le highscore à la demande du joueur
   */
  void resetHighscore();

  /**
   * parcoure toute la matrice du jeu en verifiant si toutes les boxes sont sur leurs objectives afin de determiner la
   * fin du jeu
   * @return     True or False
   */
  bool isGameWon();

  /**
   * verifie si toutes les boxes importantes ( le nombre de box == nombre d'objective) sont bloquées
   * @return  True or False
   */
  bool areAllBoxesStuck();

  /**
   * verifie  si une box est bloquée dans un coin du board (entre 2 murs)
   * @param box
   * @return   True or False
   */
  bool isBoxStuck(Cell* box);

  /**
   *  verifie si le joueur a le droit de pousser la box vers une direction x
   * @param newppos  nouvelle position du box
   * @param vecteur  la position du box
   * @return        True or false
   */
  bool isValidBoxmove(Point newppos, Point vecteur);

  /**
   * deplace la box en fonction du joueur
   * @param newppos  nouvelle position
   * @param vecteur  la position du box
   */
  void playerBoxmove(Point newppos, Point vecteur);

  /**
   * verifie si la limite de pas n'est pas depassée
   * @return     True or false
   */
  bool isStepsLimitPassed() const;


};


#endif //__BOARD_H