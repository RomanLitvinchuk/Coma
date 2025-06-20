#ifndef STATES_H_
#define STATES_H_

#include <vector>

#include "enemy.h"
#include "player.h"
#include "room.h"
enum class States {
  MAIN_MENU,
  GAME_MENU,
  COMBAT_MENU,
  CHOOSE_ENEMIES_MENU,
  ENEMY_LIST_MENU,
  PLAYER_MENU,
  LEVEL_MENU,
  INVENTORY_IN_COMBAT_MENU,
  ROOM_MENU,
  CHOOSE_ROOM_MENU
};

class GameState {
 public:
  Player& player;
  std::vector<Enemy> enemies;
  States currentState = States::MAIN_MENU;
  Room currentRoom;
  GameState(Player& player, std::vector<Enemy>& enemies, Room& room)
      : player(player), enemies(enemies), currentRoom(room) {}
};

#endif  // STATES_H_
