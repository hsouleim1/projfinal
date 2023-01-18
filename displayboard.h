#include "board.h"
#include "common.h" 


class DisplayBoard {

    shared_ptr<Board> board;

    public:
        DisplayBoard(shared_ptr<Board> board);
        void draw();
};
