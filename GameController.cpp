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
	default:
		std::cin.ignore();
		TextView::showMessage(u8"Некорректный ввод!");
	}

}

void GameController::handlePlayerMenu(int choice) 
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::GAME_MENU;
		break;
	case 2:
		state->currentState = States::LEVEL_MENU;
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"Некорректный ввод!");
	}
}

void GameController::handleLevelMenu(int choice, Player& player) 
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::PLAYER_MENU;
		break;
	case 2:
		if (player.getLevelPoints() > 0) 
		{ 
			player.MaxHealthUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"Не хватает очков характеристик!");
		}
		break;
	case 3: 
		if (player.getLevelPoints() > 0) 
		{ 
			player.MeleeLevelUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"Не хватает очков характеристик!");
		}
		break;
	case 4:
		if (player.getLevelPoints() > 0) 
		{ 
			player.GunLevelUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"Не хватает очков характеристик!");
		}
		break;
	case 5:
		if (player.getLevelPoints() > 0) 
		{ 
			player.IntelligenceUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"Не хватает очков характеристик!");
		}
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"Некорректный ввод!");
	}
}
