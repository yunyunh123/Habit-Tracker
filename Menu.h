#pragma
#include "SFML/Graphics.hpp"
#include "Habits.h"
#include <vector>
#include <string>

#define NUM_ITEMS 3

class Menu {
public:
  // Constructor and Destructor
  Menu(float width, float height, std::vector<std::string> items);
  ~Menu();

  // Public functions
  void drawMenu(sf::RenderWindow &window);
  void MoveUp();
  void MoveDown();
  int GetPressedItem() { return selectedItemIndex; }

  // Public member
  std::vector<sf::Vector2f> pos;
private:
  // Private members
  int num_items;
  int selectedItemIndex;
  sf::Font font;
  std::vector<sf::Text> menu;
};