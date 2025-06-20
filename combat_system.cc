#include "combat_system.h"

#include <iostream>
#include <random>

#include "view.h"

namespace {
std::mt19937 gen(std::random_device{}());
}

void CombatSystem::PlayerAttack(Enemy& enemy, Player& player) {
  std::uniform_real_distribution<double> dis(1.0, 100.0);
  double hit_chance = dis(gen);
  if (hit_chance < player.current_melee_.GetAccuracy()) {
    enemy.TakeDamage(player.current_melee_.GetDamage());
    View::ShowMessage(u8"Вы нанесли " +
                      std::to_string(player.current_melee_.GetDamage()) +
                      u8" урона " + enemy.GetName() + "\n");

  } else {
    View::ShowMessage(u8"Мимо!");
  }
}

void CombatSystem::EnemyTurn(Player& player, std::vector<Enemy>& enemies) {
  for (auto& current_enemy : enemies) {
    if (current_enemy.IsAlive()) {
      player.TakeDamage(current_enemy.GetAttack());
      View::ShowMessage(u8"Враг " + current_enemy.GetName() + u8" нанёс вам " +
                        std::to_string(current_enemy.GetAttack()) + u8" урона!");
    }
    std::cin.ignore();
  }
}
