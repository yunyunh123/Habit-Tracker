#include "Habits.h"

Habits::Habits(std::string name, float amount, std::string units, int frequency){
  this->name = name;
  this->amount = amount;
  this->units = units;
  this->frequency = frequency;
}

Habits::~Habits() {
}

