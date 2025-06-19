#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include "player.h"
#include "enemy.h"
#include "melee_weapon.h"

class View 
{
public:
	static void ClearScreen();
	static void ShowMainMenu();
	static void ShowGameMenu();
	static void ShowCombatMenu(const Player& player);
	static void ShowMessage(const std::string& str);
	static void ShowPlayerMenu(const Player& player);
	static void ShowLevelMenu(const Player& player);
	static void ShowEnemyList(const std::vector<Enemy>& enemies);
	static void ShowEnemyListInCombat(const std::vector<Enemy>& enemies);
	static void ShowMeleeStats(const MeleeWeapon& melee);
	static void ShowInventoryInCombat(const Player& player);
};

#endif