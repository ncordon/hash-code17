SHELL = /bin/bash


SRC = $(wildcard src/*.cc src/*.cpp)
EXE = $(basename $(SRC))

CFLAGS = -Wall
CXXFLAGS = $(CFLAGS) -std=c++0x

default: $(EXE)
	mv $(EXE) bin/
