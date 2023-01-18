#ifndef __CONTROLL_H
#define __CONTROLL_H

#include <FL/Fl.H>
#include <memory>

#include "board.h"
#include "cell.h"
#include "common.h" 




using namespace std;

class ControllBoard {
    shared_ptr<Board> board;
    vector<vector<string>> info = board->read_file("map1.txt","highscore.txt");

    public:
    ///Constructor
        ControllBoard (shared_ptr<Board> board);

        /**
         * effectue le choix du niveau dans le menu pour le board
         * @param levelName le fichier du board
         * @param HSName le fichier du highscore
         */
        void setLevel(string levelName, string HSName);

        /**
         * gere les mouvement du joueur pendant le jeu
         * @param keyCode
         */
        void handleMove(int keyCode);

        /**
         * gere les choix du joueur concernant le jeu en general ( menu/recommencer le jeu...)
         * @param keyCode
         */
        void handleGameAction(int keyCode);
        ///keyboard
        void keyPressed(int keyCode);

        /**
         * selection du niveau dans le menu
         * @param keyCode
         */
        void selectLevel(int keyCode);

        bool processEvent(const int event);

};

#endif  // CONTROLL_H