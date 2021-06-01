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


using namespace std;
using namespace sf;

const int blockSize = 150;



class PlayWindow {
    RenderWindow form;
public:
    PlayWindow();//ctor
    void initSprites(Texture& tx, vector<Sprite>& sp);//to make sprites from tile and "give" `em positions on scree
    void letIsPlay(ostream& outFileStream, Game game);//open main game window
};

PlayWindow::PlayWindow() {
    form.create(VideoMode(750, 700), "FIFTEEN PLAY", Style::Titlebar);
}

void PlayWindow::initSprites(Texture& tx, vector<Sprite>& sp) {
    for (int i = 1; i <= 16; i++) {
        sp[i].setTexture(tx);
        sp[i].setTextureRect(IntRect((i - 1) % 4 * blockSize, (i - 1) / 4 * blockSize, blockSize, blockSize));
        sp[i].setColor(sf::Color(207, 174, 139, 255));
    }
}

void PlayWindow::letIsPlay(ostream& outFileStream, Game game) {
    outFileStream << game.getField();//printing a start combination into file
        time_t startTime = clock();//get start time
    Texture tx;
    tx.loadFromFile("15.jpg");

    vector<Sprite> block(17);
    initSprites(tx, block);

    Texture txbuttonHelp; txbuttonHelp.loadFromFile("help.png");
    Texture txbuttonExitAndSave; txbuttonExitAndSave.loadFromFile("exitandsave.png");
    Sprite spbuttonHelp, spbuttonExitAndSave;
    spbuttonHelp.setTexture(txbuttonHelp); spbuttonHelp.setPosition(600, 0);
    spbuttonExitAndSave.setTexture(txbuttonExitAndSave); spbuttonExitAndSave.setPosition(600, 300);

    bool madeStepAfterHelp = false;//дописать
    while (form.isOpen() && !game.getField().isAssembled()) {//*****
        Event event;

        while (form.pollEvent(event)) {
            if (event.type == Event::Closed) {
                cout << "Form has been closed!\n";
                form.close();
            }
            if (event.type == Event::MouseButtonPressed) {//detection of mouse click
                Mouse mouse;
                Vector2i mousePos = mouse.getPosition(form);
                //cout << "Mouse: " << mousePos.x << " " << mousePos.y << endl;
                for (int i = 1; i <= 4; i++)
                    for (int j = 1; j <= 4; j++)
                        if ((i - 1) * blockSize < mousePos.y && (j - 1) * blockSize < mousePos.x && (i - 1) * blockSize + blockSize > mousePos.y && (j - 1) * blockSize + blockSize > mousePos.x) {
                            if (game.getField().changeMap(i, j)) {
                                madeStepAfterHelp = true;
                                game.incrementSteps();
                            }
                            break;
                        }
                if (mousePos.x > 600 && mousePos.x < 750 && mousePos.y>0 && mousePos.y < 300) {
                    //Help Button
                    MsgBox helpWindow;
                    helpWindow.show("Next step is: " + to_string(game.solve(madeStepAfterHelp)));
                    //cout << "Next step is: " << game.solve(madeStepAfterHelp) << "\n";
                    madeStepAfterHelp = false;
                    //throw MSGBOX with next step
                }
                else if (mousePos.x > 600 && mousePos.x < 750 && mousePos.y>300 && mousePos.y < 600) {
                    //ExitButton
                    form.close();
                }

            }//MouseButtonPressedevent
        }

        sf::Font font; font.loadFromFile("myFont.ttf");//font for every written message
        /*here I work with timer text*/
            time_t currTime = clock();//current system time
            sf::Text timerText;
        
            timerText.setFont(font);
            timerText.setString("Time: " + to_string( (currTime-startTime)/CLOCKS_PER_SEC ) + " sec");
            timerText.setCharacterSize(40);
            timerText.setFont(font);
            timerText.setPosition(sf::Vector2f(40, 630));
            timerText.setFillColor(sf::Color(249, 166, 2, 255));//golden color for text
        /*here I work with timer text*/

        /*here I work with number of steps text*/
            sf::Text stepsText;

            stepsText.setFont(font);
            stepsText.setString("Steps: " + to_string(game.getNumberOfSteps()));
            stepsText.setCharacterSize(40);
            stepsText.setFont(font);
            stepsText.setPosition(sf::Vector2f(500, 630));
            stepsText.setFillColor(sf::Color(249, 166, 2, 255));//golden color for text

        /*here I work with number of steps text*/

        form.clear(sf::Color(105, 55, 35, 255));//wooden color
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= 4; j++) {
                block[game.getField().at(i, j)].setPosition((j - 1) * blockSize, (i - 1) * blockSize);//*****
                form.draw(block[game.getField().at(i, j)]);//*****
            }
        }
        form.draw(spbuttonHelp);
        form.draw(spbuttonExitAndSave);
            form.draw(timerText);
            form.draw(stepsText);
        form.display();
    }
    form.close();
    MsgBox finalMessage;
    //printing to file
    //and printing onto screen 
    //info about the game


/*
    getting current date
*/
    time_t now = time(0);
    char* dateString = ctime(&now);
    if (game.getField().isAssembled()) {
        finalMessage.show(" You have won!");
        outFileStream << dateString;
        outFileStream << "YOU HAVE WON!" << endl;
        outFileStream << "Steps made: " << game.getNumberOfSteps() << endl;
        outFileStream << "Time required: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
        outFileStream << "**********************************************************" << endl;
    }
    else {
        finalMessage.show("    You loose!");
        outFileStream << dateString;
        outFileStream << "YOU LOOSE!" << endl;
        outFileStream << "Steps made: " << game.getNumberOfSteps() << endl;
        outFileStream << "Time required: " << (clock() - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
        outFileStream << "**********************************************************" << endl;
    }
}