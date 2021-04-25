//#include "SFML/Graphics.hpp"
#include "Menu.h"
//#include "Habits.h"
#include <iostream>
#include "Textbox.h"
#include <fstream>


void newHab(Habits habit);
void updateavg(std::string name, float todaysdata);

void makeList(std::vector<Habits> hab) {

  sf::RenderWindow window(sf::VideoMode(600, 600), "Track Habits", sf::Style::Titlebar | sf::Style::Close);
  Menu menu(window.getSize().x, window.getSize().y, hab);

  int num = hab.size();
  int index = 0;

  while (window.isOpen()) {
    sf::Event event;

    while(window.pollEvent(event)) {
      switch(event.type) {
      case sf::Event::KeyReleased: // case 1
        if(event.key.code == sf::Keyboard::Up) {
          menu.MoveUp(1);
        } else if (event.key.code == sf::Keyboard::Down) {
          menu.MoveDown(1);
        } else if (event.key.code == sf::Keyboard::Return) {
          index = menu.GetPressedItem();
          for(int i = 0; i < num; i++) {
            if (index == i) {
              std::cout << hab.at(i).name << std::endl; // take this out later
              newHab(hab.at(i));
            }
          }
        }
        break;
      // switch (menu.GetPressedItem()) {
      // case 0:
      //   std::cout << "Drink Water.\n";
      //   newHab(hab.at(0));
      //   break;
      // case 1: {
      //   std::cout << "Do yoga";
      //   newHab(hab.at(1));
      //   break;

      case sf::Event::Closed: // case 2
        window.close();
        break;
      }
    }
    window.clear();

    menu.drawList(window);

    window.display();
  }

}

void newHab(Habits habit) {
  sf::RenderWindow window(sf::VideoMode(600, 600), "Habit", sf::Style::Titlebar | sf::Style::Close);
  Menu menu(window.getSize().x, window.getSize().y, habit);

  int n = habit.frequency;

  /*
    make text a vector with n elements
    in menu.cpp, save the position of all the positions
    setposition for each of the elements
  */

  sf::Font arial;
  arial.loadFromFile("arial.ttf");

  std::vector<Textbox> texts;
  sf::Vector2f center(-50.f, -30.f);

  for (int i = 0; i < n; i++) { // creating the textboxes with the first selected
    if (i == 0)
      texts.push_back(Textbox(30, sf::Color::White, true));
    else
      texts.push_back(Textbox(30, sf::Color::White, false));

    texts.at(i).setFont(arial);

    texts.at(i).setPosition(menu.pos.at(i + 1) + center);
    texts.at(i).setLimit(true, 5);
  }

  int ind = 0;

  while (window.isOpen()) { 
    sf::Event event;

    window.pollEvent(event);

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Return) {
        if (ind + 1 < n) {

          texts.at(ind).setSelected(false);
          ind++;
          texts.at(ind).setSelected(true);
        }
      }
      if (event.key.code == sf::Keyboard::Escape) {
        cout << "index: " << ind << std::endl;
        texts.at(ind).setSelected(false);
        ind = 0;
        texts.at(ind).setSelected(true);
      }
    }

    while (window.pollEvent(event)) {


      if (event.type == sf::Event::TextEntered){ // case 1: text entered
        texts.at(ind).typedOn(event);
      }


    }

    if (event.type == sf::Event::Closed){ // case two

        window.close();
      }


    window.clear();

    menu.drawList(window);

    // for (auto i : texts)
    //   i.drawTo(window); // work on this

    for (int i = 0; i < n; i++) {
      texts.at(i).drawTo(window);
    }

    window.display();

  }

  for (int i = 0; i < n; i++) {
    cout << texts.at(i).getText() << " ";
  }


  // updateavg(habits.name, summed up values)


}


std::vector<Habits> fileinput() {
  std::ifstream thisfile;

  std::vector<Habits> hab;
  Habits temp; 
  int counter = 1;

  thisfile.open("currenthabs.txt");
  std::string word;
  while (thisfile >> word) {
    if (counter == 1) {
      while (word.find('_',1) != std::string::npos) 
        word.replace(word.find('_',1),1," ");
      temp.name = word;
    }
    else if (counter == 2) 
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

  for (int i = 0; i < hab.size(); i++) {
    std::cout << hab.at(i).name << " " << hab.at(i).amount << " " << hab.at(i).units 
      << " " << hab.at(i).frequency << " " << hab.at(i).isDone << "\n";
  }

  thisfile.close();

  return hab;
}



int main() {

  // Habits hab1("Drink water", 8, "cups", 1); // move back to main
  // Habits hab2("Do yoga", 15, "min", 3);
  // std::vector<Habits> hab;
  // hab.push_back(hab1);
  // hab.push_back(hab2);

  std::vector<Habits> hab;
  hab = fileinput();
// hab1.name = "Do yoga";


  sf::RenderWindow window(sf::VideoMode(600, 600), "Habit Tracker", sf::Style::Titlebar | sf::Style::Close);
  //does not allow for resizing

  Menu menu(window.getSize().x, window.getSize().y);

  while (window.isOpen()) {
    sf::Event event;

    while(window.pollEvent(event)) {
      switch(event.type) {
      case sf::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Up:
          menu.MoveUp(0);
          break;

        case sf::Keyboard::Down:
          menu.MoveDown(0);
          break;

        case sf::Keyboard::Return:
          switch (menu.GetPressedItem()) {
          case 0:
            std::cout << "User wants to input a new habit.\n";
            break;
          case 1: {
            makeList(hab);

            break;
          }
          case 2:
            std::cout << "User wants to view habit progress.\n";
            break;
          }

          break;
        }

        break;

      case sf::Event::Closed:
        window.close();
        break;
      }
    }

    window.clear();

    menu.drawMenu(window);

    window.display();
  }


  return 0;
}

/*things we need to generalize:
  the while loop with the switch statements
  menu.cpp
    instead of having menu and list as separate, they could just be the same thing
    but with different number of items

*/


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
      while (word.find('_',1) != std::string::npos) 
        word.replace(word.find('_',1),1," ");
      tempname = word;
      if (tempname == name) 
        isHabit = true;
    }
    else if (count == 2 && isHabit)
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

  newavg = (currentavg*daysentered + todaysdata)/(daysentered + 1);
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

