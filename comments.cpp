// Copyright 2021 Rebecca Turi bturi@bu.edu
// Copyright 2021 Nir Shukrun nshukrun@bu.edu
// Copyright 2021 Julia Hua jhua2@bu.edu
// Copyright 2021 Lisa Korver lkorver@bu.edu
#include "Menu.h"
#include <iostream>
#include "Textbox.h"
#include <fstream>
#include <functional>

const int WIDTH = 600;
const int HEIGHT = 600;

// List of functions
void getMenuWindow(int width, int height, std::string name, std::vector<std::string> list,
                   bool ifnextlist, std::vector<std::function<void(void)>> nextlist);
void getMenuWindow(int width, int height, Habits habit);
void newHabit();
void userTrackHabits(Habits habit);
void trackHabits();
void viewProgress();
void updateavg(std::string name, float todaysdata);
std::vector<Habits> fileinput();

// Main
int main() {
  std::vector<std::string> list = {"New Habit", "Track Habit(s)", "View Habit Progress"};
  std::vector<std::function<void(void)>> functions{newHabit, trackHabits, viewProgress};
  getMenuWindow(WIDTH, HEIGHT, "Menu (press up or down key)", list, true, functions);

  return 0;
}

/* Creates a menu window.
   The variable "ifnextlist" indicates whether this menu window should lead to a new menu window.
   If "ifnextlist" == true, then the function will either use:
      - nextlist (if any function exists in the vector "nextlist")
      - userTrackHabits (if no function exists in the vector "nextlist")
*/
void getMenuWindow(int width, int height, std::string name, std::vector<std::string> list,
                   bool ifnextlist, std::vector<std::function<void(void)>> nextlist) {
  sf::RenderWindow window(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
  Menu menu(width, height, list);

  int num = list.size();
  int index = 0;
  std::vector<Habits> habit_list;
  habit_list = fileinput();

  // Game loop
  while (window.isOpen()) {
    sf::Event event;

    /* Checks for:
        - keyboard input: Up, Down, Return
        - window closed by clicking X button in title bar
    */
    while(window.pollEvent(event)) {
      switch(event.type) {
      case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::Up) {
          menu.MoveUp();
        } else if (event.key.code == sf::Keyboard::Down) {
          menu.MoveDown();
        } else if ((event.key.code == sf::Keyboard::Return) && (ifnextlist == true)) {
          index = menu.GetPressedItem();

          if(not nextlist.empty()) {
            for(int i = 0; i < num; i++) {
              if (index == i) {
                nextlist.at(i)();
              }
            }
          } else {
            userTrackHabits(habit_list.at(index));
          }
        }
        break;

      case sf::Event::Closed:
        window.close();
        break;
      }
    }

    // Redraws window
    window.clear();
    menu.drawMenu(window);
    window.display();

  }
}

// Creates menu window that allows for text input
void getMenuWindow(int width, int height, Habits habit) {
  std::string name = habit.name + " (type the amount in numbers and close window when done)";
  sf::RenderWindow window(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);

  // Creating the list to be displayed in the menu
  std::vector<std::string> list;
  int num_freq = habit.frequency;
  int num_list = num_freq + 1;
  list.resize(num_list);

  list.at(0) = habit.name + " (" + std::to_string(habit.amount) + " " + habit.units + "/day)";
  for (int i = 1; i <= num_freq; i++) {
    list.at(i) = std::to_string(i) + ". ________" + habit.units;
  }

  Menu menu(WIDTH, HEIGHT, list);

  // Setting up textboxes
  sf::Font arial;
  arial.loadFromFile("arial.ttf");
  std::vector<Textbox> texts;
  sf::Vector2f center(-50.f, -30.f); // to center the textbox

  for (int i = 0; i < num_freq; i++) {
    if (i == 0)
      texts.push_back(Textbox(30, sf::Color::White, true));
    else
      texts.push_back(Textbox(30, sf::Color::White, false));

    texts.at(i).setFont(arial);

    texts.at(i).setPosition(menu.pos.at(i + 1) + center);
    texts.at(i).setLimit(true, 5);
  }

  // Game loop
  int ind = 0;
  while (window.isOpen()) {
    sf::Event event;
    window.pollEvent(event);

    // Checks for keyboard input: Return or Escape
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Return) {
        if (ind + 1 < num_freq) {
          texts.at(ind).setSelected(false);
          ind++;
          texts.at(ind).setSelected(true);
        }
      }
      if (event.key.code == sf::Keyboard::Escape) {
        texts.at(ind).setSelected(false);
        ind = 0;
        texts.at(ind).setSelected(true);
      }
    }

    // Checks for text input
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::TextEntered) {
        texts.at(ind).typedOn(event);
      }
    }

    // Checks for window closed by clicking X button in title bar
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    // Redraws window
    window.clear();
    menu.drawMenu(window);
    for (int i = 0; i < num_freq; i++) {
      texts.at(i).drawTo(window);
    }
    window.display();
  }

  // Calculates total amount inputted by user and updates avgdata.txt
  float runsum = 0;
  for (int i = 0; i < num_freq; i++) {
    try {
      runsum += std::stof(texts.at(i).getText());
    } catch(const std::invalid_argument& ia) {
      std::cerr << "Invalid arguments. Please enter numbers.\n";
      userTrackHabits(habit);
    }
  }
  updateavg(habit.name, runsum);
}

