#ifndef COMBAT_SYSTEM_H_
#define COMBAT_SYSTEM_H_

#include <vector>

#include "enemy.h"
#include "player.h"

class CombatSystem {
 private:
  Player& player;
  std::vector<Enemy> enemies;
  int experience;

 public:
  enum CombatState { PLAYER_WIN, ENEMY_WIN, CONTINUE };
  // CombatState CurrentState = CombatState::CONTINUE;
  CombatSystem(Player& player, std::vector<Enemy> enemies)
      : player(player), enemies(enemies) {}
  static void PlayerAttack(Enemy& enemy, Player& player);
  static void EnemyTurn(Player& player, std::vector<Enemy>& enemies);
  void SetExperience(int amount) { experience = amount; }
  int GetExperience() const { return experience; }
};

#endif  // COMBAT_SYSTEM_H_
