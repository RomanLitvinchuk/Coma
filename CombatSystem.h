#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>

class CombatSystem 
{
private:
	Player& player;
	std::vector<Enemy> enemies;
	int experience;
public:
	enum CombatState {
		PLAYER_WIN,
		ENEMY_WIN,
		CONTINUE
	};
	//CombatState CurrentState = CombatState::CONTINUE;
	CombatSystem(Player& player, std::vector<Enemy> enemies) : player(player), enemies(enemies) {}
	static void PlayerAttack(Enemy& enemy, Player& player);
	static void EnemyTurn(Player& player, std::vector<Enemy>& enemies);
	void setExperience(int amount) { experience = amount; }
	int getExperience() const { return experience; }
};