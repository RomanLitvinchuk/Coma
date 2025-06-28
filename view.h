#ifndef VIEW_H_
#define VIEW_H_

#include <string>
#include <vector>

#include "enemy.h"
#include "melee_weapon.h"
#include "player.h"
#include "states.h"

class View {
 public:
  static void ClearScreen();
  static void ViewMainMenu();
  static void ViewGameMenu();
  static void ViewCombatMenu(const Player& player);
  static void ViewMessage(const std::string& str);
  static void ViewPlayerMenu(const Player& player);
  static void ViewLevelMenu(const Player& player);
  static void ViewEnemyList(const std::vector<Enemy>& enemies);
  static void ViewEnemyListInCombat(const std::vector<Enemy>& enemies);
  static void ViewMeleeStats(const MeleeWeapon& melee);
  static void ViewInventoryItemsMenu(const Player& player);
  static void ViewRoomMenu(const GameState& state);
  static void ViewRoomChooseMenu(const GameState& state,
                                 const std::vector<Room>& all_rooms);
  static void ViewInventoryMeleeMenu(const Player& player);
  static void ViewInventoryGunMenu(const Player& player);
};

#endif  // VIEW_H_
