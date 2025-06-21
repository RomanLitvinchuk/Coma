#ifndef STATES_H_
#define STATES_H_

#include <vector>

#include "enemy.h"
#include "player.h"
#include "room.h"
enum class States {
  kMainMenu,
  kGameMenu,
  kCombatMenu,
  kChooseEnemiesMenu,
  kEnemyListMenu,
  kPlayerMenu,
  kLevelMenu,
  kInventoryItemsMenu,
  kInventoryInCombatMenu,
  kInventoryMeleeMenu,
  kInventoryGunMenu,
  kRoomMenu,
  kChooseRoomMenu
};

class GameState {
 public:
  Player& player_;
  std::vector<Enemy> enemies_;
  States current_state_ = States::kMainMenu;
  Room current_room_;
  GameState(Player& player, std::vector<Enemy>& enemies, Room& room)
      : player_(player), enemies_(enemies), current_room_(room) {}
};

#endif  // STATES_H_
