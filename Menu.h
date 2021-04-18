#pragma
#include "SFML/Graphics.hpp"
#include "Habits.h"


#define NUM_ITEMS 3

class Menu {
public:
  Menu(float width, float height);
  Menu(float width, float height, int test);//std::vector<Habits>);
  ~Menu();
  void drawMenu(sf::RenderWindow &window);
  void drawList(sf::RenderWindow &window);
  void MoveUp(int n);
  void MoveDown(int n);
  int GetPressedItem() { return selectedItemIndex; }
  int list_num = 2; // generalize later
private:
  int selectedItemIndex;
  sf::Font font;
  sf::Text menu[NUM_ITEMS];
  sf::Text list[2]; // generalize later
};