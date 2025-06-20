#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>

#include "combat_system.h"
#include "enemy.h"
#include "player.h"
#include "states.h"
class Controller {
 private:
  GameState* state;

 public:
  Controller(GameState* state) : state(state) {}

  void HandleMainMenu(int choice);
  void HandleGameMenu(int choice);
  void HandlePlayerMenu(int choice);
  void HandleLevelMenu(int choice, Player& player);
  void HandleEnemyListMenu(int choice);
  CombatSystem::CombatState HandleCombatMenu(int choice, Player& player,
                                             std::vector<Enemy>& enemies);
  CombatSystem::CombatState HandleChooseEnemyMenu(int choice, Player& player,
                                                  std::vector<Enemy>& enemies);
  void HandleInventoryInCombatMenu(int choice, Player& player);
  void HandleRoomMenu(int choice, std::vector<Enemy>& allEnemies);
  void HandleRoomChooseMenu(int choice, std::vector<Room>& allRooms);
};

#endif  // CONTROLLER_H_
