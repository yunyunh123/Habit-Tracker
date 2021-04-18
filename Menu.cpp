#include "Menu.h"
//#include <iostream> // take out later
Menu::Menu(float width, float height) {
  if (!font.loadFromFile("arial.ttf")) {
    // handle error
  }


  menu[0].setFont(font);
  menu[0].setFillColor(sf::Color::Red);
  menu[0].setString("New Habit");
  sf::FloatRect textRect = menu[0].getLocalBounds(); // to center the text
  menu[0].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
  menu[0].setPosition(sf::Vector2f(width / 2, height / (NUM_ITEMS + 1) * 1));

  menu[1].setFont(font);
  menu[1].setFillColor(sf::Color::White);
  menu[1].setString("Track Habit(s)");
  textRect = menu[1].getLocalBounds();
  menu[1].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
  menu[1].setPosition(sf::Vector2f(width / 2, height / (NUM_ITEMS + 1) * 2));

  menu[2].setFont(font);
  menu[2].setFillColor(sf::Color::White);
  menu[2].setString("View Habit Progress");
  textRect = menu[2].getLocalBounds();
  menu[2].setOrigin(textRect.left + textRect.width/2.0f,
                    textRect.top + textRect.height/2.0f);
  menu[2].setPosition(sf::Vector2f(width / 2, height / (NUM_ITEMS + 1) * 3));

  selectedItemIndex = 0;
}

Menu::Menu(float width, float height, int test){ //std::vector<Habits> hab) {
   // std::cout << "works";
  Habits hab1("Drink water"); // move back to main
  Habits hab2("Do yoga");
  std::vector<Habits> hab;
  hab.push_back(hab1);
  hab.push_back(hab2);


  if (!font.loadFromFile("arial.ttf")) {
    // handle error
  }

  int num = hab.size();

  //sf::Text list[num];
  sf::FloatRect textRect;
  // get the text on it
  // decide how user clicks/enters in?

  for (int i = 0; i < num; i++) {
    list[i].setFont(font);
    if (i == 0)
      list[i].setFillColor(sf::Color::Red);
    else
      list[i].setFillColor(sf::Color::White);

    list[i].setString(hab.at(i).name);
    textRect = list[i].getLocalBounds();
    list[i].setOrigin(textRect.left + textRect.width/2.0f,
                      textRect.top + textRect.height/2.0f);
    list[i].setPosition(sf::Vector2f(width / 2, height / (num + 1) * (i+1)));

  }

  selectedItemIndex = 0;
  // max num of habits??
  // return to menu

}


Menu::~Menu()
{

}

void Menu::drawMenu(sf::RenderWindow &window)
{
  for (int i = 0; i < NUM_ITEMS; i++)
  {
    window.draw(menu[i]);
  }

}

void Menu::drawList(sf::RenderWindow &window)
{
  for (int i = 0; i < list_num; i++) 
  {
    window.draw(list[i]);
  }

}

void Menu::MoveUp(int n) // if menu = 0, if tracking habits = 1
{
  if (n == 0)
  {
    if (selectedItemIndex - 1 >= 0)
    {
      menu[selectedItemIndex].setFillColor(sf::Color::White);
      selectedItemIndex--;
      menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
  }
  else if (n == 1) {
    if (selectedItemIndex - 1 >= 0)
    {
      list[selectedItemIndex].setFillColor(sf::Color::White);
      selectedItemIndex--;
      list[selectedItemIndex].setFillColor(sf::Color::Red);
    }
  }
}

void Menu::MoveDown(int n)
{
  if (n == 0) {
    if (selectedItemIndex + 1 < NUM_ITEMS)
    {
      menu[selectedItemIndex].setFillColor(sf::Color::White);
      selectedItemIndex++;
      menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
  }
  else if (n == 1) {
    if (selectedItemIndex + 1 < list_num)
    {
      list[selectedItemIndex].setFillColor(sf::Color::White);
      selectedItemIndex++;
      list[selectedItemIndex].setFillColor(sf::Color::Red);
    }
  }
}