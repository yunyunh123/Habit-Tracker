#include "Menu.h"

Menu::Menu(float width, float height, std::vector<std::string> items) {
  if (!font.loadFromFile("arial.ttf")) {
    // handle error
  }

  num_items = items.size();
  menu.resize(num_items);
  sf::FloatRect textRect;
  pos.resize(num_items);

  // Setting up text
  for(int i = 0; i < num_items; i++) {
    menu.at(i).setFont(font);
    menu.at(i).setCharacterSize(30);
    menu.at(i).setOutlineThickness(10);

    if (i == 0)
      menu.at(i).setFillColor(sf::Color::Red);
    else
      menu.at(i).setFillColor(sf::Color::White);

    menu.at(i).setString(items.at(i));

    // Centering the text
    textRect = menu.at(i).getLocalBounds();
    menu.at(i).setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top + textRect.height/2.0f);
    pos.at(i) = sf::Vector2f(width / 2, height / (num_items + 1) * (i+1)); 
    menu.at(i).setPosition(pos.at(i));
  }

  selectedItemIndex = 0;
}

Menu::~Menu()
{

}

void Menu::drawMenu(sf::RenderWindow &window)
{
  for (int i = 0; i < num_items; i++)
  {
    window.draw(menu.at(i));
  }
}

void Menu::MoveUp()
{
  if (selectedItemIndex - 1 >= 0)
  {
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex--;
    menu[selectedItemIndex].setFillColor(sf::Color::Red);
  }
  
}

void Menu::MoveDown()
{
  if (selectedItemIndex + 1 < num_items)
  {
    menu.at(selectedItemIndex).setFillColor(sf::Color::White);
    selectedItemIndex++;
    menu.at(selectedItemIndex).setFillColor(sf::Color::Red);
  } 
}