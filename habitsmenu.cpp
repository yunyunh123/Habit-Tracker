#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include <string>
#include<sstream>

using std::string;
using std::to_string;
using std::cout;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#include "Textbox.h"

 int main(){
 sf::RenderWindow window(sf::VideoMode(600.f,600.f),"Window");

// //window.setFramerateLimit(10);

 Textbox textbox1(15, sf::Color::White,false);
 sf::Font font;
 font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
 textbox1.setFont(font);
textbox1.setPosition({350,100});
textbox1.setLimit(true, 20);

while (window.isOpen()) {
// displaying title
    string newhabit = "NEW HABIT";
    string nameH = "Habit Name:";
    string amountH = "Amount:";
    string unitH = "Units:";
    string timingH = "Frequency:";
    // displaying in window using text_dash info
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    sf::Text text1(newhabit, font);
    sf::Text text2(nameH, font);
    sf::Text text3(amountH, font);
    sf::Text text4(unitH, font);
    sf::Text text5(timingH, font);
    // creating 4 text boxes
    sf::RectangleShape name(sf::Vector2f(200, 50));
    sf::RectangleShape amount(sf::Vector2f(200, 50));
    sf::RectangleShape unit(sf::Vector2f(200, 50));
    sf::RectangleShape timing(sf::Vector2f(200, 50));
    sf::RectangleShape reset(sf::Vector2f(200, 50));
    sf::RectangleShape finish(sf::Vector2f(200, 50));
    // customizing their colors
    name.setFillColor(sf::Color::Transparent);
    amount.setFillColor(sf::Color::Transparent);
    unit.setFillColor(sf::Color::Transparent);
    timing.setFillColor(sf::Color::Transparent);
    reset.setFillColor(sf::Color::White);
    finish.setFillColor(sf::Color::White);
    // setting their position to be contralized
    name.setPosition(350.f, 100.f);
    amount.setPosition(350.f, 200.f);
    unit.setPosition(350.f, 300.f);
    timing.setPosition(350.f, 400.f);
    reset.setPosition(50.f, 500.f);
    finish.setPosition(350.f, 500.f);

    text1.setPosition(200.f, 30.f);
    text2.setPosition(50.f, 100.f);
    text3.setPosition(50.f, 200.f);
    text4.setPosition(50.f, 300.f);
    text5.setPosition(50.f, 400.f);

    name.setOutlineThickness(5);
    name.setOutlineColor(sf::Color::White);
    amount.setOutlineThickness(5);
    amount.setOutlineColor(sf::Color::White);
    unit.setOutlineThickness(5);
    unit.setOutlineColor(sf::Color::White);
    timing.setOutlineThickness(5);
    timing.setOutlineColor(sf::Color::White);

textbox1.drawTo(window);
window.draw(name);
window.draw(amount);
window.draw(unit);
window.draw(timing);
window.draw(reset);
window.draw(finish);
window.draw(text1);
window.draw(text2);
window.draw(text3);
window.draw(text4);
window.draw(text5);


window.display();


sf::Event Event;

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    textbox1.setSelected(true);
}
else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    textbox1.setSelected(false);
}

while (window.pollEvent(Event)) {
    if (Event.type == sf::Event::Closed) {
        window.close();  
    }
    if (Event.type == sf::Event::TextEntered) {
  textbox1.typedOn(Event);
}
window.clear(sf::Color::Black);
}
}
return 0;
}