#include <time.h>

#include <math.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "common.h"

#include "board.h"
#include "mainwindow.h"
#include "board.h"
#include <fstream>


/*--------------------------------------------------

main

Do not edit

--------------------------------------------------*/


int main(int argc, char *argv[]) {
  
  srand(static_cast<unsigned>(time(nullptr)));
  MainWindow window;
  window.color(FL_WHITE);
  window.show(argc, argv);
  return Fl::run();
  
}
