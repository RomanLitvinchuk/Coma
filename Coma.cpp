#include <iostream>
#include <string>
#include <Windows.h>
#include "TextView.h"
#include "Player.h"
#include "States.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "GameController.h"
#include "MeleeWeapon.h"
#include "Gun.h"
#include "item.h"
#include "inventory.h"
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
		std::vector<Enemy> AllEnemies = LoadAllEnemies("enemies.txt");
		std::vector<Item> AllItems = LoadAllItems("items.txt");
		player.inventory.AddItem("1", AllItems);
		std::vector<Enemy> enemies;
		GameState state(player, enemies);
		std::vector<std::string> IdOfEnemy = {"1"};
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
				if (state.enemies.empty()) { state.enemies = EnemyFactory(AllEnemies, IdOfEnemy); }
				TextView::ShowCombatMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				auto result = controller.handleCombatMenu(choice, player, state.enemies);

				switch (result) 
				{
				case CombatSystem::PLAYER_WIN:
					for (auto& currentEnemy : state.enemies) 
					{
						player.GainExperience(currentEnemy.getExperience());
					}
					TextView::showMessage(u8"Победа!");
					state.enemies.clear();
					std::cin.ignore();
					state.currentState = States::GAME_MENU;
					break;
				case CombatSystem::ENEMY_WIN:
					state.enemies.clear();
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
					for (auto& currentEnemy : state.enemies)
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
			case States::INVENTORY_IN_COMBAT_MENU:
			{
				TextView::ShowInventoryInCombat(player);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.handleInventoryInCombatMenu(choice, player);
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

