#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>
#include "Game.h"
#include "MsgBox.h"
#include "PlayWindow.h"

using namespace std;
using namespace sf;


enum WayOfInput {
    fromFile = 0,
    generateCombination = 1
};

class AskWindow {
    RenderWindow form;
public:
    AskWindow();//ctor
    WayOfInput whereToGetCombination();//to read combination from file or to generate it?
};

AskWindow::AskWindow() {
    form.create(VideoMode(300, 240), "How to get start combination?", Style::Titlebar);
}

WayOfInput AskWindow::whereToGetCombination() {
    Texture txbuttonInputFromFile;
    Texture txbuttonGenerate;
    txbuttonInputFromFile.loadFromFile("inputFromFileCoffee.png");
    txbuttonGenerate.loadFromFile("generateCoffee.png");
    Sprite spbuttonInputFromFile;
    Sprite spbuttonGenerate;
    spbuttonInputFromFile.setTexture(txbuttonInputFromFile); spbuttonInputFromFile.setPosition(Vector2f(10, 20));
    spbuttonGenerate.setTexture(txbuttonGenerate); spbuttonGenerate.setPosition(Vector2f(10, 130));


    while (form.isOpen()) {
        Event event;

        while (form.pollEvent(event)) {
            if (event.type == Event::Closed) {
                cout << "Ask form has been closed!\n";
                form.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                Mouse mouse;
                Vector2i mousePos = mouse.getPosition(form);
                if (mousePos.x > 10 && mousePos.x < 290 && mousePos.y>20 && mousePos.y < 120) {
                    //inputFromFile Button
                    form.close();
                    return fromFile;
                }
                else if (mousePos.x > 10 && mousePos.x < 290 && mousePos.y>130 && mousePos.y < 230) {
                    //generate button
                    form.close();
                    return generateCombination;
                }

            }
        }
        form.clear(sf::Color(85, 46, 31, 255));
        form.draw(spbuttonInputFromFile);
        form.draw(spbuttonGenerate);
        form.display();
    }//main while
}