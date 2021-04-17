#pragma
#include <vector>
#include <string>

class Habits {
public:
  Habits(std::string hab_name);
  ~Habits();
  std::string name;
  bool isDone;
  //static int num_hab;
};

//Habits::num_hab = 0;
