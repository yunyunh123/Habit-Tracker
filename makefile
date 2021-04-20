# Copyright 2021 Julia Hua jhua2@bu.edu

all: main

main: main.cpp Menu.o Menu.h Habits.o Habits.h Textbox.h
	g++ main.cpp Menu.o Habits.o -o main -lsfml-graphics -lsfml-window -lsfml-system
