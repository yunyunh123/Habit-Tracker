#pragma
#include <vector>
#include <string>

class Habits {
public:
  Habits() {}
  Habits(std::string name, float amount, std::string units, int frequency);
  ~Habits();
  std::string name;
  bool isDone;
  float amount = 0;
  std::string units;
  int frequency = 1;

  //static int num_hab;
};

//Habits::num_hab = 0;
