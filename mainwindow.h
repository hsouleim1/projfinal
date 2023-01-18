#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include "board.h"
#include <iostream>
#include "displayboard.h"
#include "controll.h"

const double refreshPerSecond = 60;
int windowWidth = 800;
const int windowHeight = 600;



class MainWindow : public Fl_Window {

  shared_ptr<Board> board ;                         // model
  DisplayBoard displayBoard;                       // view
  ControllBoard controllBoard;                     // controller

public:

  MainWindow() : Fl_Window(320, 120, windowWidth, windowHeight, "SOKOBAN"),
  board{make_shared<Board>()}, displayBoard{board},controllBoard{board} {
    cout << "executing mainwindow" << endl;
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
    resizable(this);
  }

  void draw() override {
    Fl_Window::draw();
    displayBoard.draw();

  }
  
  int handle(int event) override {
    return controllBoard.processEvent(event);
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
  }
};

#endif //__MAINWINDOW_H