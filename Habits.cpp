#include "Habits.h"

//int Habits::num_hab = 0;

Habits::Habits(std::string name, float amount, std::string units, int frequency){

  this->name = name;
  this->amount = amount;
  this->units = units;
  this->frequency = frequency;
  isDone = false;


  //num_hab++;

}

Habits::~Habits() {

}

