#ifndef COMBAT_SYSTEM_H_
#define COMBAT_SYSTEM_H_

#include <vector>

#include "enemy.h"
#include "player.h"

class CombatSystem {
 private:
  Player& player_;
  std::vector<Enemy> enemies_;
  int experience_;

 public:
  enum CombatState { PLAYER_WIN, ENEMY_WIN, CONTINUE };
  // CombatState CurrentState = CombatState::CONTINUE;
  CombatSystem(Player& player, std::vector<Enemy> enemies)
      : player_(player), enemies_(enemies) {}
  static void PlayerAttack(Enemy& enemy, Player& player);
  static void EnemyTurn(Player& player, std::vector<Enemy>& enemies);
  void SetExperience(int amount) { experience_ = amount; }
  int GetExperience() const { return experience_; }
};

#endif  // COMBAT_SYSTEM_H_
