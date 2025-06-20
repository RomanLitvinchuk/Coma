#include <Windows.h>

#include <iostream>
#include <string>

#include "controller.h"
#include "enemy.h"
#include "enemy_factory.h"
#include "gun.h"
#include "inventory.h"
#include "item.h"
#include "melee_weapon.h"
#include "player.h"
#include "room.h"
#include "states.h"
#include "view.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  try {
    bool is_running = true;
    MeleeWeapon example_melee = MeleeLoader("melee.txt", "1");
    GunWeapon example_gun = GunLoader("guns.txt", "1");
    Player player(example_melee, example_gun);
    std::vector<Enemy> all_enemies = LoadAllEnemies("enemies.txt");
    std::vector<Item> all_items = LoadAllItems("items.txt");
    std::vector<Room> all_rooms = LoadAllRooms("rooms.txt");
    player.inventory_.AddItem("1", all_items);
    std::vector<Enemy> enemies;
    Room empty_room("", "", "", RoomType::kDefault, {}, {});
    GameState state(player, enemies, empty_room);
    state.current_room_ = RoomFactory("1", all_rooms);
    // std::vector<std::string> IdOfEnemy = {"1"};
    Controller controller(&state);
    std::string input;
    while (is_running) {
      std::cin.ignore();
      View::ClearScreen();
      switch (state.current_state_) {
        case States::kMainMenu: {
          View::ShowMainMenu();
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleMainMenu(choice);
          break;
        }

        case States::kGameMenu: {
          View::ShowGameMenu();
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleGameMenu(choice);
          break;
        }

        case States::kPlayerMenu: {
          View::ShowPlayerMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandlePlayerMenu(choice);
          break;
        }

        case States::kLevelMenu: {
          View::ShowLevelMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleLevelMenu(choice, player);
          break;
        }

        case States::kCombatMenu: {
          View::ShowCombatMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          auto result =
              controller.HandleCombatMenu(choice, player, state.enemies_);

          switch (result) {
            case CombatSystem::PLAYER_WIN:
              for (auto& current_enemy : state.enemies_) {
                player.GainExperience(current_enemy.GetExperience());
              }
              View::ShowMessage(u8"Победа!");
              state.enemies_.clear();
              std::cin.ignore();
              state.current_state_ = States::kGameMenu;
              break;
            case CombatSystem::ENEMY_WIN:
              state.enemies_.clear();
              View::ShowMessage(
                  u8"Вы проиграли, возвращение в главное меню...");
              std::cin.ignore();
              state.current_state_ = States::kMainMenu;
              break;
          }
          break;
        }
        case States::kChooseEnemiesMenu: {
          View::ShowEnemyListInCombat(state.enemies_);
          std::cin >> input;
          int choice = std::stoi(input);
          auto result =
              controller.HandleChooseEnemyMenu(choice, player, state.enemies_);
          switch (result) {
            case CombatSystem::PLAYER_WIN:
              for (auto& current_enemy : state.enemies_) {
                player.GainExperience(current_enemy.GetExperience());
              }
              View::ShowMessage(u8"Победа!");
              state.enemies_.clear();
              std::cin.ignore();
              state.current_state_ = States::kGameMenu;
              break;
            case CombatSystem::ENEMY_WIN:
              View::ShowMessage(
                  u8"Вы проиграли, возвращение в главное меню...");
              std::cin.ignore();
              state.current_state_ = States::kMainMenu;
              break;
          }
          break;
        }
        case States::kEnemyListMenu: {
          View::ShowEnemyList(state.enemies_);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleEnemyListMenu(choice);
          break;
        }
        case States::kInventoryInCombatMenu: {
          View::ShowInventoryInCombat(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleInventoryInCombatMenu(choice, player);
          break;
        }
        case States::kRoomMenu: {
          View::ShowRoomMenu(state);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleRoomMenu(choice, all_enemies);
          break;
        }
        case States::kChooseRoomMenu:
          View::ShowRoomChooseMenu(state, all_rooms);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleRoomChooseMenu(choice, all_rooms);
          break;
      }
    }
  } catch (const std::exception& error) {
    std::cerr << u8"Ошибка: " << error.what() << "\n";
    return 1;
  }
  return 0;
}
