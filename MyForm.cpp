#include "MyForm.h"
#include <SFML/Graphics.hpp>
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
#include "AskWindow.h"

using namespace RealKursach;
using namespace sf;

int main() {
    extern std::string userName;
    //This is authorization form 
	
	Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    RealKursach::MyForm form; //WinFormsTest - имя вашего проекта
    Application::Run(% form);
    
    
    std::ofstream out(userName + ".txt", ios_base::app);
	/*
        Play part
    */
    AskWindow aAskWindow;
    WayOfInput wayofinput = aAskWindow.whereToGetCombination();
    Game game;//Main game class
    bool combinationFromFileCanBeAssembled = true;
    if (wayofinput == fromFile)combinationFromFileCanBeAssembled = game.inputFile();
    else game.generateCombination();

    if (combinationFromFileCanBeAssembled) {
        PlayWindow aPlayWindow;
        aPlayWindow.letIsPlay(out, game);
    }
    else {
        MsgBox errorMessage;
        errorMessage.show("Can`t be solved!");
    }
	return 0;
}