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
    View::ShowMessage(u8"�� ������� " +
                      std::to_string(player.current_melee_.GetDamage()) +
                      u8" ����� " + enemy.GetName() + "\n");

  } else {
    View::ShowMessage(u8"����!");
  }
}

void CombatSystem::EnemyTurn(Player& player, std::vector<Enemy>& enemies) {
  for (auto& current_enemy : enemies) {
    if (current_enemy.IsAlive()) {
      player.TakeDamage(current_enemy.GetAttack());
      View::ShowMessage(u8"���� " + current_enemy.GetName() + u8" ���� ��� " +
                        std::to_string(current_enemy.GetAttack()) + u8" �����!");
    }
    std::cin.ignore();
  }
}
