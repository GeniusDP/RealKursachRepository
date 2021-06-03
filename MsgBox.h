#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

class MsgBox {
	RenderWindow form;
public:
	MsgBox() {//ctor
		form.create(VideoMode(400, 200), "Message", Style::Close);
	}
	void show(string text);//to render message window
};


void MsgBox::show(string text) {//to render message window
	while (form.isOpen()) {
		Event event;
		while (form.pollEvent(event)) {
			if (event.type == Event::Closed) {
				form.close();
			}
		}
		sf::Text textOnScreen;
		sf::Font font;
		font.loadFromFile("myFont.ttf");
		textOnScreen.setFont(font);
		textOnScreen.setString(text);
		textOnScreen.setCharacterSize(40);
		textOnScreen.setFillColor(sf::Color(249, 166, 2, 255));//golden color for text
		textOnScreen.setPosition(Vector2f(0, 50));
		form.clear(sf::Color(105, 55, 35, 255));//wooden color for back
		form.draw(textOnScreen);
		form.display();
	}
}