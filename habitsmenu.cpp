#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include <string>
#include<sstream>
#include <fstream>

using std::string;
using std::to_string;
using std::cout;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#include "Textbox.h"
#include "Menu.h"

 int main(){
 sf::RenderWindow window(sf::VideoMode(600.f,600.f),"Window");

//  Textbox textbox1(15, sf::Color::White,false);
//  sf::Font font;
//  font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
//  textbox1.setFont(font);
// textbox1.setPosition({350,100});
// textbox1.setLimit(true, 20);

Textbox textbox1(15, sf::Color::White,false);
 sf::Font font;
 font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
 textbox1.setFont(font);
textbox1.setPosition({350,100});
textbox1.setLimit(true, 20);

Textbox textbox2(15, sf::Color::White,false);
 textbox2.setFont(font);
textbox2.setPosition({350,200});
textbox2.setLimit(true, 20);

Textbox textbox3(15, sf::Color::White,false);
 textbox3.setFont(font);
textbox3.setPosition({350,300});
textbox3.setLimit(true, 20);

Textbox textbox4(15, sf::Color::White,false);
 textbox4.setFont(font);
textbox4.setPosition({350,400});
textbox4.setLimit(true, 20);

while (window.isOpen()) {
// displaying title
    string newhabit = "NEW HABIT";
    string nameH = "Habit Name:";
    string amountH = "Amount:";
    string unitH = "Units:";
    string timingH = "Frequency:";
    string instruction1 = "X out of window (Top right corner)";
    string instruction2 = "once you have filled all 4 boxes";
    // displaying in window using text_dash info
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    sf::Text text1(newhabit, font);
    sf::Text text2(nameH, font);
    sf::Text text3(amountH, font);
    sf::Text text4(unitH, font);
    sf::Text text5(timingH, font);
    sf::Text text6(instruction1, font);
    sf::Text text7(instruction2, font);
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
    text6.setPosition(75.f,500.f);
    text7.setPosition(75.f,550.f);
    name.setOutlineThickness(5);
    name.setOutlineColor(sf::Color::White);
    amount.setOutlineThickness(5);
    amount.setOutlineColor(sf::Color::White);
    unit.setOutlineThickness(5);
    unit.setOutlineColor(sf::Color::White);
    timing.setOutlineThickness(5);
    timing.setOutlineColor(sf::Color::White);

textbox1.drawTo(window);
textbox2.drawTo(window);
textbox3.drawTo(window);
textbox4.drawTo(window);
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

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) {
    textbox1.setSelected(true);
    textbox2.setSelected(false);
    textbox3.setSelected(false);
    textbox4.setSelected(false);
}
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
    textbox1.setSelected(false);
    textbox2.setSelected(true);
    textbox3.setSelected(false);
    textbox4.setSelected(false);
} 
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
    textbox1.setSelected(false);
    textbox2.setSelected(false);
    textbox3.setSelected(true);
    textbox4.setSelected(false);
} 
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    textbox1.setSelected(false);
    textbox2.setSelected(false);
    textbox3.setSelected(false);
    textbox4.setSelected(true);
} 



while (window.pollEvent(Event)) {
    if (Event.type == sf::Event::Closed) {
        window.close();  
    }
    if (Event.type == sf::Event::TextEntered) {
  textbox1.typedOn(Event);
  textbox2.typedOn(Event);
  textbox3.typedOn(Event);
  textbox4.typedOn(Event);

}
window.clear(sf::Color::Black);
}

}

string habitname = textbox1.getText();

for (int i = 0; i< habitname.length(); i++) {
    if (habitname.at(i) == ' ')
        habitname.at(i) = '_';
}

string amountname = textbox2.getText();
string unitname = textbox3.getText();
string freqname = textbox4.getText();

//push back into a text file 
string entry = habitname + " " + amountname + " " + unitname + " " + freqname + " " + "false";
std::ofstream myfile;
myfile.open("currenthabs.txt",std::fstream::app);
myfile << entry << '\n';
myfile.close();

return 0;
}