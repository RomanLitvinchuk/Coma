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
		bool isRunning = true;
		MeleeWeapon ExampleMelee = MeleeLoader("melee.txt", "1");
		GunWeapon ExampleGun = GunLoader("guns.txt", "1");
		Player player(ExampleMelee, ExampleGun);
		std::vector<Enemy> enemies;
		GameState state(player, enemies);
		std::vector<int> IdOfEnemy = { 1, 2 };
		state.enemies = EnemyLoader("enemies.txt", IdOfEnemy);
		GameController controller(&state);
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
			case States::COMBAT_MENU:
			{
				//CombatSystem battle(player, enemies);
				TextView::ShowCombatMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				auto result = controller.handleCombatMenu(choice, player, state.enemies);

				switch (result) 
				{
				case CombatSystem::PLAYER_WIN:
					for (auto& currentEnemy : enemies) 
					{
						player.GainExperience(currentEnemy.getExperience());
					}
					TextView::showMessage(u8"Победа!");
					state.enemies.clear();
					std::cin.ignore();
					state.currentState = States::GAME_MENU;
					break;
				case CombatSystem::ENEMY_WIN:
					TextView::showMessage(u8"Вы проиграли, возвращение в главное меню...");
					std::cin.ignore();
					state.currentState = States::MAIN_MENU;
					break;
				}
				break;
			}
			case States::CHOOSE_ENEMIES_MENU:
			{
				TextView::ShowEnemyListInCombat(state.enemies);
				std::cin >> input;
				int choice = std::stoi(input);
				auto result = controller.handleChooseEnemyMenu(choice, player, state.enemies);
				switch (result)
				{
				case CombatSystem::PLAYER_WIN:
					for (auto& currentEnemy : enemies)
					{
						player.GainExperience(currentEnemy.getExperience());
					}
					TextView::showMessage(u8"Победа!");
					state.enemies.clear();
					std::cin.ignore();
					state.currentState = States::GAME_MENU;
					break;
				case CombatSystem::ENEMY_WIN:
					TextView::showMessage(u8"Вы проиграли, возвращение в главное меню...");
					std::cin.ignore();
					state.currentState = States::MAIN_MENU;
					break;
				}
				break;
			}
			case States::ENEMY_LIST_MENU:
			{
				TextView::showEnemyList(state.enemies);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.handleEnemyListMenu(choice);
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

