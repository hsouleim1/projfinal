#include "controll.h"
#include "common.h"


ControllBoard::ControllBoard(shared_ptr<Board> board) : board{board}{}


void ControllBoard::setLevel(string levelName, string HSName){
  info = board->read_file(levelName, HSName);
  board->initialize(info);
  board->setIsMenu(false);

}


bool ControllBoard::processEvent(const int event) {
   switch (event) {
    case FL_KEYDOWN:
      keyPressed(Fl::event_key());
      return true;
    default:
      return false;
  }
}


void ControllBoard::selectLevel(int keyCode){
  switch (keyCode) {
       case '1':
      setLevel("map1.txt","map1highScore.txt");
      break;
      case '2':
      setLevel("map2.txt","map2highScore.txt");
      break;
      case '3':
      setLevel("map3.txt","map3highScore.txt");
      break;
      default : {}
    }
    board->draw();
}

void ControllBoard::handleMove(int keyCode){
  switch (keyCode) {
  case 'o':
    board->move({0, -1});
    break;
  case 'l':
    board->move({0, 1});
    break;
  case 'k':
    board->move({-1, 0});
    break;
  case 'm':
    board->move({1, 0});
    break;
  }
}

void ControllBoard::handleGameAction(int keyCode){
   switch (keyCode) {
        case 'p':
            board->setIsMenu(true);
            break;
        case ' ':
            board->initialize(info);
            break;
        case 'r':
            board->resetHighscore();
            break;
        case 'q':
            exit(0);
   }
}


void ControllBoard::keyPressed(
    int keyCode) {
    if (board->getIsMenu()){
      selectLevel(keyCode);
    }
    if (board->isGameWon() || board->areAllBoxesStuck() || board->isStepsLimitPassed()){
      handleGameAction(keyCode);
    }
    else{
    handleMove(keyCode);
    handleGameAction(keyCode);
}
  
}