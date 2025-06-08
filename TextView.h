#pragma once
#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "MeleeWeapon.h"

class TextView 
{
public:
	static void ClearScreen();
	static void showMainMenu();
	static void showGameMenu();
	static void ShowCombatMenu(const Player& player);
	static void showMessage(const std::string& str);
	static void showPlayerMenu(const Player& player);
	static void showLevelMenu(const Player& player);
	static void showEnemyList(const std::vector<Enemy>& enemies);
	static void ShowEnemyListInCombat(const std::vector<Enemy>& enemies);
	static void showMeleeStats(const MeleeWeapon& melee);
	static void ShowInventoryInCombat(const Player& player);
};