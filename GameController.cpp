#include "GameController.h"
#include "TextView.h"
#include <iostream>

void GameController::handleMainMenu(int choice)
{
	switch (choice) 
	{
	case 1: //Новая игра
		state->currentState = States::GAME_MENU;
		TextView::showMessage(u8"Новая игра начата!");
		break;
	//case 2: Сохранение
	//	std::cin.ignore();
	case 3:
		exit(0);
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"Некорректный ввод!");
	}
}

void GameController::handleGameMenu(int choice) 
{
	switch (choice) 
	{
	//case 1: Передвижение

	case 2: //Игрок
		state->currentState = States::PLAYER_MENU;
		break;
	//case 3: Боёвка
	//case 4: Сохранение
	case 5:
		state->currentState = States::MAIN_MENU;
		break;
	}
}

void GameController::handlePlayerMenu(int choice) 
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::GAME_MENU;
		break;
	}
}
