//#include "SFML/Graphics.hpp"
#include "Menu.h"
//#include "Habits.h"
#include <iostream>

void makeList() {

  sf::RenderWindow window(sf::VideoMode(600, 600), "Track Habits", sf::Style::Titlebar | sf::Style::Close);
  Menu menu(window.getSize().x, window.getSize().y, 2);

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

        // case sf::Keyboard::Return:
        //   switch (menu.GetPressedItem()) {
        //   case 0:
        //     std::cout << "User wants to input a new habit.\n";
        //     break;
        //   case 1: {

        //     break;
        //   }

        //   break;
        // }

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


  int main() {

    // Habits hab1("Drink water");
    // Habits hab2("Do yoga");
    // std::vector<Habits> current_habs;
    // current_habs.push_back(hab1);
    // current_habs.push_back(hab2);

    // /std::cout << hab1.name;

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
              makeList();

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