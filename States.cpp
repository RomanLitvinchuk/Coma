#include "States.h"
#include <iostream>

void MainMenuState::render() 
{
	std::cout << "===============КОМА===============" << std::endl;
	std::cout << "1.Боёвка\n 2.Персонаж";
}

//void MainMenuState::handleInput(int input);