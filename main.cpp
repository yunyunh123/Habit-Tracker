//#include "SFML/Graphics.hpp"
#include "Menu.h"
//#include "Habits.h"
#include <iostream>



int main()
{

  Habits hab1("Drink water");
  Habits hab2("Do yoga");
  std::vector<Habits> current_habs;
  current_habs.push_back(hab1);
  current_habs.push_back(hab2);

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
                case 1: {
                  sf::RenderWindow window2(sf::VideoMode(600, 600), "Track Habits",sf::Style::Titlebar | sf::Style::Close);
                  Menu track_hab(window2.getSize().x, window2.getSize().y, current_habs);
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

    menu.draw(window);

    window.display();
  }


  return 0;
}