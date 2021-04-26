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
const int MAX_HAB = 5;

// List of functions
void getMenuWindow(int width, int height, std::string name, std::vector<std::string> list,
                   bool ifnextlist, std::vector<std::function<void(void)>> nextlist);
void getMenuWindow(int width, int height, Habits habit);
void newHabit();
void userTrackHabits(Habits habit);
void trackHabits();
void viewProgress();
void updateavg(std::string name, float todaysdata);
float getCurrentAvg(std::string name);
std::vector<Habits> fileinput();

// Main
int main() {
  std::vector<std::string> list = {"New Habit (max: 5)", "Track Habit(s)", "View Habit Progress"};
  std::vector<std::function<void(void)>> functions{newHabit, trackHabits, viewProgress};
  getMenuWindow(WIDTH, HEIGHT, "Menu (press up or down key, press enter to select option)", list, true, functions);

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

// Creates menu window for a habit that allows for text input
void getMenuWindow(int width, int height, Habits habit) {
  std::string name = habit.name + " (enter value with at least 1 decimal place and close window when done)";
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
  sf::Vector2f center(-70.f, -30.f); // to center the textbox

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
  try {
    for (int i = 0; i < num_freq; i++) {
      runsum += std::stof(texts.at(i).getText());
    }
    updateavg(habit.name, runsum);
  } catch(const std::invalid_argument& ia) {
    std::cerr << "Invalid arguments. Please enter floats.\n";
    userTrackHabits(habit);
  }
}

void newHabit() {

  std::vector<Habits> habs = fileinput();
  int size = habs.size();
  if (size < MAX_HAB) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "New Habit (press up or down key to type in textboxes)");
    std::vector<Textbox> textbox;
    int num = 4;
    float x_pos_textbox = 350;
    float y_pos_textbox = 100;

    // Setting up textboxes
    sf::Font font;
    font.loadFromFile("arial.ttf");
    for (int i = 0; i < num; i++) {
      textbox.push_back(Textbox(30, sf::Color::White, false));
      textbox.at(i).setFont(font);
      textbox.at(i).setPosition({x_pos_textbox, y_pos_textbox + i * 100});
      textbox.at(i).setLimit(true, 12);

      if(i == 0)
        textbox.at(i).setSelected(true);
      else
        textbox.at(i).setSelected(false);
    }

    // Setting up texts
    int index = 1;

    while (window.isOpen()) {
      // displaying title
      string newhabit = "NEW HABIT";
      string nameH = "Habit Name:";
      string amountH = "Amount:\n(0<float)";
      string unitH = "Units:";
      string timingH = "Frequency:\n(0 < int <= 5)";
      string instruction1 = "Press up and down key to select textbox.";
      string instruction2 = "Fill out all 4 boxes. Close window when done.";
      // displaying in window using text_dash info
      sf::Text text1(newhabit, font);
      sf::Text text2(nameH, font, 25);
      sf::Text text3(amountH, font, 25);
      sf::Text text4(unitH, font, 25);
      sf::Text text5(timingH, font, 25);
      sf::Text text6(instruction1, font, 20);
      sf::Text text7(instruction2, font, 20);
      // creating 4 text boxes
      sf::RectangleShape name(sf::Vector2f(200, 50));
      sf::RectangleShape amount(sf::Vector2f(200, 50));
      sf::RectangleShape unit(sf::Vector2f(200, 50));
      sf::RectangleShape timing(sf::Vector2f(200, 50));

      // customizing their colors
      name.setFillColor(sf::Color::Transparent);
      amount.setFillColor(sf::Color::Transparent);
      unit.setFillColor(sf::Color::Transparent);
      timing.setFillColor(sf::Color::Transparent);

      // setting their position to be contralized
      name.setPosition(350.f, 100.f);
      amount.setPosition(350.f, 200.f);
      unit.setPosition(350.f, 300.f);
      timing.setPosition(350.f, 400.f);

      text1.setPosition(200.f, 30.f);
      text2.setPosition(50.f, 100.f);
      text3.setPosition(50.f, 200.f);
      text4.setPosition(50.f, 300.f);
      text5.setPosition(50.f, 400.f);
      text6.setPosition(75.f, 500.f);
      text7.setPosition(75.f, 550.f);
      name.setOutlineThickness(5);
      name.setOutlineColor(sf::Color::White);
      amount.setOutlineThickness(5);
      amount.setOutlineColor(sf::Color::White);
      unit.setOutlineThickness(5);
      unit.setOutlineColor(sf::Color::White);
      timing.setOutlineThickness(5);
      timing.setOutlineColor(sf::Color::White);

      for (int i = 0; i < num; i++) {
        textbox.at(i).drawTo(window);
      }

      window.draw(name);
      window.draw(amount);
      window.draw(unit);
      window.draw(timing);
      window.draw(text1);
      window.draw(text2);
      window.draw(text3);
      window.draw(text4);
      window.draw(text5);
      window.draw(text6);
      window.draw(text7);

      window.display();
      sf::Event Event;

      while (window.pollEvent(Event)) {
        if (Event.type == sf::Event::Closed) {
          window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
          if (index == 4) {
            textbox.at(3).setSelected(false);
            index --;
            textbox.at(2).setSelected(true);
          } else if (index == 3) {
            textbox.at(2).setSelected(false);
            index --;
            textbox.at(1).setSelected(true);
          } else if (index == 2) {
            textbox.at(1).setSelected(false);
            index --;
            textbox.at(0).setSelected(true);
          }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
          if (index == 1) {
            textbox.at(0).setSelected(false);
            index ++;
            textbox.at(1).setSelected(true);
          } else if (index == 2) {
            textbox.at(1).setSelected(false);
            index ++;
            textbox.at(2).setSelected(true);
          } else if (index == 3) {
            textbox.at(2).setSelected(false);
            index ++;
            textbox.at(3).setSelected(true);
          }
        }

        if (Event.type == sf::Event::TextEntered) {
          for (int i = 0; i < num; i++) {
            textbox.at(i).typedOn(Event);
          }
        }
        window.clear(sf::Color::Black);
      }

    }

    string habitname = textbox.at(0).getText();

    for (int i = 0; i < habitname.length(); i++) {
      if (habitname.at(i) == ' ')
        habitname.at(i) = '_';
    }

    string unitname = textbox.at(2).getText();
    float amount;
    int freq;

    try {
      amount = std::stof(textbox.at(1).getText());
      freq = std::stoi(textbox.at(3).getText());

      if (amount <= 0 or freq <= 0 or freq > 5) {
        newHabit();
      } else {
        // Store entries in currenthabs.txt and avgdata.txt
        string entry = habitname + " " + std::to_string(amount) + " " + unitname + " " + std::to_string(freq) + " " + "false";
        std::ofstream myfile;
        myfile.open("currenthabs.txt", std::fstream::app);
        myfile << entry << "\n";
        myfile.close();

        std::ofstream avgdata;
        avgdata.open("avgdata.txt", std::fstream::app);
        entry = habitname + " 0 0";
        avgdata << entry << "\n";
        avgdata.close();
      }
    } catch(const std::invalid_argument& ia) {
      std::cerr << "Invalid arguments.\n";
      newHabit();
    }
  }
}

