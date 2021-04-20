#pragma
#include "SFML/Graphics.hpp"
#include "Habits.h"
#include <vector>

#define NUM_ITEMS 3

class Menu {
public:
  Menu(float width, float height);
  Menu(float width, float height, std::vector<Habits>);//std::vector<Habits>);
  Menu(float width, float height, Habits hab);
  ~Menu();
  void drawMenu(sf::RenderWindow &window);
  void drawList(sf::RenderWindow &window);
  void MoveUp(int n);
  void MoveDown(int n);
  int GetPressedItem() { return selectedItemIndex; }
  int list_num; // generalize later
  std::vector<sf::Vector2f> pos;
private:
  int selectedItemIndex;
  sf::Font font;
  sf::Text menu[NUM_ITEMS];
  std::vector<sf::Text> list; // generalize later
};