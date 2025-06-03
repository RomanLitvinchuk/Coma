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
	case 3: //Боёвка
		state->currentState = States::COMBAT_MENU;
		break;
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

CombatSystem::CombatState GameController::handleCombatMenu(int choice, Player& player, std::vector<Enemy>& enemies)
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::CHOOSE_ENEMIES_MENU;
		break;
	case 2:
		player.setDefending();
		CombatSystem::EnemyTurn(player, enemies);
		player.StopDefending();
		if (!player.isAlive()) { return CombatSystem::ENEMY_WIN; }
		else { return CombatSystem::CONTINUE; }
		break;
	//case 3: Предметы
	case 4:
		state->currentState = States::ENEMY_LIST_MENU;
		return CombatSystem::CONTINUE;
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"Некорректный ввод!");
		return CombatSystem::CONTINUE;
	}
}

CombatSystem::CombatState GameController::handleChooseEnemyMenu(int choice, Player& player, std::vector<Enemy>& enemies) 
{
	switch (choice) 
	{
	case 0:
		state->currentState = States::COMBAT_MENU;
		return CombatSystem::CONTINUE;
		break;
	default:
		if (choice <= enemies.size()) 
		{
			CombatSystem::PlayerAttack(enemies[choice-1], player);
			CombatSystem::EnemyTurn(player, enemies);
			state->currentState = States::COMBAT_MENU;
			if (!player.isAlive()) { return CombatSystem::ENEMY_WIN; }
			bool AllFalse = true;
			for (auto& currentEnemy : enemies) 
			{
				if (currentEnemy.isAlive()) 
				{
					AllFalse = false;
					break;
				}
			}
			if (AllFalse) { 
				return CombatSystem::PLAYER_WIN; 
			}
			else { 
				return CombatSystem::CONTINUE; 
				state->currentState = States::COMBAT_MENU;
			}
		}
		else 
		{
			std::cin.ignore();
			TextView::showMessage(u8"Некорректный ввод!");
			return CombatSystem::CONTINUE;
		}
		break;
	}

}

void GameController::handleEnemyListMenu(int choice) 
{
	switch (choice) 
	{
	case 0:
		state->currentState = States::COMBAT_MENU;
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"Некорректный ввод!");
	}
}