#include "controller.h"
#include "view.h"
#include <iostream>

void Controller::HandleMainMenu(int choice)
{
	switch (choice) 
	{
	case 1: //Новая игра
		state->currentState = States::GAME_MENU;
		View::ShowMessage(u8"Новая игра начата!");
		break;
	//case 2: Сохранение
	//	std::cin.ignore();
	case 3:
		exit(0);
		break;
	default:
		std::cin.ignore();
		View::ShowMessage(u8"Некорректный ввод!");
	}
}

void Controller::HandleGameMenu(int choice) 
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
		View::ShowMessage(u8"Некорректный ввод!");
	}

}

void Controller::HandlePlayerMenu(int choice) 
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
		View::ShowMessage(u8"Некорректный ввод!");
	}
}

void Controller::HandleLevelMenu(int choice, Player& player) 
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::PLAYER_MENU;
		break;
	case 2:
		if (player.GetLevelPoints() > 0) 
		{ 
			player.MaxHealthUp(); 
			player.SetLevelPoints(player.GetLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			View::ShowMessage(u8"Не хватает очков характеристик!");
		}
		break;
	case 3: 
		if (player.GetLevelPoints() > 0) 
		{ 
			player.MeleeLevelUp(); 
			player.SetLevelPoints(player.GetLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			View::ShowMessage(u8"Не хватает очков характеристик!");
		}
		break;
	case 4:
		if (player.GetLevelPoints() > 0) 
		{ 
			player.GunLevelUp(); 
			player.SetLevelPoints(player.GetLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			View::ShowMessage(u8"Не хватает очков характеристик!");
		}
		break;
	case 5:
		if (player.GetLevelPoints() > 0) 
		{ 
			player.IntelligenceUp(); 
			player.SetLevelPoints(player.GetLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			View::ShowMessage(u8"Не хватает очков характеристик!");
		}
		break;
	default:
		std::cin.ignore();
		View::ShowMessage(u8"Некорректный ввод!");
	}
}

CombatSystem::CombatState Controller::HandleCombatMenu(int choice, Player& player, std::vector<Enemy>& enemies)
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::CHOOSE_ENEMIES_MENU;
		break;
	case 2:
		player.SetDefending();
		CombatSystem::EnemyTurn(player, enemies);
		player.StopDefending();
		if (!player.IsAlive()) { return CombatSystem::ENEMY_WIN; }
		else { return CombatSystem::CONTINUE; }
		break;
	case 3:
		state->currentState = States::INVENTORY_IN_COMBAT_MENU;
		break;
	case 4:
		state->currentState = States::ENEMY_LIST_MENU;
		return CombatSystem::CONTINUE;
		break;
	default:
		std::cin.ignore();
		View::ShowMessage(u8"Некорректный ввод!");
		return CombatSystem::CONTINUE;
	}
}

CombatSystem::CombatState Controller::HandleChooseEnemyMenu(int choice, Player& player, std::vector<Enemy>& enemies) 
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
			if (!player.IsAlive()) { return CombatSystem::ENEMY_WIN; }
			bool AllFalse = true;
			for (auto& currentEnemy : enemies) 
			{
				if (currentEnemy.IsAlive()) 
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
			View::ShowMessage(u8"Некорректный ввод!");
			return CombatSystem::CONTINUE;
		}
		break;
	}

}

void Controller::HandleEnemyListMenu(int choice) 
{
	switch (choice) 
	{
	case 0:
		state->currentState = States::COMBAT_MENU;
		break;
	default:
		std::cin.ignore();
		View::ShowMessage(u8"Некорректный ввод!");
	}
}

void Controller::HandleInventoryInCombatMenu(int choice, Player& player) 
{
	switch (choice) 
	{
	case 0:
		state->currentState = States::COMBAT_MENU;
		break;
	default:
		if (choice <= player.inventory.items.size()) 
		{
			if (player.GetHealth() < player.GetMaxHealth()) 
			{
				player.Heal(player.inventory.items[choice - 1].GetHealAmount());
				View::ShowMessage(u8"Вы использовали " + player.inventory.items[choice - 1].GetName() + u8", вы восстановили " + std::to_string(player.inventory.items[choice - 1].GetHealAmount()));
				std::cin.ignore();
				player.inventory.RemoveItem(player.inventory.items[choice - 1].GetID());
			}
			else { View::ShowMessage(u8"У вас уже полное здоровье"); }
			std::cin.ignore();
		}
		else 
		{
			std::cin.ignore();
			View::ShowMessage(u8"Некорректный ввод!");
		}
	}
}