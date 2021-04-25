#pragma
#include <vector>
#include <string>

class Habits {
public:
  // Constructors and Destructors
  Habits() {}
  Habits(std::string name, float amount, std::string units, int frequency);
  ~Habits();

  // Public members
  std::string name;
  std::string units;
  int frequency = 1;
  float amount = 0;
  bool isDone = false;
};
