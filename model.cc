#include <iostream>
#include <string>
#include <Windows.h>
#include "view.h"
#include "player.h"
#include "states.h"
#include "enemy.h"
#include "enemy_factory.h"
#include "controller.h"
#include "melee_weapon.h"
#include "gun.h"
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
		Controller controller(&state);
		std::string input;
		while (isRunning) 
		{
			std::cin.ignore();
			View::ClearScreen();
			switch (state.currentState) 
			{
			case States::MAIN_MENU: 
			{
				View::ShowMainMenu();
				std::cin >> input;
				int choice = std::stoi(input);
				controller.HandleMainMenu(choice);
				break;
			}

			case States::GAME_MENU: 
			{
				View::ShowGameMenu();
				std::cin >> input;
				int choice = std::stoi(input);
				controller.HandleGameMenu(choice);
				break;
			}

			case States::PLAYER_MENU: 
			{
				View::ShowPlayerMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.HandlePlayerMenu(choice);
				break;
			}
			case States::LEVEL_MENU:
			{
				View::ShowLevelMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.HandleLevelMenu(choice, player);
				break;
			}
			case States::COMBAT_MENU:
			{
				//CombatSystem battle(player, enemies);
				if (state.enemies.empty()) { state.enemies = EnemyFactory(AllEnemies, IdOfEnemy); }
				View::ShowCombatMenu(player);
				std::cin >> input;
				int choice = std::stoi(input);
				auto result = controller.HandleCombatMenu(choice, player, state.enemies);

				switch (result) 
				{
				case CombatSystem::PLAYER_WIN:
					for (auto& currentEnemy : state.enemies) 
					{
						player.GainExperience(currentEnemy.GetExperience());
					}
					View::ShowMessage(u8"Победа!");
					state.enemies.clear();
					std::cin.ignore();
					state.currentState = States::GAME_MENU;
					break;
				case CombatSystem::ENEMY_WIN:
					state.enemies.clear();
					View::ShowMessage(u8"Вы проиграли, возвращение в главное меню...");
					std::cin.ignore();
					state.currentState = States::MAIN_MENU;
					break;
				}
				break;
			}
			case States::CHOOSE_ENEMIES_MENU:
			{
				View::ShowEnemyListInCombat(state.enemies);
				std::cin >> input;
				int choice = std::stoi(input);
				auto result = controller.HandleChooseEnemyMenu(choice, player, state.enemies);
				switch (result)
				{
				case CombatSystem::PLAYER_WIN:
					for (auto& currentEnemy : state.enemies)
					{
						player.GainExperience(currentEnemy.GetExperience());
					}
					View::ShowMessage(u8"Победа!");
					state.enemies.clear();
					std::cin.ignore();
					state.currentState = States::GAME_MENU;
					break;
				case CombatSystem::ENEMY_WIN:
					View::ShowMessage(u8"Вы проиграли, возвращение в главное меню...");
					std::cin.ignore();
					state.currentState = States::MAIN_MENU;
					break;
				}
				break;
			}
			case States::ENEMY_LIST_MENU:
			{
				View::ShowEnemyList(state.enemies);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.HandleEnemyListMenu(choice);
				break;
			}
			case States::INVENTORY_IN_COMBAT_MENU:
			{
				View::ShowInventoryInCombat(player);
				std::cin >> input;
				int choice = std::stoi(input);
				controller.HandleInventoryInCombatMenu(choice, player);
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

