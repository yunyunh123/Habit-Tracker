# Copyright 2021 Julia Hua jhua2@bu.edu

all: main

main: main.cpp Menu.o Menu.h
	g++ main.cpp Menu.o -o main -lsfml-graphics -lsfml-window -lsfml-system
