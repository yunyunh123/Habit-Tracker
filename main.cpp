//#include "SFML/Graphics.hpp"
#include "Menu.h"
//#include "Habits.h"
#include <iostream>
#include "Textbox.h"

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
  text.centerText();
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

int main() {

  Habits hab1("Drink water", 8, "cups", 1); // move back to main
  Habits hab2("Do yoga", 15, "min", 3);
  std::vector<Habits> hab;
  hab.push_back(hab1);
  hab.push_back(hab2);

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