void newHabit() { 
}

void userTrackHabits(Habits habit) { getMenuWindow(WIDTH, HEIGHT, habit); }

void trackHabits() {
  std::vector<Habits> habit_list;
  habit_list = fileinput();

  // Creates list of each habit name
  std::vector<std::string> list;
  for (auto i : habit_list)
    list.push_back(i.name);

  std::vector<std::function<void(void)>> empty{};
  getMenuWindow(WIDTH, HEIGHT, "Track Habit(s) (press up or down key)",
    list, true, empty);
}

void viewProgress() {
}

/* Reads from the file "currenthabs.txt" where the data for each habit 
is stored on separate lines, with spaces separating each data point 
then returns a vector of all current habits */
std::vector<Habits> fileinput() {
  std::ifstream thisfile;

  std::vector<Habits> hab;
  Habits temp;
  int counter = 1;
  thisfile.open("currenthabs.txt");
  std::string word;

  // Reads from the file word by word 
  while (thisfile >> word) {
    // counts through each data point and assigns then to the appropriate object
    if (counter == 1) {
      while (word.find('_', 1) != std::string::npos)
        word.replace(word.find('_', 1), 1, " ");
      temp.name = word;
    } else if (counter == 2)
      temp.amount = std::stof(word);
    else if (counter == 3)
      temp.units = word;
    else if (counter == 4)
      temp.frequency = std::stoi(word);
    else if (counter == 5) {
      temp.isDone = (word == "true");
      hab.push_back(temp);
      counter = 0;
    } 
    counter++;
  }


  thisfile.close();

  return hab;
}

// Calculates new average from data input and updates the "avgdata.txt" data file
void updateavg(std::string name, float todaysdata) {

  std::ifstream avgdata;

  avgdata.open("avgdata.txt");
  std::string word;
  int count = 1;
  std::string tempname;
  bool isHabit = false;
  float currentavg, newavg;
  int daysentered;

  // Reads the file word by word, counting through each line 
  while (avgdata >> word) {
    if (count == 1) {
      while (word.find('_', 1) != std::string::npos)
        word.replace(word.find('_', 1), 1, " ");
      tempname = word;
      // see if the current line is the habit we are checking for
      if (tempname == name)
        isHabit = true;
    } else if (count == 2 && isHabit)
      currentavg = std::stof(word);
    else if (count == 3 && isHabit) {
      daysentered = std::stoi(word);
      break;
    }
    if (count == 3)
      count = 0;
    count++;
  }

  avgdata.close();

  // calculate the new average and add another day entered
  newavg = (currentavg * daysentered + todaysdata) / (daysentered + 1);
  daysentered++;

  // read from the file again to create a vector of string with each line
  avgdata.open("avgdata.txt");
  std::string theline;
  std::vector<string> updatedfile;

  while (std::getline(avgdata, theline))
    updatedfile.push_back(theline);
  for (int i = 0; i < name.length(); i++) {
    if (name.at(i) == ' ')
      name.at(i) = '_';
  }

  // find the line to update and add the new information
  for (int i = 0; i < updatedfile.size(); i++) {
    if (updatedfile.at(i).find(name) != std::string::npos) {
      updatedfile.at(i) = name + " " + std::to_string(newavg)
                          + " " + std::to_string(daysentered);
    }
  }

  avgdata.close();

  // output the data to the file again
  std::ofstream newdata;
  newdata.open("avgdata.txt", std::fstream::trunc);

  for (string s : updatedfile)
    newdata << s << "\n";

  newdata.close();
}
