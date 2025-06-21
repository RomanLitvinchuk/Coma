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
    enemy.TakeDamage(CalculateMeleeDamage(player));
    View::ShowMessage(u8"Вы нанесли " +
                      std::to_string(CalculateMeleeDamage(player)) + u8" урона " +
                      enemy.GetName() + "\n");
    if (enemy.GetHealth() <= 0) {
        View::ShowMessage(u8"Вы убили " + enemy.GetName());
    }

  } else {
    View::ShowMessage(u8"Мимо!");
  }
}

void CombatSystem::EnemyTurn(Player& player, std::vector<Enemy>& enemies) {
  for (auto& current_enemy : enemies) {
    if (current_enemy.IsAlive()) {
      player.TakeDamage(current_enemy.GetAttack());
      View::ShowMessage(u8"Враг " + current_enemy.GetName() + u8" нанёс вам " +
                        std::to_string(current_enemy.GetAttack()) +
                        u8" урона!");
    }
    std::cin.ignore();
  }
}

int CombatSystem::CalculateMeleeDamage(const Player& player) {
  double base_damage =
      player.current_melee_.GetDamage() + player.GetMeleeLevel() * 0.2f;
  double mental_multiplier =
      1.0f + (100 - player.GetMentalHealth()) * 0.005f * 0.5f;
  double total_damage = base_damage * mental_multiplier;
  return static_cast<int>(std::round(total_damage));
}
