#include "board.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include "animation.h"
#include <unistd.h>
#include <algorithm>

using namespace std;
bool Board::isNumber(string s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

string Board::getMatchingDirection( Point vecteur){
  vector<Point> vecteurs{{0,1}, {1,0}, {0,-1}, {-1,0}};
  vector<string>matching_directions{"Down", "Right", "Up", "Left"};
  for (int i = 0; i< vecteurs.size(); i++) {
    if (vecteur == vecteurs[i]) {
      return matching_directions[i];
    }
  }
  return {-1,-1}; 
}

void Board::start_cell_animation(Cell* cell, string direction, int distance) {
  cell->startAnimation(direction, distance);
}
void Board::handleAnimation() {
  // evite que plusieurs animations s'overlay (cas box/stackbox)
  bool animationInProgress = true;
  while(animationInProgress) {
    animationInProgress = false;
    for (auto &v: cells){
      for (auto &c: v) {
        if (c.isAnimated()) {
          animationInProgress = true;
          break;
        }
      }
    }
    if (animationInProgress) {
      Fl::wait();
    } 
  }
}

vector<vector<string>> Board::read_file(string filename, string highScoreFile) {
  // This is called by the constructor but also by keyPressed to
  // reset whenever spacebar is called. (prof)
  // Until the last step when we needed to reset, this would be the constructor
  setSteps(0) ;     // reset steps
  setHSFile(highScoreFile);
  vector<vector<string>> boardtest{};
  // cells initiation
  initHighscore();
  ifstream mapFile;
  mapFile.open(filename);
  if (!mapFile) {
    cout << "Unable to open file" << endl;
    exit(1);
  }
  string line;
  int x1 = 0;
  getline(mapFile,line);
  stepsLimit = stoi(line);
  while (getline(mapFile, line)) {
    boardtest.emplace_back();
    string cellType;
    for (char val : line) {
      if (val != ',') {
        cellType += val; // allows cell identifier to be longer than one char '
      } else {

        boardtest[x1].push_back(cellType);
        cellType = ""; // emptying value for next elem
      }
    }
    x1++;
  }
      mapFile.close();
        return boardtest;
  }
  

  void Board::initialize(vector<vector<string>> boardinfo){
  setSteps(0);
  cells.clear(); // Needed to remove the cells if we are starting again
  // cells initiation
  string cur_type;
  for (int x = 0; x < boardinfo.size(); x++) {
    cells.emplace_back();
    for (int y = 0; y < boardinfo[x].size(); y++) { // unchangeable board size
      cells[x].push_back({{50 * x + 25, 50 * y + 25}, 50, 50});
      cells[x][y].setPosition({x, y}); // coord matrice jamais -
      string elem = boardinfo[y][x];
      Cell* cell = &cells[x][y];
      if (elem == PATH) {
        cell->setType(PATH);
        }
      else if (elem == WALL) {
       cell->setType(WALL);
      }
      else if (elem == STACKBOX){
        cell->setType(STACKBOX);
        cell->setColorBoxID(-1);
      }
      else if (elem.substr(0, 1) == BOX) {
        cell->setType(BOX);
        cell->setBox(true);
        cell->setColorBoxID( 0);
        if (elem.size() > 1) { // is a color box because has an ID
          cell->setColorBoxID( stoi(elem.substr(1, elem.size() - 1))); // ID must be between 1 and 99
            cell->setColor(boxcolors[cell->getColorBoxID()] - 1);
        }
      }
      else if (elem == PLAYER) {
        cells[x][y].setType(PLAYER);
        playerCell = &cells[x][y];
      }
      else if (elem.substr(0, 1) == OBJECTIVE) {
        cell->setType(OBJECTIVE);
        cell->setObjective(true);
        cell->setColorObjID(0);
        if (elem.size() > 1) { // is a color objective because has an ID
          cell->setColorObjID(stoi(elem.substr(1, elem.size() - 1))); // ID must between 1 and 12
          cell->setColor(objectivecolors[cell->getColorObjID()] - 1);
        }
      } else if (isNumber(elem) && elem.size()<=2) {
        cell->setType(PORTAL);
        cell->setPortal(true) ;
        cell->setPortalID(stoi(elem));
        cell->setColor( portalColors[((stoi(elem)/10) +  (stoi(elem)-(stoi(elem)/10) *10 ) )-3]) ;
      }
    }
  }
  updateAllNeighbors();
  }

Point Board::isValidStackBoxMove(Point vecteur){
    Point pos_to_check = playerCell->getPosition() + vecteur;
    while (cells[pos_to_check.x][pos_to_check.y].getType()== STACKBOX) {
        pos_to_check = pos_to_check + vecteur;
    }
    if (isValidMove(pos_to_check)) {
        return pos_to_check;
    }
    else{
        return {-1,-1}; // impossible move
    }
}

void Board::StackBoxMove(Point vecteur){
    string direction = getMatchingDirection(vecteur);
    Point last_sbox_pos = isValidStackBoxMove(vecteur);
    Point balise = {-1,-1};
    if (last_sbox_pos != balise) {
      start_cell_animation(playerCell,direction,50);
              handleAnimation();
        Point newppos = playerCell->getPosition() + vecteur;
        playermove(newppos);
        Point cur_sbox_pos = playerCell->getPosition() + vecteur;
        while (cur_sbox_pos.x != last_sbox_pos.x || cur_sbox_pos.y != last_sbox_pos.y) {
            setStackBoxPos(cur_sbox_pos);
            cur_sbox_pos = cur_sbox_pos + vecteur;
        }
        Cell* last_sbox_cell = &cells[cur_sbox_pos.x-vecteur.x][cur_sbox_pos.y-vecteur.y];
        start_cell_animation(last_sbox_cell,direction,50);
        setStackBoxPos(cur_sbox_pos); // on bouge la case extra
        handleAnimation();
    }
}

void Board::setStackBoxPos(Point cell) {
    Cell* cellptr = &cells[cell.x][cell.y];
    cellptr->setColorBoxID(0);
    cellptr->setType(STACKBOX);
    cellptr->setBox(true);
}

bool Board::isBoxStuck(Cell* box) {
    int wallcount = 0;
    vector <Cell*> box_neighbors = box->getNeighbors();
    for (int i = 0; i < box_neighbors.size() + 1 ; i ++ ) { //+1 et %size pr finir boucle
        if (wallcount == 2) {
            return true;
        }
        if (box_neighbors[i % box_neighbors.size()]->getType()== WALL && !box->isObjective()) {
            wallcount +=1;}

    }
    return false;
}
bool Board::areAllBoxesStuck(){
  int box_count = 0;
  int obj_count = 0;
  int stuckboxcount = 0;
  for (auto &v : cells)
    for (auto &c : v) {
      if (c.getType() == BOX  || c.getType() == STACKBOX ) {
        box_count +=1;
        if (isBoxStuck(&c)) {
          stuckboxcount +=1;
        }
        if (c.isObjective()){
            obj_count +=1;
        }
      }
       else if (c.getType() == OBJECTIVE) {
        obj_count +=1;
        }
    }
    if (int freeboxcount = box_count - stuckboxcount; obj_count > freeboxcount) {
      return true;
      }
  return false;
}

bool Board::isGameWon() {
  for (auto &v : cells)
    for (auto &c : v) {
      if (c.isObjective() && ((c.getType() != BOX && c.getType() != STACKBOX )|| ((c.getType() == BOX || c.getType() == STACKBOX ) && c.getColorObjID() != c.getColorBoxID()))) {
        return false;
      }
    }
  setHighscore(getNumSteps());
  return true;
}

bool Board::isValidMove(Point destination) {
  return cells[destination.x][destination.y].getType() != WALL &&
         cells[destination.x][destination.y].getType() != BOX;
}

void Board::move(Point vecteur) {
  Point playerCellPos = playerCell->getPosition();
  Point newppos = playerCellPos + vecteur;
  string direction = getMatchingDirection(vecteur);
  if (isInBoard(newppos) &&areNeighbors(playerCell, &cells[newppos.x][newppos.y])) {
      if (!isValidMove(newppos)) {
          if (cells[newppos.x][newppos.y].getType() == BOX && isValidBoxmove(newppos, vecteur)) {
            playerBoxmove(newppos, vecteur);}
      } else {
          if (cells[newppos.x][newppos.y].isPortal() && cells[newppos.x][newppos.y].getType() != STACKBOX) {
             start_cell_animation(playerCell,direction,50);
             handleAnimation();
             PortalTravel(newppos);
          } else if (cells[newppos.x][newppos.y].getType() == STACKBOX) {
              StackBoxMove(vecteur); //la verif se fait dans stackboxmove
          } else {
              start_cell_animation(playerCell,direction,50);
              handleAnimation();
              playermove(newppos);
          }}}
}

bool Board::areNeighbors(Cell *c1,const Cell *c2) {
  for (unsigned int i = 0; i < c1->getNeighbors().size(); i++) {
    if (c1->getNeighbors()[i] == c2) {
      return true;}
  }
  return false;
}

void Board::playerBoxmove(Point newppos, Point vecteur) {
  Point boxDest = newppos + vecteur;
  string direction = getMatchingDirection(vecteur);
  start_cell_animation(playerCell,direction,50);
  handleAnimation();
    cells[boxDest.x][boxDest.y].setColorBoxID( cells[newppos.x][newppos.y].getColorBoxID());
    cells[boxDest.x][boxDest.y].setColor(boxcolors[cells[boxDest.x][boxDest.y].getColorBoxID()] - 1);
    if(cells[newppos.x][newppos.y].isObjective()) {//restore the color of the objective
        cells[newppos.x][newppos.y].setColorBoxID(-1);
        cells[newppos.x][newppos.y].setColor(objectivecolors[cells[newppos.x][newppos.y].getColorObjID()] - 1);
    }
    else if(cells[newppos.x][newppos.y].isPortal()){//restore the color of the portal
        cells[newppos.x][newppos.y].setColorBoxID(-1);
        cells[newppos.x][newppos.y].setColor(portalColors[(((cells[newppos.x][newppos.y].getPortalID()/10) +  (cells[newppos.x][newppos.y].getPortalID()-(cells[newppos.x][newppos.y].getPortalID()/10) *10 )) )-3]);
    }
  playermove(newppos);
  cells[boxDest.x][boxDest.y].setType(BOX);
  handleAnimation();
}

bool Board::isValidBoxmove(Point newppos, Point vecteur) {
  Point boxDest = {newppos.x + vecteur.x, newppos.y + vecteur.y};
  return areNeighbors(&cells[newppos.x][newppos.y],
                      &cells[boxDest.x][boxDest.y]) &&
         cells[boxDest.x][boxDest.y].getType() !=WALL && cells[boxDest.x][boxDest.y].getType() != STACKBOX &&
         cells[boxDest.x][boxDest.y].getType() !=BOX;
}

vector<vector<Cell>> Board::getCells() { return cells; }

bool Board::matchPortals(Cell c1, Cell c2) {
  return (c2.getPortalID() ==((c1.getPortalID() - ((c1.getPortalID() / 10) * 10)) * 10) + c1.getPortalID() / 10);
}

void Board::PortalTravel(Point portal) {
  for (auto &v : cells)
    for (auto &c : v) {
      if (c.getType() == PORTAL &&
          matchPortals(cells[portal.x][portal.y], c)) {
          playermove(c.getPosition());
        break;
      }
    }
}

void Board::draw() {
  counter += 1;
  if (counter < 80) {
    intro.draw();
    name1.draw();
    name2.draw();
  } 
  else if(isInMenu){
    movecommands.draw();
    movementDown.draw();
    movementUp.draw();
    movementLeft.draw();
    movementRight.draw();
    textSelectLevel.draw();
    gamecommands.draw();
    extracommands.draw();
  }
    else {
    if (isGameWon()) {
      textYouWin.draw();
    } else if (areAllBoxesStuck() || isStepsLimitPassed()) {
      textYouLose.draw();
    } else {
      for (auto &v : cells) {
        for (auto &c : v)
          c.draw();
      }
        ///Ingame texts
       Text textSteps{"NUMBER OF STEPS :" + to_string(getNumSteps()), {520, 10}, 20, FL_GRAY0};
       Text textHighScore{"YOUR HIGHSCORE IS:" + to_string(gamesHighScore), {520, 50}, 20, FL_GRAY0};
       Text textStepsLimit{"THE STEPS LIMIT :" + to_string(stepsLimit), {520, 90}, 20, FL_GRAY0};
       textSteps.draw();
      textStepsLimit.draw();
      textHighScore.draw();
    }
  }
}

void Board::updateAllNeighbors() {
  // This computes the (pointers to) neighbors of each cell
  for (auto &cell : cells)
    for (unsigned y = 0; y < cells.size(); y++) {
      updateCellNeighbors(&cell[y]);
    }
}

void Board::playermove(Point newppos) {
  playerCell->setColorBoxID(-1) ;
  playerCell->setBox(false);
  if (playerCell->isObjective()) {
    playerCell->setType(OBJECTIVE);
  } else if (playerCell->isPortal()) {
    playerCell->setType(PORTAL);
  } else {
    playerCell->setType(PATH);
  }
  cells[newppos.x][newppos.y].setType(PLAYER);
  cells[newppos.x][newppos.y].setColorBoxID(-1);
  incrementSteps();
  updateCellNeighbors(playerCell);
  playerCell = &cells[newppos.x][newppos.y];
}

bool Board::isInBoard(Point newppos) {
  return (0 <= newppos.x < cells.size() && 0 <= newppos.y < cells.size()) ;
}

void Board::updateCellNeighbors(Cell *cell) {
  int x = cell->getPosition().x;
  int y = cell->getPosition().y;
  vector<Cell *> neighbors;
  for (auto &shift : vector<Point>({
           {-1, 0}, // The 4 neighbors relative to the cell
           {0, 1},
           {1, 0},
           {0, -1},
       })) {
    // check lower bounds
    if (!((x == 0 && shift.x == -1) || (y == 0 && shift.y == -1))) {
      int neighborx = (x + shift.x);
      int neighbory = (y + shift.y);
      // check upper bounds
      if (neighborx < cells.size() && neighbory < cells[neighborx].size()) {
        neighbors.push_back(&cells[neighborx][neighbory]);
      }
    }
    cells[x][y].setNeighbors(neighbors);
  }
}

void Board::initHighscore() {
  ifstream highScoreFile(getHSFile());
  if (!highScoreFile) {
    cout << "Unable to open file" << endl;
    exit(1);
  } else {
    highScoreFile.seekg(0, highScoreFile.end);
    int length = highScoreFile.tellg();
    char *buffer = new char[length];
    highScoreFile.seekg(0, highScoreFile.beg);
    highScoreFile.read(buffer, length);//reads the first line of the file
    sscanf(buffer, "%d", &gamesHighScore);
  }
  highScoreFile.close();
}

void Board::resetHighscore() {
  ofstream highscoreFile(getHSFile(),  ofstream::trunc);
  if (!highscoreFile) {
    cout << "Unable to open file" << endl;
    exit(1);
  } else {
    highscoreFile << 0 << endl;
      gamesHighScore = 0;
  }
  highscoreFile.close();
}

void Board::setHighscore(unsigned int newHighscore) {
  if (gamesHighScore == 0 || (gamesHighScore > newHighscore && newHighscore != 0)) {
    ofstream highscoreFile(getHSFile(), ofstream::out | ofstream::trunc);// replace whats in the file by erasing the existing score
    highscoreFile << newHighscore << endl;
      gamesHighScore = newHighscore;
  }
}

bool Board::isStepsLimitPassed() const{
    return (getNumSteps()>=stepsLimit);
}
