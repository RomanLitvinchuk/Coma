#include "CombatSystem.h"
#include "TextView.h"
#include <iostream>
#include <random>

namespace {
	std::mt19937 gen(std::random_device{}());
}

void CombatSystem::PlayerAttack(Enemy& enemy, Player& player) 
{
	std::uniform_real_distribution<double> dis(1.0, 100.0);
	double HitChance = dis(gen);
	if (HitChance < player.CurrentMelee.getAccuracy()) 
	{
		enemy.takeDamage(player.CurrentMelee.getDamage());
		TextView::showMessage(u8"Вы нанесли " + std::to_string(player.CurrentMelee.getDamage()) + u8" урона " + enemy.getName() + "\n");
		
	}
	else 
	{
		TextView::showMessage(u8"Мимо!");
	}
}


void CombatSystem::EnemyTurn(Player& player, std::vector<Enemy>& enemies)
{
	for (auto& currentEnemy : enemies)
	{
		if (currentEnemy.isAlive())
		{
			player.takeDamage(currentEnemy.getAttack());
			TextView::showMessage(u8"Враг " + currentEnemy.getName() + u8" нанёс вам " + std::to_string(currentEnemy.getAttack()) + u8" урона!");
		}
		std::cin.ignore();
	}
}