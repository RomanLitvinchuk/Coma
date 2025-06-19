#include "combat_system.h"
#include "view.h"
#include <iostream>
#include <random>

namespace {
	std::mt19937 gen(std::random_device{}());
}

void CombatSystem::PlayerAttack(Enemy& enemy, Player& player) 
{
	std::uniform_real_distribution<double> dis(1.0, 100.0);
	double HitChance = dis(gen);
	if (HitChance < player.CurrentMelee.GetAccuracy()) 
	{
		enemy.TakeDamage(player.CurrentMelee.GetDamage());
		View::ShowMessage(u8"Вы нанесли " + std::to_string(player.CurrentMelee.GetDamage()) + u8" урона " + enemy.GetName() + "\n");
		
	}
	else 
	{
		View::ShowMessage(u8"Мимо!");
	}
}


void CombatSystem::EnemyTurn(Player& player, std::vector<Enemy>& enemies)
{
	for (auto& currentEnemy : enemies)
	{
		if (currentEnemy.IsAlive())
		{
			player.TakeDamage(currentEnemy.GetAttack());
			View::ShowMessage(u8"Враг " + currentEnemy.GetName() + u8" нанёс вам " + std::to_string(currentEnemy.GetAttack()) + u8" урона!");
		}
		std::cin.ignore();
	}
}