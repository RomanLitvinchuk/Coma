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
  static void ShowMainMenu();
  static void ShowGameMenu();
  static void ShowCombatMenu(const Player& player);
  static void ShowMessage(const std::string& str);
  static void ShowPlayerMenu(const Player& player);
  static void ShowLevelMenu(const Player& player);
  static void ShowEnemyList(const std::vector<Enemy>& enemies);
  static void ShowEnemyListInCombat(const std::vector<Enemy>& enemies);
  static void ShowMeleeStats(const MeleeWeapon& melee);
  static void ShowInventoryInCombat(const Player& player);
  static void ShowRoomMenu(const GameState& state);
  static void ShowRoomChooseMenu(const GameState& state,
                                 const std::vector<Room>& all_rooms);
};

#endif  // VIEW_H_
