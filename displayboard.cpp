#include "displayboard.h"
#include "common.h"


DisplayBoard::DisplayBoard(shared_ptr<Board> board) : board{board} {}


void DisplayBoard::draw() {
    board->draw();
}