void userTrackHabits(Habits habit) {
  getMenuWindow(WIDTH, HEIGHT, habit);
}

void trackHabits() {
  std::vector<Habits> habit_list;
  habit_list = fileinput();

  // Creates list of each habit name
  std::vector<std::string> list;
  for (auto i : habit_list)
    list.push_back(i.name);

  std::vector<std::function<void(void)>> empty{};
  getMenuWindow(WIDTH, HEIGHT, "Track Habit(s) (press up or down key, press enter to select option)",
                list, true, empty);
}

void viewProgress() {
  std::vector<std::string> list = {"Progress: daily averages"};
  std::vector<Habits> habit_list;
  habit_list = fileinput();
  std::string line;
  int num = habit_list.size();
  float currentavg;

  for (int i = 0; i < num; i++) {
    currentavg = getCurrentAvg(habit_list.at(i).name);
    line = habit_list.at(i).name + ": " + std::to_string(currentavg);
    list.push_back(line);
  }


  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Progress (daily averages)",
                          sf::Style::Titlebar | sf::Style::Close);
  Menu menu(WIDTH, HEIGHT, list);

  while(window.isOpen()) {
    sf::Event event;

    while(window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    menu.drawMenu(window);
    window.display();
  }
}

// Returns the current habits that the user wants to track
std::vector<Habits> fileinput() {
  std::ifstream thisfile;

  std::vector<Habits> hab;
  Habits temp;
  int counter = 1;

  thisfile.open("currenthabs.txt");
  std::string word;
  while (thisfile >> word) {
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
    } // add another data point for daily average + today's amount?
    counter++;
  }


  thisfile.close();

  return hab;
}

float getCurrentAvg(std::string name) {
  std::ifstream avgdata;
  avgdata.open("avgdata.txt");
  std::string word;
  int count = 1;
  std::string tempname;
  bool isHabit = false;
  float currentavg = 0;

  while (avgdata >> word) {
    if (count == 1 and (isHabit == false)) {
      while (word.find('_', 1) != std::string::npos)
        word.replace(word.find('_', 1), 1, " ");
      tempname = word;
      if (tempname == name)
        isHabit = true;
    } else if (count == 2 && isHabit) {
      currentavg = std::stof(word);
      break;
    }

    if (count == 3)
      count = 0;
    count++;
  }

  avgdata.close();

  return currentavg;
}

// Updates the average amount done per day for each habit
void updateavg(std::string name, float todaysdata) {

  std::ifstream avgdata;
  avgdata.open("avgdata.txt");
  std::string word;
  int count = 1;
  std::string tempname;
  bool isHabit = false;
  float currentavg, newavg;
  int daysentered;

  while (avgdata >> word) {
    if (count == 1) {
      while (word.find('_', 1) != std::string::npos)
        word.replace(word.find('_', 1), 1, " ");
      tempname = word;
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

  newavg = (currentavg * daysentered + todaysdata) / (daysentered + 1);
  daysentered++;

  avgdata.open("avgdata.txt");
  std::string theline;
  std::vector<string> updatedfile;

  while (std::getline(avgdata, theline))
    updatedfile.push_back(theline);

  for (int i = 0; i < name.length(); i++) {
    if (name.at(i) == ' ')
      name.at(i) = '_';
  }

  for (int i = 0; i < updatedfile.size(); i++) {
    if (updatedfile.at(i).find(name) != std::string::npos) {
      updatedfile.at(i) = name + " " + std::to_string(newavg)
                          + " " + std::to_string(daysentered);
    }
  }

  avgdata.close();

  std::ofstream newdata;
  newdata.open("avgdata.txt", std::fstream::trunc);

  for (string s : updatedfile)
    newdata << s << "\n";

  newdata.close();
}

