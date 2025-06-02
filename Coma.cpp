#include <iostream>
#include <string>
#include <Windows.h>
#include "TextView.h"
#include "Player.h"
#include "States.h"
#include "GameController.h"
#include "MeleeWeapon.h"
#include "Gun.h"
int main() 
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	try 
	{
		GameState state;
		GameController controller(&state);
		bool isRunning = true;
		MeleeWeapon ExampleMelee = MeleeLoader("melee.txt", "1");
		GunWeapon ExampleGun = GunLoader("guns.txt", "1");
		Player player(ExampleMelee, ExampleGun);
		int lp = 10;
		player.setLevelPoints(lp);
		std::string input;
		while (isRunning) 
		{
			std::cin.ignore();
			TextView::ClearScreen();
			switch (state.currentState) 
			{
			case States::MAIN_MENU: 
			{
				TextView::showMainMenu();
				std::cin >> input;
				int choice = std::stoi(input);
				controller.handleMainMenu(choice);
				break;
			}

			case States::GAME_MENU: 
			{
				TextView::showGameMenu();
				std::cin >> input;
				int choice = std::stoi(input);
				controller.handleGameMenu(choice);
				break;
			}

			case States::PLAYER_MENU: 
			{
				TextView::showPlayerMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.handlePlayerMenu(choice);
				break;
			}
			case States::LEVEL_MENU:
			{
				TextView::showLevelMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.handleLevelMenu(choice, player);
				break;
			}

			}
		}
	}
	catch (const std::exception& error) {
		std::cerr << u8"Ошибка: " << error.what() << "\n";
		return 1;
	}
	return 0;
}

