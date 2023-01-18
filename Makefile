#Make file for mac


LDFLAGS +=-lfltk
ALL_FILES= board.cpp  cell.cpp   main.cpp  rectangle.cpp  text.cpp displayboard.cpp controll.cpp circle.cpp animation.cpp item.cpp
CXXFLAGS += $(shell fltk-config --cxxflags)
LDFLAGS  += $(shell fltk-config --ldflags)
CXXFLAGS += --std='c++17' -Wall -Wextra -pedantic
LDFLAGS  += -lfltk
CXX = g++
all:
	g++ $(CXXFLAGS) $(ALL_FILES) -o main $(LDFLAGS)