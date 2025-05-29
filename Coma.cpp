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
				try {
					int choice = std::stoi(input);
					controller.handleMainMenu(choice);
				}
				catch (...)
				{
					TextView::showMessage(u8"Некорректный ввод");
				}
				break;
			}

			case States::GAME_MENU: 
			{
				TextView::showGameMenu();
				std::cin >> input;
				try 
				{
					int choice = std::stoi(input);
					controller.handleGameMenu(choice);
				}
				catch (...) 
				{
					TextView::showMessage(u8"Некорректный ввод");
				}
				break;
			}

			case States::PLAYER_MENU: 
			{
				TextView::showPlayerMenu(player);
				std::cin >> input;
				try 
				{
					int choice = std::stoi(input);
					controller.handlePlayerMenu(choice);
				}
				catch (...) 
				{
					TextView::showMessage(u8"Некорректный ввод");
				}
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

