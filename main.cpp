//#include "SFML/Graphics.hpp"
#include "Menu.h"
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Habit Tracker",sf::Style::Titlebar | sf::Style::Close);
  //does not allow for resizing

  Menu menu(window.getSize().x, window.getSize().y);

  while (window.isOpen()) {
    sf::Event event;

    while(window.pollEvent(event)) {
      switch(event.type) 
      {
        case sf::Event::KeyReleased:
          switch (event.key.code) 
          {
            case sf::Keyboard::Up:
              menu.MoveUp();
              break;

            case sf::Keyboard::Down:
              menu.MoveDown();
              break;

            case sf::Keyboard::Return:
              switch (menu.GetPressedItem())
              {
                case 0:
                  std::cout << "User wants to input a new habit.\n";
                  break;
                case 1:
                  std::cout << "User wants to track habit(s).\n";
                  break;
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

    menu.draw(window);

    window.display();
  }


  return 0;
}