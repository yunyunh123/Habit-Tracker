//#include "SFML/Graphics.hpp"
#include "Menu.h"
//#include "Habits.h"
#include <iostream>
#include "Textbox.h"
#include <fstream>

void newHab(Habits habit);

void makeList(std::vector<Habits> hab) {

  sf::RenderWindow window(sf::VideoMode(600, 600), "Track Habits", sf::Style::Titlebar | sf::Style::Close);
  Menu menu(window.getSize().x, window.getSize().y, hab);

  while (window.isOpen()) {
    sf::Event event;

    while(window.pollEvent(event)) {
      switch(event.type) {
        case sf::Event::KeyReleased:
          switch (event.key.code) {
            case sf::Keyboard::Up:
              menu.MoveUp(1);
              break;

            case sf::Keyboard::Down:
              menu.MoveDown(1);
              break;
          }

        case sf::Keyboard::Return:
          switch (menu.GetPressedItem()) {
          case 0:
            std::cout << "Drink Water.\n";
            newHab(hab.at(0));
            break;
          case 1: {
            std::cout << "Do yoga";
            newHab(hab.at(1));
            break;
          }

          break;
        }

        break;

      case sf::Event::Closed:
        window.close();
        break;
      }
    }
      window.clear();

      menu.drawList(window);

      window.display();
    }

  }

void newHab(Habits habit) {
 sf::RenderWindow window(sf::VideoMode(600, 600), "Habit", sf::Style::Titlebar | sf::Style::Close);
  Menu menu(window.getSize().x, window.getSize().y, habit);

  int n = habit.frequency;

  /*
    make text a vector with n elements
    in menu.cpp, save the position of all the positions
    setposition for each of the elements
  */

  sf::Font arial;
  arial.loadFromFile("arial.ttf");
  Textbox text(30, sf::Color::White, true);
  text.setFont(arial);
  //sf::Vector2f pos = menu.pos.at(0);
  // text.centerText();
  text.setPosition(menu.pos.at(1));
  text.setLimit(true, 20);

  while (window.isOpen()) {
    sf::Event event;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
      text.setSelected(true);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      text.setSelected(false);
    }
    while (window.pollEvent(event)) {
      switch(event.type){
        case sf::Event::Closed:
          window.close();
          //break;
        case sf::Event::TextEntered:
          text.typedOn(event);
          break;
      }
    }
    window.clear();

    menu.drawList(window);
    text.drawTo(window); // work on this

    window.display();

  }


}

std::vector<Habits> fileinput() {
  std::ifstream thisfile;

  std::vector<Habits> hab;
  Habits temp; 
  int counter = 1;

  thisfile.open("currenthabs.txt");
  std::string word;
  while (thisfile >> word) {
    if (counter == 1) {
      while (word.find('_',1) != std::string::npos) 
        word.replace(word.find('_',1),1," ");
      temp.name = word;
    }
    else if (counter == 2) 
      temp.amount = std::stof(word);
    else if (counter == 3) 
      temp.units = word;
    else if (counter == 4) 
      temp.frequency = std::stoi(word);
    else if (counter == 5) {
      temp.isDone = (word == "true");
      hab.push_back(temp);
      counter = 0;
    } // add another data point for daily average + today's amount? 
    counter++;
  }

  for (int i = 0; i < hab.size(); i++) {
    std::cout << hab.at(i).name << " " << hab.at(i).amount << " " << hab.at(i).units 
      << " " << hab.at(i).frequency << " " << hab.at(i).isDone << "\n";
  }

  thisfile.close();

  return hab;
}


void updateavg(std::string name, float todaysdata) {

  std::ifstream avgdata;

  avgdata.open("avgdata.txt");
  std::string word;
  int count = 1;
  std::string tempname;
  bool isHabit = false;
  float currentavg, newavg;
  int daysentered;

  while (avgdata >> word) {
    if (count == 1) {
      while (word.find('_',1) != std::string::npos) 
        word.replace(word.find('_',1),1," ");
      tempname = word;
      if (tempname == name) 
        isHabit = true;
    }
    else if (count == 2 && isHabit)
      currentavg = std::stof(word);
    else if (count == 3 && isHabit) {
      daysentered = std::stoi(word);
      break;
    }
    if (count == 3) 
      count = 0;
    count++; 
  }

  avgdata.close();

  newavg = (currentavg*daysentered + todaysdata)/(daysentered + 1);
  daysentered++;

  avgdata.open("avgdata.txt");
  std::string theline;
  std::vector<string> updatedfile;

  while (std::getline(avgdata, theline))
    updatedfile.push_back(theline);

  for (int i = 0; i < name.length(); i++) {
    if (name.at(i) == ' ')
      name.at(i) = '_';
  }

  for (int i = 0; i < updatedfile.size(); i++) {
    if (updatedfile.at(i).find(name) != std::string::npos) {
      updatedfile.at(i) = name + " " + std::to_string(newavg) 
        + " " + std::to_string(daysentered);
    }
  }

  avgdata.close();

  std::ofstream newdata;
  newdata.open("avgdata.txt", std::fstream::trunc);

  for (string s : updatedfile) 
    newdata << s << "\n";

  newdata.close();
}

int main() {

  std::vector<Habits> hab;
  hab = fileinput();
 // hab1.name = "Do yoga";


    sf::RenderWindow window(sf::VideoMode(600, 600), "Habit Tracker", sf::Style::Titlebar | sf::Style::Close);
    //does not allow for resizing

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
      sf::Event event;

      while(window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::KeyReleased:
          switch (event.key.code) {
          case sf::Keyboard::Up:
            menu.MoveUp(0);
            break;

          case sf::Keyboard::Down:
            menu.MoveDown(0);
            break;

          case sf::Keyboard::Return:
            switch (menu.GetPressedItem()) {
            case 0:
              std::cout << "User wants to input a new habit.\n";
              break;
            case 1: {
              makeList(hab);

              break;
            }
            case 2:
              std::cout << "User wants to view habit progress.\n";
              break;
            }

            break;
          }

          break;

        case sf::Event::Closed:
          window.close();
          break;
        }
      }

      window.clear();

      menu.drawMenu(window);

      window.display();
    }


    return 0;
  }

  /*things we need to generalize:
    the while loop with the switch statements
    menu.cpp 
      instead of having menu and list as separate, they could just be the same thing
      but with different number of items
  */