#include <Windows.h>

#include <iostream>
#include <random>
#include <string>

#include "controller.h"
#include "enemy.h"
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
    std::vector<MeleeWeapon> all_melee = LoadAllMelee("melee.txt");
    MeleeWeapon example_melee = MeleeFactory("1", all_melee);
    std::vector<GunWeapon> all_guns = LoadAllGuns("guns.txt");
    GunWeapon example_gun = GunFactory("1", all_guns);
    Player player(example_melee, example_gun);
    player.inventory_.AddMelee("1", all_melee);
    player.inventory_.AddGun("1", all_guns);
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
          View::ViewMainMenu();
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleMainMenu(choice);
          break;
        }

        case States::kGameMenu: {
          View::ViewGameMenu();
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleGameMenu(choice);
          break;
        }

        case States::kPlayerMenu: {
          View::ViewPlayerMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandlePlayerMenu(choice);
          break;
        }

        case States::kLevelMenu: {
          View::ViewLevelMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleLevelMenu(choice, player);
          break;
        }

        case States::kCombatMenu: {
          View::ViewCombatMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          auto result =
              controller.HandleCombatMenu(choice, player, state.enemies_);

          switch (result) {
            case CombatSystem::kPlayerWin:
              for (auto& current_enemy : state.enemies_) {
                player.GainExperience(current_enemy.GetExperience());
              }
              View::ViewMessage(u8"Победа!");
              state.enemies_.clear();
              std::cin.ignore();
              state.current_state_ = States::kGameMenu;
              break;
            case CombatSystem::kEnemyWin:
              state.enemies_.clear();
              View::ViewMessage(
                  u8"Вы проиграли, возвращение в главное меню...");
              std::cin.ignore();
              state.current_state_ = States::kMainMenu;
              break;
          }
          break;
        }
        case States::kChooseEnemiesMenu: {
          View::ViewEnemyListInCombat(state.enemies_);
          std::cin >> input;
          int choice = std::stoi(input);
          auto result =
              controller.HandleChooseEnemyMenu(choice, player, state.enemies_);
          switch (result) {
            case CombatSystem::kPlayerWin:
              for (auto& current_enemy : state.enemies_) {
                player.GainExperience(current_enemy.GetExperience());
              }
              View::ViewMessage(u8"Победа!");
              state.enemies_.clear();
              std::cin.ignore();
              state.current_state_ = States::kGameMenu;
              break;
            case CombatSystem::kEnemyWin:
              View::ViewMessage(
                  u8"Вы проиграли, возвращение в главное меню...");
              std::cin.ignore();
              state.current_state_ = States::kMainMenu;
              break;
          }
          break;
        }

        case States::kEnemyListMenu: {
          View::ViewEnemyList(state.enemies_);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleEnemyListMenu(choice);
          break;
        }

        case States::kInventoryInCombatMenu: {
          View::ViewInventoryItemsMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleInventoryInCombatMenu(choice, player);
          break;
        }

        case States::kInventoryItemsMenu: {
          View::ViewInventoryItemsMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleInventoryItemsMenu(choice, player);
          break;
        }

        case States::kInventoryMeleeMenu: {
          View::ViewInventoryMeleeMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleInventoryMeleeMenu(choice, player);
          break;
        }

        case States::kInventoryGunMenu: {
          View::ViewInventoryGunMenu(player);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleInventoryGunMenu(choice, player);
          break;
        }

        case States::kRoomMenu: {
          View::ViewRoomMenu(state);
          std::cin >> input;
          int choice = std::stoi(input);
          controller.HandleRoomMenu(choice, player, all_enemies, all_melee,
                                    all_guns, all_items);
          break;
        }

        case States::kChooseRoomMenu:
          View::ViewRoomChooseMenu(state, all_rooms);
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
