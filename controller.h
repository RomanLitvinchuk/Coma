#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "states.h"
#include "player.h"
#include "enemy.h"
#include "combat_system.h"
#include <vector>
class Controller 
{
private:
	GameState* state;
public:
	Controller(GameState* state) : state(state) {}

	void HandleMainMenu(int choice);
	void HandleGameMenu(int choice);
	void HandlePlayerMenu(int choice);
	void HandleLevelMenu(int choice, Player& player);
	void HandleEnemyListMenu(int choice);
	CombatSystem::CombatState HandleCombatMenu(int choice, Player& player, std::vector<Enemy>& enemies);
	CombatSystem::CombatState HandleChooseEnemyMenu(int choice, Player& player, std::vector<Enemy>& enemies);
	void HandleInventoryInCombatMenu(int choice, Player& player);
};

#endif