#pragma once
#include "States.h"
#include "Player.h"
#include "Enemy.h"
#include "CombatSystem.h"
#include <vector>
class GameController 
{
private:
	GameState* state;
public:
	GameController(GameState* state) : state(state) {}

	void handleMainMenu(int choice);
	void handleGameMenu(int choice);
	void handlePlayerMenu(int choice);
	void handleLevelMenu(int choice, Player& player);
	void handleEnemyListMenu(int choice);
	CombatSystem::CombatState handleCombatMenu(int choice, Player& player, std::vector<Enemy>& enemies);
	CombatSystem::CombatState handleChooseEnemyMenu(int choice, Player& player, std::vector<Enemy>& enemies);
	void handleInventoryInCombatMenu(int choice, Player& player);
};